#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

struct Config {
    std::string server_address;

    // Load config from TOML file, returns default config if file doesn't exist
    static Config load() noexcept;

    // Save config to TOML file
    bool save() const noexcept;
};

#endif // CONFIG_HPP
