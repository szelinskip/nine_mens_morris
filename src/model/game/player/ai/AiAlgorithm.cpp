#include "AiAlgorithm.hpp"

namespace model {
namespace ai {

AiAlgorithm::AiAlgorithm(const std::string& name, const PlayerColor who, std::unique_ptr<EvalFunction>&& evalFn)
    : name(name)
    , who(who)
    , evalFn(std::move(evalFn))
    , visitedStates(0)
    , prunedStates(0)
{
}

AiAlgorithm::~AiAlgorithm() = default;
AiAlgorithm::AiAlgorithm(AiAlgorithm &&) = default;
AiAlgorithm &AiAlgorithm::operator=(AiAlgorithm &&) = default;

uint32_t AiAlgorithm::getVisitedStates() const
{
    return visitedStates;
}

uint32_t AiAlgorithm::getPrunedStates() const
{
    return prunedStates;
}

std::string AiAlgorithm::getInfo() const
{
    return name + ", eval fn: " + evalFn->getInfo();
}

} // namespace ai
} // namespace model
