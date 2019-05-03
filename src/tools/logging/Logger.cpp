#include "Logger.hpp"

namespace tools {

Logger::Logger(LoggingPolicyPtr&& policy)
{
    loggingPolicies.push_back(std::move(policy));
}

Logger::~Logger() = default;

Logger& Logger::addLoggingPolicy(LoggingPolicyPtr&& policy)
{
    loggingPolicies.push_back(std::move(policy));
    return *this;
}

} // namespace tools
