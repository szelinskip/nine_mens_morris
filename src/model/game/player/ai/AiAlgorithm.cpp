#include "AiAlgorithm.hpp"

namespace model {
namespace ai {

using namespace std::chrono_literals;

AiAlgorithm::AiAlgorithm(const std::string& name,
                         const PlayerColor who,
                         std::unique_ptr<EvalFunction>&& evalFn,
                         const std::chrono::seconds searchTimeLimit)
    : name(name)
    , who(who)
    , evalFn(std::move(evalFn))
    , visitedStates(0)
    , prunedStates(0)
    , searchTimeLimit(searchTimeLimit)
    , timeConstraintExceeded(false)
{
}

AiAlgorithm::~AiAlgorithm() = default;
AiAlgorithm::AiAlgorithm(AiAlgorithm &&) = default;
AiAlgorithm &AiAlgorithm::operator=(AiAlgorithm &&) = default;

uint64_t AiAlgorithm::getVisitedStates() const
{
    return visitedStates;
}

uint64_t AiAlgorithm::getPrunedStates() const
{
    return prunedStates;
}

bool AiAlgorithm::wasSearchTimeExceeded() const
{
    return timeConstraintExceeded;
}

std::string AiAlgorithm::getInfo() const
{
    return name + ", eval fn: " + evalFn->getInfo();
}

bool AiAlgorithm::checkTimeConstraint()
{
    if(searchTimeLimit != 0s && SteadyClock::now() - startAlgTp > searchTimeLimit)
    {
        timeConstraintExceeded = true;
        return true;
    }
    else
        return false;
}

} // namespace ai
} // namespace model
