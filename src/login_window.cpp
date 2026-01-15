#include "login_window.hpp"
#include "http_client.hpp"
#include "config.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>

using namespace ftxui;

// Nord color palette
namespace nord {
    const Color bg = Color::RGB(46, 52, 64);          // nord0
    const Color fg = Color::RGB(216, 222, 233);       // nord5
    const Color frost = Color::RGB(136, 192, 208);    // nord8
}

ftxui::Component LoginWindow(
    const std::string& initial_server,
    LoginCallback on_login,
    ErrorCallback on_error
) {
    // State
    auto server = std::make_shared<std::string>(initial_server);
    auto username = std::make_shared<std::string>();
    auto password = std::make_shared<std::string>();
    auto is_loading = std::make_shared<bool>(false);

    // Input options
    InputOption server_opt;
    InputOption username_opt;
    InputOption password_opt;
    password_opt.password = true;

    // Create input components
    auto server_input = Input(server.get(), server_opt);
    auto username_input = Input(username.get(), username_opt);
    auto password_input = Input(password.get(), password_opt);

    // Container for TAB navigation
    auto inputs = Container::Vertical({
        server_input,
        username_input,
        password_input,
    });

    // Main component with rendering
    return Renderer(inputs, [=] {
        // Header box with title and tagline
        auto header = window(
            text(""),
            vbox({
                text("Verses") | bold | center,
                text("Code is poetry, servers host verses") | center,
            })
        ) | color(nord::frost);

        // Input fields with window-style borders (label in top border)
        auto server_field = window(
            text("Server address:") | color(nord::frost),
            server_input->Render()
        ) | color(nord::frost);

        auto username_field = window(
            text("Username:") | color(nord::frost),
            username_input->Render()
        ) | color(nord::frost);

        auto password_field = window(
            text("Password:") | color(nord::frost),
            password_input->Render()
        ) | color(nord::frost);

        // Version text
        auto version = text("v.1.0") | dim | center;

        // Main dialog content
        auto dialog = vbox({
            header,
            text(""),
            server_field,
            text(""),
            username_field,
            text(""),
            password_field,
            text(""),
            (*is_loading
                ? text("Authenticating...") | color(nord::frost) | center
                : text("")),
            filler(),
            version,
        }) | size(WIDTH, EQUAL, 50) | bgcolor(nord::bg);

        return vbox({
            filler(),
            hbox({
                filler(),
                dialog,
                filler(),
            }),
            filler(),
        });
    }) | CatchEvent([=](Event event) {
        if (event == Event::Return && !*is_loading) {
            if (server->empty()) {
                on_error("Server address is required");
                return true;
            }
            if (username->empty()) {
                on_error("Username is required");
                return true;
            }
            if (password->empty()) {
                on_error("Password is required");
                return true;
            }

            *is_loading = true;

            auto result = http::login(*server, *username, *password);

            *is_loading = false;

            if (result.is_success()) {
                Config config;
                config.server_address = *server;
                config.save();
                on_login(result.response->access_token);
            } else {
                on_error(result.error->message);
            }

            return true;
        }
        return false;
    });
}
