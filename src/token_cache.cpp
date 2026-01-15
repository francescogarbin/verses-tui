#include "token_cache.hpp"
#include "xdg.hpp"
#include <fstream>
#include <sys/stat.h>

namespace token_cache {

bool save(const std::string& token) noexcept {
    try {
        std::string path = xdg::token_file_path();
        std::ofstream file(path);
        if (!file) {
            return false;
        }

        file << token;
        file.close();

        // Set restrictive permissions (owner read/write only)
        chmod(path.c_str(), 0600);

        return true;
    } catch (...) {
        return false;
    }
}

std::optional<std::string> load() noexcept {
    try {
        std::ifstream file(xdg::token_file_path());
        if (!file) {
            return std::nullopt;
        }

        std::string token;
        std::getline(file, token);

        if (token.empty()) {
            return std::nullopt;
        }

        return token;
    } catch (...) {
        return std::nullopt;
    }
}

bool clear() noexcept {
    return std::remove(xdg::token_file_path().c_str()) == 0;
}

} // namespace token_cache
