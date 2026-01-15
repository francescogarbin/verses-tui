#ifndef XDG_HPP
#define XDG_HPP

#include <string>

namespace xdg {

// Get XDG config directory for verses-tui
// Returns $XDG_CONFIG_HOME/verses-tui or ~/.config/verses-tui
std::string config_dir() noexcept;

// Get XDG cache directory for verses-tui
// Returns $XDG_CACHE_HOME/verses-tui or ~/.cache/verses-tui
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
