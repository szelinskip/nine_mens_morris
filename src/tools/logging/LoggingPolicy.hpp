#pragma once

namespace tools {

class LoggingPolicy
{
public:
    LoggingPolicy();
    virtual ~LoggingPolicy();

    LoggingPolicy(const LoggingPolicy&) = delete;
    LoggingPolicy& operator=(const LoggingPolicy&) = delete;
    LoggingPolicy(LoggingPolicy&&) = delete;
    LoggingPolicy& operator=(LoggingPolicy&&) = delete;

    virtual void log(const char* buffer) = 0;
};

} // namespace tools
