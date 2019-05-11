#include "EvalFunction.hpp"

namespace model {
namespace ai {

EvalFunction::EvalFunction(const std::string& info)
    : info(info)
{

}

EvalFunction::~EvalFunction() = default;
EvalFunction::EvalFunction(const EvalFunction &) = default;
EvalFunction &EvalFunction::operator=(const EvalFunction &) = default;
EvalFunction::EvalFunction(EvalFunction &&) = default;
EvalFunction &EvalFunction::operator=(EvalFunction &&) = default;

std::string EvalFunction::getInfo() const
{
    return info;
}

} // namespace ai
} // namespace model
