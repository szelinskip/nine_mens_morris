#include "EvalFnLeftCheckersDiff.hpp"

namespace model {
namespace ai {

EvalFnLeftCheckersDiff::EvalFnLeftCheckersDiff()
    : EvalFunction("Left checkers diff")
{
}

EvalFnLeftCheckersDiff::~EvalFnLeftCheckersDiff() = default;
EvalFnLeftCheckersDiff::EvalFnLeftCheckersDiff(const EvalFnLeftCheckersDiff&) = default;
EvalFnLeftCheckersDiff &EvalFnLeftCheckersDiff::operator=(const EvalFnLeftCheckersDiff&) = default;
EvalFnLeftCheckersDiff::EvalFnLeftCheckersDiff(EvalFnLeftCheckersDiff&&) = default;
EvalFnLeftCheckersDiff &EvalFnLeftCheckersDiff::operator=(EvalFnLeftCheckersDiff&&) = default;

int EvalFnLeftCheckersDiff::evalGameState(const model::GameState &gameState, const model::PlayerColor who)
{
    return 2 * gameState.getLeftCheckersOnBoard(who) - 3 * gameState.getLeftCheckersOnBoard(getOponent(who));
}

} // namespace ai
} // namespace model
