#include "NineMensMorris.hpp"

#include "player/Player.hpp"
#include <src/model/game/GameManager.hpp>

#include <algorithm>
#include <iostream>

#include <src/tools/logging/FileLoggingPolicy.hpp>

namespace model {

NineMensMorris::NineMensMorris(std::unique_ptr<Player> whitePlayer,
                               std::unique_ptr<Player> blackPlayer,
                               GameManager* gameManager,
                               tools::Logger& logger)
    : whitePlayer(std::move(whitePlayer))
    , blackPlayer(std::move(blackPlayer))
    , currentPlayer(nullptr)
    , gameManager(gameManager)
    , turnNum(0)
    , logger(logger)
    , gameMovesLogger(std::make_unique<tools::FileLoggingPolicy>("game_moves_log", true))
    , gameStatesLogger(std::make_unique<tools::FileLoggingPolicy>("game_states_log", true))
{
    gameMovesLogger.log("%s(): White player info: %s", __FUNCTION__, this->whitePlayer->getInfo().c_str());
    gameMovesLogger.log("%s(): Black player info: %s", __FUNCTION__, this->blackPlayer->getInfo().c_str());
    gameStatesLogger.log("%s(): White player info: %s", __FUNCTION__, this->whitePlayer->getInfo().c_str());
    gameStatesLogger.log("%s(): Black player info: %s", __FUNCTION__, this->blackPlayer->getInfo().c_str());
}

NineMensMorris::~NineMensMorris() = default;

void NineMensMorris::startGame()
{
    logger.log("%s()", __FUNCTION__);
    bool gameOver = false;
    Player* winner = nullptr;
    auto gameStartTp = std::chrono::steady_clock::now();
    while(!gameOver && !gameManager->shouldStopGame())
    {
        turnNum++;
        gameManager->beforeTurnActions(turnNum,
                                       gameState.getWhiteLeftCheckersToPut(),
                                       gameState.getBlackLeftCheckersToPut(),
                                       gameState.getWhiteLeftCheckersOnBoard(),
                                       gameState.getBlackLeftCheckersOnBoard(),
                                       gameState.getWhiteCheckersKilledByBlack(),
                                       gameState.getBlackCheckersKilledByWhite());
        std::chrono::milliseconds elapsed;
        if(!checkGameOverCondition())
        {
            logger.log("%s(): game over condition FALSE", __FUNCTION__);
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
            currentPlayer->incrementMovesNumber();
            std::chrono::time_point moveDoneTp = std::chrono::steady_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(moveDoneTp - startMoveTp);
            const auto& lastMove = gameState.getLastMove();
            gameMovesLogger.log("Turn no: %u, Who: %12s, this player move no: %u, from field: %2s, "
                                "to field: %2s, oponent's checker taken: %2s, turn time: %.3f [s], "
                                "visited states: %d, pruned states: %d",
                                turnNum,
                                currentPlayer->getName().c_str(),
                                currentPlayer->getMovesNumber(),
                                lastMove.fromField.c_str(),
                                lastMove.toField.c_str(),
                                lastMove.fieldOponentsCheckerTaken.c_str(),
                                elapsed.count() / 1000.0,
                                currentPlayer->getVisitedStates(),
                                currentPlayer->getPrunedStates());
            gameStatesLogger.log("Turn no: %u, Who: %12s, this player move no: %u, from field: %2s, "
                                 "to field: %2s, oponent's checker taken: %2s, turn time: %.3f [s], "
                                 "visited states: %d, pruned states: %d, game state:\n%s",
                                 turnNum,
                                 currentPlayer->getName().c_str(),
                                 currentPlayer->getMovesNumber(),
                                 lastMove.fromField.c_str(),
                                 lastMove.toField.c_str(),
                                 lastMove.fieldOponentsCheckerTaken.c_str(),
                                 elapsed.count() / 1000.0,
                                 currentPlayer->getVisitedStates(),
                                 currentPlayer->getPrunedStates(),
                                 gameState.getStrRepr().c_str());
            gameStatesHistory.emplace_back(gameState);
        }
        else
        {
            logger.log("%s(): game over condition TRUE", __FUNCTION__);
            gameOver = true;
            if(!isGameEndedWithDraw())
            {

                if(!gameState.isGameOverDueToNoPossibleMovements())
                    winner = currentPlayer;
                else
                    winner = getCurrentPlayer();
            }
        }
        gameManager->afterTurnActions(elapsed, gameState.getLastMove());
    }
    if(gameOver)
        gameManager->gameFinishedActions(winner);
    auto gameEndTp = std::chrono::steady_clock::now();
    auto gameTimeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(gameEndTp - gameStartTp);
    std::string winnerStr = "DRAW";
    if(winner != nullptr)
        winnerStr = winner->getName();
    gameMovesLogger.log("%s(): winner: %s, total game time elapsed: %.3f [s]",
                        __FUNCTION__,
                        winnerStr.c_str(),
                        gameTimeElapsed.count() / 1000.0);
    gameStatesLogger.log("%s(): winner: %s, total game time elapsed: %.3f [s]",
                         __FUNCTION__,
                         winnerStr.c_str(),
                         gameTimeElapsed.count() / 1000.0);
}

bool NineMensMorris::checkGameOverCondition() const
{
    bool checkersCondition = gameState.isGameOverState();
    if(checkersCondition)
    {
        logger.log("%s(): checkers game over condition", __FUNCTION__);
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
            logger.log("%s(): state repeated 3 times", __FUNCTION__);
        else
            logger.log("%s(): state NOT repeated 3 times, just %d", __FUNCTION__, stateRepetitionsInPast);
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
