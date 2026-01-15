#include "http_client.hpp"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <algorithm>

namespace {

size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t total_size = size * nmemb;
    userp->append(static_cast<char*>(contents), total_size);
    return total_size;
}

// Normalize server address: ensure it has a protocol prefix
// Accepts: IP, http://IP, https://IP, domain, http://domain, https://domain
std::string normalize_server_address(const std::string& address) {
    std::string result = address;

    // Trim whitespace
    while (!result.empty() && std::isspace(static_cast<unsigned char>(result.front()))) {
        result.erase(result.begin());
    }
    while (!result.empty() && std::isspace(static_cast<unsigned char>(result.back()))) {
        result.pop_back();
    }

    // Remove trailing slash
    if (!result.empty() && result.back() == '/') {
        result.pop_back();
    }

    // Check if protocol is already present
    std::string lower = result;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (lower.find("http://") != 0 && lower.find("https://") != 0) {
        // No protocol specified, default to http:// for development flexibility
        result = "http://" + result;
    }

    return result;
}

// RAII wrapper for CURL handle
class CurlHandle {
public:
    CurlHandle() noexcept : handle_(curl_easy_init()) {}
    ~CurlHandle() {
        if (handle_ != nullptr) {
            curl_easy_cleanup(handle_);
        }
    }

    CurlHandle(const CurlHandle&) = delete;
    CurlHandle& operator=(const CurlHandle&) = delete;

    CURL* get() noexcept { return handle_; }
    explicit operator bool() const noexcept { return handle_ != nullptr; }

private:
    CURL* handle_ = nullptr;
};

// RAII wrapper for curl_slist
class CurlHeaders {
public:
    CurlHeaders() noexcept = default;
    ~CurlHeaders() {
        if (headers_ != nullptr) {
            curl_slist_free_all(headers_);
        }
    }

    CurlHeaders(const CurlHeaders&) = delete;
    CurlHeaders& operator=(const CurlHeaders&) = delete;

    void append(const char* header) {
        headers_ = curl_slist_append(headers_, header);
    }

    struct curl_slist* get() noexcept { return headers_; }

private:
    struct curl_slist* headers_ = nullptr;
};

// Configure curl for flexible development use
void configure_curl_options(CURL* curl) {
    // Disable SSL certificate verification for development
    // This allows self-signed certs and localhost testing
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    // Follow redirects
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Timeouts
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
}

} // anonymous namespace

namespace http {

AuthResult login(const std::string& server_address,
                 const std::string& username,
                 const std::string& password) noexcept {
    AuthResult result;

    CurlHandle curl;
    if (!curl) {
        result.error = AuthError{0, "Failed to initialize HTTP client"};
        return result;
    }

    // Normalize and build URL
    std::string base_url = normalize_server_address(server_address);
    std::string url = base_url + "/login";

    // Build JSON body
    nlohmann::json body;
    body["username"] = username;
    body["password"] = password;
    std::string body_str = body.dump();

    // Setup headers
    CurlHeaders headers;
    headers.append("Content-Type: application/json");

    // Response buffer
    std::string response_body;

    // Configure curl
    configure_curl_options(curl.get());
    curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl.get(), CURLOPT_POST, 1L);
    curl_easy_setopt(curl.get(), CURLOPT_POSTFIELDS, body_str.c_str());
    curl_easy_setopt(curl.get(), CURLOPT_HTTPHEADER, headers.get());
    curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &response_body);

    // Perform request
    CURLcode res = curl_easy_perform(curl.get());

    if (res != CURLE_OK) {
        std::string error_msg = "Connection failed: ";
        error_msg += curl_easy_strerror(res);
        result.error = AuthError{0, error_msg};
        return result;
    }

    // Get response code
    long http_code = 0;
    curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &http_code);

    if (http_code == 200) {
        try {
            auto json = nlohmann::json::parse(response_body);
            AuthResponse auth;
            auth.access_token = json.at("access_token").get<std::string>();
            auth.token_type = json.value("token_type", "bearer");
            result.response = auth;
        } catch (const std::exception& e) {
            result.error = AuthError{static_cast<int>(http_code), "Invalid response from server"};
        }
    } else if (http_code == 401) {
        result.error = AuthError{401, "Invalid username or password"};
    } else {
        // Try to extract error detail from response
        std::string error_msg = "HTTP " + std::to_string(http_code);
        try {
            auto json = nlohmann::json::parse(response_body);
            if (json.contains("detail")) {
                error_msg += ": " + json["detail"].get<std::string>();
            }
        } catch (...) {
            if (!response_body.empty()) {
                // Show first part of response for debugging
                error_msg += ": " + response_body.substr(0, 100);
            }
        }
        result.error = AuthError{static_cast<int>(http_code), error_msg};
    }

    return result;
}

bool validate_token(const std::string& server_address,
                    const std::string& token) noexcept {
    CurlHandle curl;
    if (!curl) {
        return false;
    }

    // Normalize and build URL
    std::string base_url = normalize_server_address(server_address);
    std::string url = base_url + "/me";

    // Setup headers
    CurlHeaders headers;
    headers.append("Content-Type: application/json");
    std::string auth_header = "Authorization: Bearer " + token;
    headers.append(auth_header.c_str());

    // Response buffer
    std::string response_body;

    // Configure curl
    configure_curl_options(curl.get());
    curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl.get(), CURLOPT_HTTPHEADER, headers.get());
    curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &response_body);

    // Perform request
    CURLcode res = curl_easy_perform(curl.get());

    if (res != CURLE_OK) {
        return false;
    }

    long http_code = 0;
    curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &http_code);

    return http_code == 200;
}

} // namespace http
