#pragma once

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <queue>

#include <src/model/communication/Action.hpp>
#include <src/tools/logging/Logger.hpp>
#include "NineMensMorris.hpp"

namespace controller {
class MasterController;
} // namespace controller

namespace model {

using ActionPtr = std::unique_ptr<Action>;

class GameManager
{
public:
    GameManager(tools::Logger& logger, const bool shouldIntroducePauseBetweenPlayers = true);
    ~GameManager();

    GameManager() = delete;
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
    GameManager(GameManager&&) = delete;
    GameManager& operator=(GameManager&&) = delete;

    void setController(controller::MasterController* controller);

    void run();
    void stop();
    bool shouldStopGame() const;

    void putAction(ActionPtr action);
    Move getInput();

    void beforeTurnActions(const uint32_t turnNum,
                           const uint32_t whiteLeftCheckersToPut,
                           const uint32_t blackLeftCheckersToPut,
                           const uint32_t whiteLeftCheckersOnBoard,
                           const uint32_t blackLeftCheckersOnBoard,
                           const uint32_t whiteCheckersKilledByBlack,
                           const uint32_t blackCheckersKilledByWhite);

    void afterTurnActions(std::chrono::milliseconds elapsed,
                          const Move& lastMove,
                          const uint32_t turnNum,
                          const bool timeConstraintExceeded);

    void playersTurnAction(const Player* currentPlayer);
    void gameFinishedActions(const Player* winner);

    void waitOnGameManager();
    void waitUntilGameNotStarted();

private:
    void runningLoop();
    void runGame(const PlayerType whitePlayerType,
                 const PlayerHeuristic whitePlayerHeuristic,
                 const uint32_t whitePlayerDepth,
                 const PlayerType blackPlayerType,
                 const PlayerHeuristic blackPlayerHeuristic,
                 const uint32_t blackPlayerDepth,
                 const std::chrono::seconds timeConstraint);

    void handleAction(ActionPtr action);
    void handleInputReq(ActionPtr action);
    void handleInputProvided(ActionPtr action);
    void handleGameStart(ActionPtr action);
    void handleGameStop();
    void handleGamePause();
    void handleGameResume();
    void handleActionMoveDone(ActionPtr action);
    void handleGuiOff();
    void handleGuiOn();
    void handleWaitOnGame();
    Move buildInputMove();
    void resetGameManager();

    const std::chrono::milliseconds pauseBetweenPlayers;

    controller::MasterController* controller;

    std::mutex actionsQMutex;
    std::queue<ActionPtr> actionsQueue;

    std::thread actionsLoopThread;
    std::thread gameThread;

    std::atomic<bool> gameRunning;
    std::unique_ptr<NineMensMorris> nineMensMorris;

    std::atomic<bool> shouldRunLoop;

    std::mutex userInputMutex;
    std::condition_variable userInputProvided;
    uint32_t waitingForInput;
    bool inputProvided;
    bool millMoveInputAwaiting;
    Move userInputMove;
    std::vector<std::string> boardFieldInputs;

    std::atomic<bool> shouldTerminate;
    std::atomic<bool> shouldStop;

    std::atomic<bool> shouldPause;
    std::mutex pauseMutex;
    std::condition_variable pauseCondition;

    std::atomic<bool> shouldUpdateUi;

    bool shouldIntroducePauseBetweenPlayers;

    tools::Logger& logger;
};

}
