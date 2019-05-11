#pragma once

#include "LoggingPolicy.hpp"

class MainWindow;

namespace tools {

class GuiLogBoxLoggingPolicy : public LoggingPolicy
{
public:
    GuiLogBoxLoggingPolicy(MainWindow& window);
    virtual ~GuiLogBoxLoggingPolicy() override;

    GuiLogBoxLoggingPolicy() = delete;
    GuiLogBoxLoggingPolicy(const GuiLogBoxLoggingPolicy&) = delete;
    GuiLogBoxLoggingPolicy& operator=(const GuiLogBoxLoggingPolicy&) = delete;
    GuiLogBoxLoggingPolicy(GuiLogBoxLoggingPolicy&&) = delete;
    GuiLogBoxLoggingPolicy& operator=(GuiLogBoxLoggingPolicy&&) = delete;

    virtual void log(const char* buffer) override;

private:
    MainWindow& window;
};

} // namespace tools
