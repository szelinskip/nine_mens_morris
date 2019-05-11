#include "GuiLogBoxLoggingPolicy.hpp"

#include <QMetaObject>
#include <string>

#include <src/view/MainWindow.h>

namespace tools {

GuiLogBoxLoggingPolicy::GuiLogBoxLoggingPolicy(MainWindow& window)
    : window(window)
{
}

GuiLogBoxLoggingPolicy::~GuiLogBoxLoggingPolicy() = default;

void GuiLogBoxLoggingPolicy::log(const char* buffer)
{
    std::string msg(buffer);
    QMetaObject::invokeMethod(&window, "logOnLogBox", Q_ARG(const std::string&, msg));
}

} // namespace tools
