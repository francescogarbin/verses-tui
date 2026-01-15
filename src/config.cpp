#include "config.hpp"
#include "xdg.hpp"
#include <toml++/toml.hpp>
#include <fstream>

Config Config::load() noexcept {
    Config config;
    config.server_address = "https://";

    try {
        auto tbl = toml::parse_file(xdg::config_file_path());

        if (auto server = tbl["server"]["address"].value<std::string>()) {
            config.server_address = *server;
        }
    } catch (...) {
        // File doesn't exist or is invalid, use defaults
    }

    return config;
}

bool Config::save() const noexcept {
    try {
        toml::table tbl;
        tbl.insert("server", toml::table{
            {"address", server_address}
        });

        std::ofstream file(xdg::config_file_path());
        if (!file) {
            return false;
        }

        file << tbl;
        return file.good();
    } catch (...) {
        return false;
    }
}
