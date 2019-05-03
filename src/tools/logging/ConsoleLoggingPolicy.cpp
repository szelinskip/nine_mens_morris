#include "ConsoleLoggingPolicy.hpp"

#include <iostream>

namespace tools {

void ConsoleLoggingPolicy::log(const char* buffer)
{
    std::cout << buffer << std::endl;
}

} // namespace tools
