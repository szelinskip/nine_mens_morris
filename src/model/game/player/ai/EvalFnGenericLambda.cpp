#include "EvalFnGenericLambda.hpp"

namespace model {
namespace ai {

EvalFnGenericLambda::EvalFnGenericLambda(const std::function<int (const GameState &, const PlayerColor)>& evalFn,
                                         const std::string& info)
    : EvalFunction(info)
    , evalFn(evalFn)
{
}

EvalFnGenericLambda::~EvalFnGenericLambda() = default;
EvalFnGenericLambda::EvalFnGenericLambda(const EvalFnGenericLambda &) = default;
EvalFnGenericLambda &EvalFnGenericLambda::operator=(const EvalFnGenericLambda &) = default;
EvalFnGenericLambda::EvalFnGenericLambda(EvalFnGenericLambda &&) = default;
EvalFnGenericLambda &EvalFnGenericLambda::operator=(EvalFnGenericLambda &&) = default;

int EvalFnGenericLambda::evalGameState(const GameState &gameState, const PlayerColor who)
{
    return evalFn(gameState, who);
}

} // namespace ai
} // namespace model
