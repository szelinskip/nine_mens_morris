#include "AiAlgorithm.hpp"

namespace model {
namespace ai {

AiAlgorithm::AiAlgorithm(const PlayerColor who, std::unique_ptr<EvalFunction>&& evalFn)
    : who(who)
    , evalFn(std::move(evalFn))
{
}

AiAlgorithm::~AiAlgorithm() = default;
AiAlgorithm::AiAlgorithm(AiAlgorithm &&) = default;
AiAlgorithm &AiAlgorithm::operator=(AiAlgorithm &&) = default;

} // namespace ai
} // namespace model
