#ifndef LOGIN_WINDOW_HPP
#define LOGIN_WINDOW_HPP

#include <string>
#include <functional>
#include <ftxui/component/component.hpp>

// Callback type for successful login
using LoginCallback = std::function<void(const std::string& token)>;

// Callback type for errors
using ErrorCallback = std::function<void(const std::string& message)>;

// Create the login window component
// initial_server: Pre-filled server address from config
// on_login: Called when login succeeds with the auth token
// on_error: Called when login fails with error message
ftxui::Component LoginWindow(
    const std::string& initial_server,
    LoginCallback on_login,
    ErrorCallback on_error
);

#endif // LOGIN_WINDOW_HPP
