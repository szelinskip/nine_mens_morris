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
    int LeftcheckersDiffPart = gameState.getLeftCheckersOnBoard(who) - gameState.getLeftCheckersOnBoard(getOponent(who));

    bool millInLastMove = gameState.lastMoveCreatedMill();
    int millInLastMovePart = 0;
    if(millInLastMove)
    {
        const auto& lastMove = gameState.getLastMove();
        if(lastMove.who == who)
            millInLastMovePart = 1;
        else
            millInLastMovePart = -1;
    }

    bool isGameOverMove = gameState.isGameOverState();
    int gameOverPart = 0;
    if(isGameOverMove)
    {
        PlayerColor winner = gameState.whoIsWinnerIfGameOver();
        if(winner == who)
            gameOverPart = 1;
        else
            gameOverPart = -1;
    }

    return
        7 * LeftcheckersDiffPart
        + 20 * millInLastMovePart
        + 1000 * gameOverPart;
}

} // namespace ai
} // namespace model
