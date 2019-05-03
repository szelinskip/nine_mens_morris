#pragma once

#include <string>

#include "LoggingPolicy.hpp"

namespace tools {

class ConsoleLoggingPolicy : public LoggingPolicy
{
public:
    virtual void log(const char* buffer) override;
};

} // namespace tools
