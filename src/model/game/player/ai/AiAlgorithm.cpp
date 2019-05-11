#include "AiAlgorithm.hpp"

namespace model {
namespace ai {

AiAlgorithm::AiAlgorithm(const std::string& name, const PlayerColor who, std::unique_ptr<EvalFunction>&& evalFn)
    : name(name)
    , who(who)
    , evalFn(std::move(evalFn))
{
}

std::string AiAlgorithm::getInfo() const
{
    return name + ", eval fn: " + evalFn->getInfo();
}

AiAlgorithm::~AiAlgorithm() = default;
AiAlgorithm::AiAlgorithm(AiAlgorithm &&) = default;
AiAlgorithm &AiAlgorithm::operator=(AiAlgorithm &&) = default;

} // namespace ai
} // namespace model
