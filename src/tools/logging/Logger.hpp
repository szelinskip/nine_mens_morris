#pragma once

#include <string>
#include <memory>
#include <fstream>
#include <mutex>
#include <vector>

#include "LoggingPolicy.hpp"

namespace tools {

using LoggingPolicyPtr = std::unique_ptr<LoggingPolicy>;

class Logger
{
public:
    Logger(LoggingPolicyPtr&& policy);
    ~Logger();

    Logger() = delete;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    Logger& addLoggingPolicy(LoggingPolicyPtr&& policy);

    template<class... Args>
    void log(const char* format, Args... args);

private:
    std::mutex logMutex;
    std::vector<LoggingPolicyPtr> loggingPolicies;
};

template<class... Args>
void Logger::log(const char* format, Args... args)
{
    std::lock_guard<std::mutex> lock(logMutex);
    char buffer[400];
    std::snprintf(buffer, sizeof(buffer), format, args...);
    for(auto& policy : loggingPolicies)
        policy->log(buffer);
}

} // namespace tools
