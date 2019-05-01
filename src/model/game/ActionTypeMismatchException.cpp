#include "ActionTypeMismatchException.hpp"

namespace model {

ActionTypeMismatchException::ActionTypeMismatchException(const std::string& msg)
    : std::runtime_error(msg)
{
}

} // namespace model
