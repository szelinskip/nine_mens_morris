#pragma once

#include <cstring>
#include <chrono>
#include <ctime>
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
    char buffer[600];
    std::time_t currTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm* time = std::localtime(&currTime);
    constexpr uint32_t bufferTimeSize = 9;
    char bufferTime[bufferTimeSize];
    std::strftime(bufferTime, sizeof(bufferTime), "%H:%M:%S", time);
    std::strcpy(buffer, bufferTime);
    buffer[bufferTimeSize - 1] = ' ';
    std::snprintf(buffer + bufferTimeSize, sizeof(buffer) - bufferTimeSize, format, args...);
    for(auto& policy : loggingPolicies)
        policy->log(buffer);
}

} // namespace tools
