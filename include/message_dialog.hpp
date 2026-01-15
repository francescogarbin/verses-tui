#ifndef MESSAGE_DIALOG_HPP
#define MESSAGE_DIALOG_HPP

#include <string>
#include <functional>
#include <ftxui/component/component.hpp>

// Create a message dialog overlay
// message: The message to display
// on_close: Called when dialog is dismissed (ESC or RETURN)
ftxui::Component MessageDialog(
    const std::string& message,
    std::function<void()> on_close
);

#endif // MESSAGE_DIALOG_HPP
