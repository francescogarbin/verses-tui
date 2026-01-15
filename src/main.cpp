#include "xdg.hpp"
#include "config.hpp"
#include "token_cache.hpp"
#include "http_client.hpp"
#include "login_window.hpp"
#include "message_dialog.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

// Nord color palette
namespace nord {
    const Color bg = Color::RGB(46, 52, 64);       // nord0
    const Color fg = Color::RGB(236, 239, 244);   // nord6
    const Color frost = Color::RGB(136, 192, 208); // nord8
    const Color green = Color::RGB(163, 190, 140); // nord14
}

int main() {
    // Ensure XDG directories exist
    if (!xdg::ensure_directories()) {
        std::cerr << "Failed to create config/cache directories\n";
        return 1;
    }

    // Load configuration
    Config config = Config::load();

    // Application state
    std::string auth_token;
    bool show_error_dialog = false;
    std::string error_message;
    bool logged_in = false;

    // Try to load cached token
    auto cached_token = token_cache::load();
    if (cached_token.has_value() && !config.server_address.empty()) {
        // Validate cached token
        if (http::validate_token(config.server_address, *cached_token)) {
            auth_token = *cached_token;
            logged_in = true;
        }
    }

    // Create screen
    auto screen = ScreenInteractive::Fullscreen();

    // Login callbacks
    auto on_login_success = [&](const std::string& token) {
        auth_token = token;
        token_cache::save(token);
        logged_in = true;
        screen.Post(Event::Custom);
    };

    auto on_login_error = [&](const std::string& msg) {
        error_message = msg;
        show_error_dialog = true;
        screen.Post(Event::Custom);
    };

    auto close_error_dialog = [&]() {
        show_error_dialog = false;
        screen.Post(Event::Custom);
    };

    // Create components
    auto login = LoginWindow(config.server_address, on_login_success, on_login_error);
    auto error_dialog = MessageDialog(error_message, close_error_dialog);

    // Logged-in placeholder (will be replaced with main TUI in future sprints)
    auto logged_in_view = Renderer([&] {
        return vbox({
            text("Verses TUI") | bold | color(nord::frost) | center,
            text("") | center,
            text("Successfully logged in!") | color(nord::green) | center,
            text("") | center,
            text("Token: " + auth_token.substr(0, 20) + "...") | dim | center,
            text("") | center,
            text("Press 'q' to quit") | dim | center,
        }) | center | border | bgcolor(nord::bg);
    }) | CatchEvent([&](Event event) {
        if (event == Event::Character('q') || event == Event::Character('Q')) {
            screen.Exit();
            return true;
        }
        return false;
    });

    // Main renderer with modal support
    auto main_component = Renderer([&] {
        Element base;

        if (logged_in) {
            base = logged_in_view->Render();
        } else {
            base = login->Render();
        }

        if (show_error_dialog) {
            // Re-create dialog with current message for rendering
            auto dialog_element = vbox({
                text("Error") | bold | color(Color::RGB(191, 97, 106)),
                separator(),
                text(error_message) | color(nord::fg),
                filler(),
                text("Press ENTER or ESC to close") | dim | center,
            }) | border | bgcolor(nord::bg) | size(WIDTH, GREATER_THAN, 40) | size(HEIGHT, GREATER_THAN, 6) | center;

            base = dbox({
                base,
                dialog_element | clear_under | center,
            });
        }

        return base;
    }) | CatchEvent([&](Event event) {
        // Handle error dialog events first
        if (show_error_dialog) {
            if (event == Event::Return || event == Event::Escape) {
                close_error_dialog();
                return true;
            }
            return true; // Consume all events when dialog is shown
        }

        // Pass events to appropriate component
        if (logged_in) {
            return logged_in_view->OnEvent(event);
        } else {
            return login->OnEvent(event);
        }
    });

    screen.Loop(main_component);

    return 0;
}
