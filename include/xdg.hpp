#ifndef XDG_HPP
#define XDG_HPP

#include <string>

namespace xdg {

// Get the application XDG path given a base directory.
// Return <base>/APP_NAME
std::string xdg_path(const std::string &base);

// Get XDG config directory for verses-tui
// Returns $XDG_CONFIG_HOME/APP_NAME or ~/.config/APP_NAME
std::string config_dir() noexcept;

// Get XDG cache directory for verses-tui
// Returns $XDG_CACHE_HOME/APP_NAME or ~/.cache/APP_NAME
std::string cache_dir() noexcept;

// Ensure directories exist, create if needed
// Returns true on success
bool ensure_directories() noexcept;

// Get path to config file
std::string config_file_path() noexcept;

// Get path to token file
std::string token_file_path() noexcept;

} // namespace xdg

#endif // XDG_HPP
