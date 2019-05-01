#pragma once

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <queue>

#include <src/model/communication/Action.hpp>
#include "NineMensMorris.hpp"

namespace controller {
class MasterController;
} // namespace controller

namespace model {

using ActionPtr = std::unique_ptr<Action>;

class GameManager
{
public:
    GameManager();
    ~GameManager();

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
    GameManager(GameManager&&) = delete;
    GameManager& operator=(GameManager&&) = delete;

    void setController(controller::MasterController* controller);

    void run();

    void putAction(ActionPtr action);
    std::string getInput();

private:
    void runningLoop();
    void runGame();
    void handleAction(ActionPtr action);
    void handleInputReq();
    void handleInputProvided(ActionPtr action);
    void handleGameStart();
    void handleActionMoveDone(ActionPtr action);

    controller::MasterController* controller;

    std::mutex actionsQMutex;
    std::queue<ActionPtr> actionsQueue;

    std::thread actionsLoopThread;
    std::thread gameThread;

    std::atomic<bool> gameRunning;

    std::atomic<bool> shouldRunLoop;

    std::mutex userInputMutex;
    std::condition_variable userInputProvided;
    bool inputProvided;
    std::string userInput;
};

}
