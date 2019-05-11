#include "NineMensMorris.hpp"

#include "player/Player.hpp"
#include "GameManager.hpp"

#include <algorithm>
#include <iostream>

namespace model {

NineMensMorris::NineMensMorris(std::unique_ptr<Player> whitePlayer, std::unique_ptr<Player> blackPlayer, GameManager* gameManager)
    : whitePlayer(std::move(whitePlayer))
    , blackPlayer(std::move(blackPlayer))
    , currentPlayer(nullptr)
    , gameManager(gameManager)
{
}

NineMensMorris::~NineMensMorris() = default;

void NineMensMorris::startGame()
{
    std::cout << __FUNCTION__ << std::endl;
    bool gameOver = false;
    Player* winner = nullptr;
    while(!gameOver && !gameManager->shouldStopGame())
    {
        gameManager->beforeTurnActions(gameState.getWhiteLeftCheckersToPut(),
                                       gameState.getBlackLeftCheckersToPut(),
                                       gameState.getWhiteLeftCheckersOnBoard(),
                                       gameState.getBlackLeftCheckersOnBoard(),
                                       gameState.getWhiteCheckersKilledByBlack(),
                                       gameState.getBlackCheckersKilledByWhite());
        std::chrono::milliseconds elapsed;
        if(!checkGameOverCondition())
        {
            std::cout << "game over condition FALSE" << std::endl;
            currentPlayer = getCurrentPlayer();
            gameManager->playersTurnAction(currentPlayer);
            std::chrono::time_point startMoveTp = std::chrono::steady_clock::now();
            bool moveValid = currentPlayer->makeMove(gameState);
            if(!moveValid)
                continue;
            if(lastMoveCreatedMill())
            {
               /* bool millMoveValid = */currentPlayer->millMove(gameState);
            }
            std::chrono::time_point moveDoneTp = std::chrono::steady_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(moveDoneTp - startMoveTp);
            gameStatesHistory.emplace_back(gameState);
        }
        else
        {
            std::cout << "game over condition TRUE" << std::endl;
            gameOver = true;
            if(!isGameEndedWithDraw())
                winner = currentPlayer;
        }
        gameManager->afterTurnActions(elapsed, gameState.getLastMove());
    }
    gameManager->gameFinishedActions(winner);
}

bool NineMensMorris::checkGameOverCondition() const
{
    bool checkersCondition = gameState.isGameOverState();
    if(checkersCondition)
    {
        std::cout << "checkers game over condition" << std::endl;
        return true;
    }
    else
    {
        auto stateRepetitionsInPast =
            std::count_if(gameStatesHistory.cbegin(),
                          gameStatesHistory.cend(),
                          [this](const auto& stateFromPast)
                          {return stateFromPast.isBoardEqual(gameState);});
        if(stateRepetitionsInPast == 3)
            std::cout << "state repeated 3 times" << std::endl;
        else
            std::cout << "state NOT repeated 3 times, just " << stateRepetitionsInPast << std::endl;
        return stateRepetitionsInPast == 3;
    }
}

Player *NineMensMorris::getCurrentPlayer() const
{
    if(currentPlayer == whitePlayer.get())
        return blackPlayer.get();
    else if(currentPlayer == blackPlayer.get())
        return whitePlayer.get();
    else  // currentPlayer == nullptr
        return whitePlayer.get();
}

bool NineMensMorris::isGameEndedWithDraw() const
{
    auto stateRepetitionsInPast =
        std::count_if(gameStatesHistory.cbegin(),
                      gameStatesHistory.cend(),
                      [this](const auto& stateFromPast)
                      {return stateFromPast.isBoardEqual(gameState);});
    return stateRepetitionsInPast == 3;
}

bool NineMensMorris::lastMoveCreatedMill() const
{
    return gameState.lastMoveCreatedMill();
}

} // namespace model
