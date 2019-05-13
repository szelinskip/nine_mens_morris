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
    int score = 2 * gameState.getLeftCheckersOnBoard(who) - 3 * gameState.getLeftCheckersOnBoard(getOponent(who));

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

    return score + 1000 * gameOverPart;
}

} // namespace ai
} // namespace model
