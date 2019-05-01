#include "UnsupportedActionType.hpp"

namespace model {

UnsupportedActionType::UnsupportedActionType(const std::string& msg)
    : std::runtime_error(msg)
{
}

} // namespace model
