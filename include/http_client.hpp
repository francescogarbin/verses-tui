#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

#include <string>
#include <optional>

struct AuthResponse {
    std::string access_token;
    std::string token_type;
};

struct AuthError {
    int status_code;
    std::string message;
};

// Result type for authentication
struct AuthResult {
    std::optional<AuthResponse> response;
    std::optional<AuthError> error;

    bool is_success() const noexcept { return response.has_value(); }
};

namespace http {

// Perform login request
// server_address: Base URL (e.g., "https://verses.example.com")
// username: User's username
// password: User's password
AuthResult login(const std::string& server_address,
                 const std::string& username,
                 const std::string& password) noexcept;

// Validate token by calling /me endpoint
bool validate_token(const std::string& server_address,
                    const std::string& token) noexcept;

} // namespace http

#endif // HTTP_CLIENT_HPP
