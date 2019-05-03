#include "EvalFnLeftCheckersDiff.hpp"

namespace model {
namespace ai {

int EvalFnLeftCheckersDiff::evalGameState(const model::GameState &gameState, const model::PlayerColor who)
{
    return 2 * gameState.getLeftCheckersOnBoard(who) - 3 * gameState.getLeftCheckersOnBoard(getOponent(who));
}

} // namespace ai
} // namespace model
