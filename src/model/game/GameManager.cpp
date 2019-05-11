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

GameManager::GameManager(tools::Logger& logger)
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
    , logger(logger)
{
}

void GameManager::run()
{
    std::cout << __FUNCTION__ << std::endl;
    shouldRunLoop = true;
    actionsLoopThread = std::thread(&GameManager::runningLoop, this);
}

void GameManager::stop()
{
    // release waiting threads to join them properly
    shouldTerminate = true;
    userInputProvided.notify_all();
}

bool GameManager::shouldStopGame() const
{
    return shouldTerminate || shouldStop;
}

GameManager::~GameManager()
{
    shouldRunLoop = false;
    if(gameThread.joinable())
        gameThread.join();

    if(actionsLoopThread.joinable())
        actionsLoopThread.join();
}

void GameManager::setController(controller::MasterController* controller)
{
    this->controller = controller;
}

void GameManager::putAction(ActionPtr action)
{
    if(shouldTerminate)
        return;
    std::cout << __FUNCTION__ << std::endl;
    std::lock_guard<std::mutex> lock(actionsQMutex);
    actionsQueue.push(std::move(action));
}

Move GameManager::getInput()
{
    std::cout << __FUNCTION__ << std::endl;
    std::unique_lock<std::mutex> lock(userInputMutex);
    userInputProvided.wait(lock, [this](){return inputProvided || shouldStop || shouldTerminate;});
    inputProvided = false;
    std::cout << __FUNCTION__ << " input got " << userInputMove.fromField << " -> " << userInputMove.toField << std::endl;
    return userInputMove;
}

void GameManager::beforeTurnActions(const uint32_t whiteLeftCheckersToPut,
                                    const uint32_t blackLeftCheckersToPut,
                                    const uint32_t whiteLeftCheckersOnBoard,
                                    const uint32_t blackLeftCheckersOnBoard,
                                    const uint32_t whiteCheckersKilledByBlack,
                                    const uint32_t blackCheckersKilledByWhite)
{
    std::cout << __FUNCTION__ << std::endl;
    if(shouldUpdateUi)
    {
        controller->updateUI(whiteLeftCheckersToPut,
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
    std::cout << __FUNCTION__ << std::endl;
    controller->updateLastMove(elapsed, lastMove);
    std::cout << "sleeping for: " << pauseBetweenPlayers.count() << " ms" << std::endl;
    std::this_thread::sleep_for(pauseBetweenPlayers);
    std::cout << "end sleep" << std::endl;
}

void GameManager::playersTurnAction(const Player* currentPlayer)
{
    std::cout << __FUNCTION__ << std::endl;
    controller->updateCurrentPlayer(currentPlayer->getColor());
}

void GameManager::gameFinishedActions(const Player* winner)
{
    std::cout << __FUNCTION__ << std::endl;
    std::string winnerName = "DRAW";
    if(winner != nullptr)
        winnerName = winner->getName();
    controller->gameFinishedStatus(winnerName);
}

void GameManager::runningLoop()
{
    std::cout << __FUNCTION__ << std::endl;
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
    std::cout << __FUNCTION__ << std::endl;
    gameRunning = true;

    PlayerFactory playerFactory;

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
                                                      this);

    nineMensMorris->startGame();
    std::cout << __FUNCTION__ << " game finished " << std::endl;
}

void GameManager::handleAction(ActionPtr action)
{
    std::cout << __FUNCTION__ << std::endl;
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
        default:
            throw UnsupportedActionType("Type: " + std::to_string(static_cast<int>(type)));
    }
}

void GameManager::handleInputReq(ActionPtr action)
{
    auto actionInputReq = dynamic_cast<ActionInputReq*>(action.get());
    if(actionInputReq == nullptr)
        throw ActionTypeMismatchException("Type: " + std::to_string(static_cast<int>(action->getType())));
    std::lock_guard<std::mutex> lock(userInputMutex);
    userInputMove = Move{};
    if(!actionInputReq->isFirstStage() && !actionInputReq->isMillMove())
        waitingForInput += 2;
    else
        waitingForInput += 1;
    millMoveInputAwaiting = actionInputReq->isMillMove();
    std::cout << __FUNCTION__ << "waiting for: " << waitingForInput << " is mill move? " << millMoveInputAwaiting << std::endl;
}

void GameManager::handleInputProvided(ActionPtr action)
{
    std::cout << __FUNCTION__ << std::endl;
    auto actionInputProvided = dynamic_cast<ActionInputProvided*>(action.get());
    if(actionInputProvided == nullptr)
        throw ActionTypeMismatchException("Type: " + std::to_string(static_cast<int>(action->getType())));
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
    std::cout << __FUNCTION__ << std::endl;
    auto actionGameStart = dynamic_cast<ActionGameStart*>(action.get());
    if(actionGameStart == nullptr)
        throw ActionTypeMismatchException("Type: " + std::to_string(static_cast<int>(action->getType())));
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
    shouldStop = true;
    userInputProvided.notify_all();
    if(gameThread.joinable())
        gameThread.join();
    gameRunning = false;
    controller->gameStopped();
}

void GameManager::handleGamePause()
{
    shouldPause = true;
    controller->gamePaused();
}

void GameManager::handleGameResume()
{
    shouldPause = false;
    pauseCondition.notify_all();
    controller->gameResumed();
}

void GameManager::handleActionMoveDone(ActionPtr action)
{
    std::cout << __FUNCTION__ << std::endl;
    auto actionMoveDone = dynamic_cast<ActionMoveDone*>(action.get());
    if(actionMoveDone == nullptr)
        throw ActionTypeMismatchException("Type: " + std::to_string(static_cast<int>(action->getType())));
    if(shouldUpdateUi)
        controller->updateUI(actionMoveDone->getMove());
}

void GameManager::handleGuiOff()
{
    shouldUpdateUi = false;
}

void GameManager::handleGuiOn()
{
    shouldUpdateUi = true;
}

Move GameManager::buildInputMove()
{
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
