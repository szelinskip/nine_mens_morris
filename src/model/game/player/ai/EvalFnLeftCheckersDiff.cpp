#include "EvalFnLeftCheckersDiff.hpp"

namespace model {
namespace ai {

int EvalFnLeftCheckersDiff::evalGameState(const model::GameState &gameState, const model::PlayerColor who)
{
    return gameState.getLeftCheckersOnBoard(who) - gameState.getLeftCheckersOnBoard(getOponent(who));
}

} // namespace ai
} // namespace model
