#include "xdg.hpp"
#include <cstdlib>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>

namespace {

std::string get_home_dir() noexcept {
    const char* home = std::getenv("HOME");
    if (home != nullptr) {
        return home;
    }

    // Fallback to passwd entry
    struct passwd* pw = getpwuid(getuid());
    if (pw != nullptr) {
        return pw->pw_dir;
    }

    return "";
}

bool create_directory(const std::string& path) noexcept {
    struct stat st;
    if (stat(path.c_str(), &st) == 0) {
        return S_ISDIR(st.st_mode);
    }
    return mkdir(path.c_str(), 0700) == 0;
}

bool create_directory_recursive(const std::string& path) noexcept {
    std::string current;
    for (char c : path) {
        current += c;
        if (c == '/') {
            if (!current.empty() && current != "/") {
                if (!create_directory(current)) {
                    return false;
                }
            }
        }
    }
    return create_directory(path);
}

} // anonymous namespace

namespace xdg {

std::string config_dir() noexcept {
    const char* xdg_config = std::getenv("XDG_CONFIG_HOME");
    std::string base;

    if (xdg_config != nullptr && xdg_config[0] != '\0') {
        base = xdg_config;
    } else {
        base = get_home_dir() + "/.config";
    }

    return base + "/verses-tui";
}

std::string cache_dir() noexcept {
    const char* xdg_cache = std::getenv("XDG_CACHE_HOME");
    std::string base;

    if (xdg_cache != nullptr && xdg_cache[0] != '\0') {
        base = xdg_cache;
    } else {
        base = get_home_dir() + "/.cache";
    }

    return base + "/verses-tui";
}

bool ensure_directories() noexcept {
    return create_directory_recursive(config_dir()) &&
           create_directory_recursive(cache_dir());
}

std::string config_file_path() noexcept {
    return config_dir() + "/config.toml";
}

std::string token_file_path() noexcept {
    return cache_dir() + "/token";
}

} // namespace xdg
