#pragma once

#include <stdexcept>
#include <string>

namespace model {

class ActionTypeMismatchException : public std::runtime_error
{
public:
    ActionTypeMismatchException(const std::string& msg);
};

} // namespace model
