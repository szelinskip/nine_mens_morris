#include "EvalFnCheckersArrangement.hpp"

namespace model {
namespace ai {

EvalFnCheckersArrangement::EvalFnCheckersArrangement()
    : EvalFunction("Checkers arrangement")
{
}

EvalFnCheckersArrangement::~EvalFnCheckersArrangement() = default;
EvalFnCheckersArrangement::EvalFnCheckersArrangement(const EvalFnCheckersArrangement&) = default;
EvalFnCheckersArrangement &EvalFnCheckersArrangement::operator=(const EvalFnCheckersArrangement&) = default;
EvalFnCheckersArrangement::EvalFnCheckersArrangement(EvalFnCheckersArrangement&&) = default;
EvalFnCheckersArrangement &EvalFnCheckersArrangement::operator=(EvalFnCheckersArrangement&&) = default;

int EvalFnCheckersArrangement::evalGameState(const model::GameState &gameState, const model::PlayerColor who)
{
    int numOfMorrisesPart = gameState.getPlayerNumOfMorrises(who) - gameState.getPlayerNumOfMorrises(getOponent(who));
    int numOf1ToMorrisPart = gameState.getPlayerNumOf1ToMorrisCombinations(who) - gameState.getPlayerNumOf1ToMorrisCombinations(getOponent(who));
    int leftCheckersPart = gameState.getLeftCheckersOnBoard(who) - gameState.getLeftCheckersOnBoard(getOponent(who));
    int blockedCheckersNumPart = gameState.getNumOfBlockedCheckers(getOponent(who)) - gameState.getNumOfBlockedCheckers(who);

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

    bool lastMoveBlockedMill = gameState.lastMoveBlockedMill();
    int lastMoveBlockedMillPart = 0;
    if(lastMoveBlockedMill)
    {
        const auto& lastMove = gameState.getLastMove();
        if(lastMove.who == who)
            lastMoveBlockedMillPart = 1;
        else
            lastMoveBlockedMillPart = -1;
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

    return 14 * millInLastMovePart
           + 43 * numOfMorrisesPart
           + 10 * blockedCheckersNumPart
           + 8 * numOf1ToMorrisPart
           + 11 * leftCheckersPart
           + 5 * lastMoveBlockedMillPart
           + 1086 * gameOverPart;
}

} // namespace ai
} // namespace model
