#include "EvalFnLeftCheckersDiffAndMorris.hpp"

namespace model {
namespace ai {

EvalFnLeftCheckersDiffAndMorris::EvalFnLeftCheckersDiffAndMorris()
    : EvalFunction("Left checkers diff and morris")
{
}

EvalFnLeftCheckersDiffAndMorris::~EvalFnLeftCheckersDiffAndMorris() = default;
EvalFnLeftCheckersDiffAndMorris::EvalFnLeftCheckersDiffAndMorris(const EvalFnLeftCheckersDiffAndMorris&) = default;
EvalFnLeftCheckersDiffAndMorris &EvalFnLeftCheckersDiffAndMorris::operator=(const EvalFnLeftCheckersDiffAndMorris&) = default;
EvalFnLeftCheckersDiffAndMorris::EvalFnLeftCheckersDiffAndMorris(EvalFnLeftCheckersDiffAndMorris&&) = default;
EvalFnLeftCheckersDiffAndMorris &EvalFnLeftCheckersDiffAndMorris::operator=(EvalFnLeftCheckersDiffAndMorris&&) = default;

int EvalFnLeftCheckersDiffAndMorris::evalGameState(const model::GameState &gameState, const model::PlayerColor who)
{
    int score = 2 * gameState.getLeftCheckersOnBoard(who) - 3 * gameState.getLeftCheckersOnBoard(getOponent(who));
    bool millInLastMove = gameState.lastMoveCreatedMill();
    if(millInLastMove)
    {
        const auto& lastMove = gameState.getLastMove();
        if(lastMove.who == who)
            score++;
        else
            score--;
    }
    return score;
}

} // namespace ai
} // namespace model
