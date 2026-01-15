#include "message_dialog.hpp"
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

ftxui::Component MessageDialog(
    const std::string& message,
    std::function<void()> on_close
) {
    return Renderer([=]([[maybe_unused]] bool focused) {
        auto content = vbox({
            text(""),
            paragraph(message) | color(nord::fg),
            text(""),
            text("[ESC=close]") | dim | center,
        });

        auto dialog = window(
            text("Something went wrong") | color(nord::frost),
            content
        ) | color(nord::frost)
          | size(WIDTH, GREATER_THAN, 40)
          | size(WIDTH, LESS_THAN, 60)
          | bgcolor(nord::bg);

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
        if (event == Event::Return || event == Event::Escape) {
            on_close();
            return true;
        }
        return false;
    });
}
