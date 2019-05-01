#include "GameManager.hpp"
#include "UnsupportedActionType.hpp"
#include "ActionTypeMismatchException.hpp"
#include "player/HumanPlayer.hpp"
#include <src/controller/MasterController.hpp>

#include <iostream>

namespace model {

GameManager::GameManager()
    : gameRunning(false)
    , shouldRunLoop(false)
    , waitingForInput(0)
    , inputProvided(false)
    , shouldTerminate(false)
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

bool GameManager::shouldStop() const
{
    return shouldTerminate;
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

std::string GameManager::getInput()
{
    std::cout << __FUNCTION__ << std::endl;
    std::unique_lock<std::mutex> lock(userInputMutex);
    userInputProvided.wait(lock, [this](){return inputProvided || shouldTerminate;});
    inputProvided = false;
    std::cout << __FUNCTION__ << " input got " << userInput << std::endl;
    return userInput;
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
                    handleAction(std::move(req));
                }
                catch(UnsupportedActionType&)
                {
                    shouldRunLoop = false;
                }
                catch(ActionTypeMismatchException&)
                {
                    shouldRunLoop = false;
                }
            }
        }
    }
}

void GameManager::runGame()
{
    std::cout << __FUNCTION__ << std::endl;
    gameRunning = true;
    nineMensMorris = std::make_unique<NineMensMorris>(
        std::make_unique<HumanPlayer>(*this, "Player white", PlayerColor::White),
        std::make_unique<HumanPlayer>(*this, "Player black", PlayerColor::Black),
        this);
    nineMensMorris->startGame();
}

void GameManager::handleAction(ActionPtr action)
{
    std::cout << __FUNCTION__ << std::endl;
    ActionType type = action->getType();
    switch(type)
    {
        case ActionType::GameStart:
            handleGameStart();
            break;
        case ActionType::InputReq:
            handleInputReq();
            break;
        case ActionType::MoveDone:
            handleActionMoveDone(std::move(action));
            break;
        case ActionType::InputProvided:
            handleInputProvided(std::move(action));
            break;
        default:
            throw UnsupportedActionType("Type: " + std::to_string(static_cast<int>(type)));
    }
}

void GameManager::handleInputReq()
{
    std::cout << __FUNCTION__ << std::endl;
    std::lock_guard<std::mutex> lock(userInputMutex);
    waitingForInput++;
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
        waitingForInput--;
        userInput = actionInputProvided->getBoardField();
        userInputProvided.notify_all();
    }
}

void GameManager::handleGameStart()
{
    std::cout << __FUNCTION__ << std::endl;
    if(gameRunning)
        return;
    gameThread = std::thread(&GameManager::runGame, this);
}

void GameManager::handleActionMoveDone(ActionPtr action)
{
    std::cout << __FUNCTION__ << std::endl;
    auto actionMoveDone = dynamic_cast<ActionMoveDone*>(action.get());
    if(actionMoveDone == nullptr)
        throw ActionTypeMismatchException("Type: " + std::to_string(static_cast<int>(action->getType())));
    controller->updateUI(actionMoveDone->getBoardField(), actionMoveDone->getPlayerColor());
}

} // namespace model
