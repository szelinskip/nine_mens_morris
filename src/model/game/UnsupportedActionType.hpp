#pragma once

#include <stdexcept>
#include <string>

namespace model {

class UnsupportedActionType : public std::runtime_error
{
public:
    UnsupportedActionType(const std::string& msg);
};

} // namespace model
