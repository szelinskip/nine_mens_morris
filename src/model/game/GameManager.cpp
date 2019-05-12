#include "GameManager.hpp"
#include "UnsupportedActionType.hpp"
#include "ActionTypeMismatchException.hpp"
#include "player/HumanPlayer.hpp"
#include "player/ComputerPlayer.hpp"
#include "player/PlayerFactory.hpp"
#include "player/PlayerInfo.hpp"
#include <src/controller/MasterController.hpp>

#include <chrono>
#include <iostream>

namespace model {

using namespace std::chrono_literals;

GameManager::GameManager(tools::Logger& logger, const bool shouldIntroducePauseBetweenPlayers)
    : pauseBetweenPlayers(500ms)
    , gameRunning(false)
    , shouldRunLoop(false)
    , waitingForInput(0)
    , inputProvided(false)
    , millMoveInputAwaiting(false)
    , shouldTerminate(false)
    , shouldStop(false)
    , shouldPause(false)
    , shouldUpdateUi(true)
    , shouldIntroducePauseBetweenPlayers(shouldIntroducePauseBetweenPlayers)
    , logger(logger)
{
}

GameManager::~GameManager()
{
    shouldRunLoop = false;
    if(gameThread.joinable())
        gameThread.join();

    if(actionsLoopThread.joinable())
        actionsLoopThread.join();
}

void GameManager::run()
{
    logger.log("%s()", __FUNCTION__);
    shouldRunLoop = true;
    actionsLoopThread = std::thread(&GameManager::runningLoop, this);
}

void GameManager::stop()
{
    logger.log("%s()", __FUNCTION__);
    // release waiting threads to join them properly
    shouldTerminate = true;
    userInputProvided.notify_all();
}

bool GameManager::shouldStopGame() const
{
    return shouldTerminate || shouldStop;
}

void GameManager::setController(controller::MasterController* controller)
{
    this->controller = controller;
}

void GameManager::putAction(ActionPtr action)
{
    if(shouldTerminate)
        return;
    logger.log("%s(), action type: %s", __FUNCTION__, actionTypeToString(action->getType()));
    std::lock_guard<std::mutex> lock(actionsQMutex);
    actionsQueue.push(std::move(action));
}

Move GameManager::getInput()
{
    logger.log("%s()", __FUNCTION__);
    std::unique_lock<std::mutex> lock(userInputMutex);
    userInputProvided.wait(lock, [this](){return inputProvided || shouldStop || shouldTerminate;});
    inputProvided = false;
    logger.log("%s(), input got %s -> %s", __FUNCTION__, userInputMove.fromField.c_str(), userInputMove.toField.c_str());
    return userInputMove;
}

void GameManager::beforeTurnActions(const uint32_t turnNum,
                                    const uint32_t whiteLeftCheckersToPut,
                                    const uint32_t blackLeftCheckersToPut,
                                    const uint32_t whiteLeftCheckersOnBoard,
                                    const uint32_t blackLeftCheckersOnBoard,
                                    const uint32_t whiteCheckersKilledByBlack,
                                    const uint32_t blackCheckersKilledByWhite)
{
    logger.log("%s()", __FUNCTION__);
    if(shouldUpdateUi)
    {
        controller->updateUI(turnNum,
                             whiteLeftCheckersToPut,
                             blackLeftCheckersToPut,
                             whiteLeftCheckersOnBoard,
                             blackLeftCheckersOnBoard,
                             whiteCheckersKilledByBlack,
                             blackCheckersKilledByWhite);
    }

    std::unique_lock<std::mutex> lock(pauseMutex);
    pauseCondition.wait(lock, [this](){return !shouldPause || shouldStop || shouldTerminate;});
}

void GameManager::afterTurnActions(std::chrono::milliseconds elapsed, const Move& lastMove)
{
    logger.log("%s()", __FUNCTION__);
    controller->updateLastMove(elapsed, lastMove);
    if(!shouldIntroducePauseBetweenPlayers)
        return;
    logger.log("%s() sleeping for: %llu ms", __FUNCTION__, pauseBetweenPlayers.count());
    std::this_thread::sleep_for(pauseBetweenPlayers);
    logger.log("%s() end sleep", __FUNCTION__);
}

void GameManager::playersTurnAction(const Player* currentPlayer)
{
    logger.log("%s()", __FUNCTION__);
    controller->updateCurrentPlayer(currentPlayer->getColor());
}

void GameManager::gameFinishedActions(const Player* winner)
{
    logger.log("%s()", __FUNCTION__);
    std::string winnerName = "DRAW";
    if(winner != nullptr)
        winnerName = winner->getName();
    controller->gameFinishedStatus(winnerName);
}

void GameManager::waitOnGameManager()
{
    if(gameThread.joinable())
        gameThread.join();

    shouldRunLoop = false;

    if(actionsLoopThread.joinable())
        actionsLoopThread.join();
}

void GameManager::waitUntilGameNotStarted()
{
    while(!gameRunning);
}

void GameManager::runningLoop()
{
    logger.log("%s()", __FUNCTION__);
    while(shouldRunLoop)
    {
        {
            std::lock_guard<std::mutex> lock(actionsQMutex);
            if(!actionsQueue.empty())
            {
                auto req = std::move(actionsQueue.front());
                actionsQueue.pop();
                try
                {
                    logger.log("%s(): passing action to handle", __FUNCTION__);
                    handleAction(std::move(req));
                }
                catch(UnsupportedActionType&)
                {
                    shouldRunLoop = false;
                    logger.log("%s(): UnsupportedActionType", __FUNCTION__);
                }
                catch(ActionTypeMismatchException&)
                {
                    shouldRunLoop = false;
                    logger.log("%s(): ActionTypeMismatchException", __FUNCTION__);
                }
            }
        }
    }
}

void GameManager::runGame(const PlayerType whitePlayerType,
                          const PlayerHeuristic whitePlayerHeuristic,
                          const uint32_t whitePlayerDepth,
                          const PlayerType blackPlayerType,
                          const PlayerHeuristic blackPlayerHeuristic,
                          const uint32_t blackPlayerDepth)
{
    logger.log("%s()", __FUNCTION__);
    gameRunning = true;

    PlayerFactory playerFactory(logger);

    auto whitePlayer = playerFactory.makePlayer(*this,
                                                "Player white",
                                                PlayerColor::White,
                                                whitePlayerType,
                                                whitePlayerHeuristic,
                                                whitePlayerDepth);

    auto blackPlayer = playerFactory.makePlayer(*this,
                                                "Player black",
                                                PlayerColor::Black,
                                                blackPlayerType,
                                                blackPlayerHeuristic,
                                                blackPlayerDepth);

    nineMensMorris = std::make_unique<NineMensMorris>(std::move(whitePlayer),
                                                      std::move(blackPlayer),
                                                      this,
                                                      logger);

    nineMensMorris->startGame();
    gameRunning = false;
    logger.log("%s() game finished", __FUNCTION__);
}

void GameManager::handleAction(ActionPtr action)
{
    logger.log("%s(), action type: %s", __FUNCTION__, actionTypeToString(action->getType()));
    ActionType type = action->getType();
    switch(type)
    {
        case ActionType::GameStart:
            handleGameStart(std::move(action));
            break;
        case ActionType::GameStop:
            handleGameStop();
            break;
        case ActionType::GamePause:
            handleGamePause();
            break;
        case ActionType::GameResume:
            handleGameResume();
            break;
        case ActionType::InputReq:
            handleInputReq(std::move(action));
            break;
        case ActionType::MoveDone:
            handleActionMoveDone(std::move(action));
            break;
        case ActionType::InputProvided:
            handleInputProvided(std::move(action));
            break;
        case ActionType::GuiOff:
            handleGuiOff();
            break;
        case ActionType::GuiOn:
            handleGuiOn();
            break;
        case ActionType::WaitOnGame:
            handleWaitOnGame();
            break;
        default:
            throw UnsupportedActionType("Type: " + std::to_string(static_cast<int>(type)));
    }
}

void GameManager::handleInputReq(ActionPtr action)
{
    logger.log("%s()", __FUNCTION__);
    auto actionInputReq = dynamic_cast<ActionInputReq*>(action.get());
    if(actionInputReq == nullptr)
        throw ActionTypeMismatchException("Type: " + std::string(actionTypeToString(action->getType())));
    std::lock_guard<std::mutex> lock(userInputMutex);
    userInputMove = Move{};
    if(!actionInputReq->isFirstStage() && !actionInputReq->isMillMove())
        waitingForInput += 2;
    else
        waitingForInput += 1;
    millMoveInputAwaiting = actionInputReq->isMillMove();
    logger.log("%s(): waiting for: %d, is mill move: %d", __FUNCTION__, waitingForInput, millMoveInputAwaiting);
}

void GameManager::handleInputProvided(ActionPtr action)
{
    logger.log("%s()", __FUNCTION__);
    auto actionInputProvided = dynamic_cast<ActionInputProvided*>(action.get());
    if(actionInputProvided == nullptr)
        throw ActionTypeMismatchException("Type: " + std::string(actionTypeToString(action->getType())));
    std::lock_guard<std::mutex> lock(userInputMutex);
    if(waitingForInput > 0)
    {
        inputProvided = true;
        boardFieldInputs.push_back(actionInputProvided->getBoardField());
        waitingForInput--;
        if(waitingForInput == 0)
        {
            userInputMove = buildInputMove();
            userInputProvided.notify_all();
        }
    }
}

void GameManager::handleGameStart(ActionPtr action)
{
    logger.log("%s()", __FUNCTION__);
    auto actionGameStart = dynamic_cast<ActionGameStart*>(action.get());
    if(actionGameStart == nullptr)
        throw ActionTypeMismatchException("Type: " + std::string(actionTypeToString(action->getType())));
    if(gameRunning)
        return;
    if(gameThread.joinable())
        gameThread.join();
    if(shouldTerminate)
        return;
    resetGameManager();
    controller->resetUI();
    gameThread = std::thread(&GameManager::runGame,
                             this,
                             actionGameStart->whitePlayerType,
                             actionGameStart->whitePlayerHeuristic,
                             actionGameStart->whitePlayerDepth,
                             actionGameStart->blackPlayerType,
                             actionGameStart->blackPlayerHeuristic,
                             actionGameStart->blackPlayerDepth);
    controller->gameStarted();
}

void GameManager::handleGameStop()
{
    logger.log("%s()", __FUNCTION__);
    shouldStop = true;
    userInputProvided.notify_all();
    gameRunning = false;
    controller->gameStopped();
}

void GameManager::handleGamePause()
{
    logger.log("%s()", __FUNCTION__);
    shouldPause = true;
    controller->gamePaused();
}

void GameManager::handleGameResume()
{
    logger.log("%s()", __FUNCTION__);
    shouldPause = false;
    pauseCondition.notify_all();
    controller->gameResumed();
}

void GameManager::handleActionMoveDone(ActionPtr action)
{
    logger.log("%s()", __FUNCTION__);
    auto actionMoveDone = dynamic_cast<ActionMoveDone*>(action.get());
    if(actionMoveDone == nullptr)
        throw ActionTypeMismatchException("Type: " + std::string(actionTypeToString(action->getType())));
    if(shouldUpdateUi)
        controller->updateUI(actionMoveDone->getMove());
}

void GameManager::handleGuiOff()
{
    logger.log("%s()", __FUNCTION__);
    shouldUpdateUi = false;
}

void GameManager::handleGuiOn()
{
    logger.log("%s()", __FUNCTION__);
    shouldUpdateUi = true;
}

void GameManager::handleWaitOnGame()
{
}

Move GameManager::buildInputMove()
{
    logger.log("%s()", __FUNCTION__);
    Move m{};
    if(boardFieldInputs.size() == 2)
    {
        m.fromField = boardFieldInputs[0];
        m.toField = boardFieldInputs[1];
    }
    else  // size() == 1
    {
        if(millMoveInputAwaiting)
        {
            m.fieldOponentsCheckerTaken = boardFieldInputs[0];
        }
        else
        {
            m.toField = boardFieldInputs[0];
        }
    }
    boardFieldInputs.clear();
    millMoveInputAwaiting = false;
    return m;
}

void GameManager::resetGameManager()
{
    logger.log("%s()", __FUNCTION__);
    shouldTerminate = false;
    shouldStop = false;
    shouldPause = false;
    waitingForInput = false;
    inputProvided = false;
    millMoveInputAwaiting = false;
    userInputMove = Move{};
    boardFieldInputs.clear();
}

} // namespace model
