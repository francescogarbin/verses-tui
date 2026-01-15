#ifndef TOKEN_CACHE_HPP
#define TOKEN_CACHE_HPP

#include <string>
#include <optional>

namespace token_cache {

// Save token to cache file
bool save(const std::string& token) noexcept;

// Load token from cache file
std::optional<std::string> load() noexcept;

// Clear cached token
bool clear() noexcept;

} // namespace token_cache

#endif // TOKEN_CACHE_HPP
