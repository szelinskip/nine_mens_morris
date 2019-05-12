#pragma once

#include <memory>
#include <string>

#include <src/model/communication/Action.hpp>
#include <src/view/CheckerType.hpp>
#include <src/model/game/Move.hpp>
#include <src/tools/logging/Logger.hpp>

using namespace model;

namespace model {
class GameManager;
} // namespace model

class MainWindow;

namespace controller {

class MasterController
{
public:
    MasterController(MainWindow* mainWindow, GameManager* gameManager, tools::Logger& logger);
    ~MasterController();

    MasterController() = delete;
    MasterController(const MasterController&) = delete;
    MasterController& operator=(const MasterController&) = delete;
    MasterController(MasterController&&) = delete;
    MasterController& operator=(MasterController&&) = delete;

    void userInputField(const std::string& boardField);
    void updateUI(const Move& move);
    void updateUI(const uint32_t turnNum,
                  const uint32_t whiteLeftCheckersToPut,
                  const uint32_t blackLeftCheckersToPut,
                  const uint32_t whiteLeftCheckersOnBoard,
                  const uint32_t blackLeftCheckersOnBoard,
                  const uint32_t whiteCheckersKilledByBlack,
                  const uint32_t blackCheckersKilledByWhite);
    void resetUI();
    void updateCurrentPlayer(const PlayerColor color);
    void updateLastMove(std::chrono::milliseconds elapsed,
                        const Move& lastMove,
                        const uint32_t turnNum,
                        const bool timeConstraintExceeded);
    void gameFinishedStatus(const std::string& winnerName);
    void startGame(const std::string& whitePlayerTypeStr,
                   const std::string& whitePlayerHeurisitcStr,
                   const std::string& whiteTreeDepthStr,
                   const std::string& blackPlayerTypeStr,
                   const std::string& blackPlayerHeurisitcStr,
                   const std::string& blackTreeDepthStr,
                   const std::string& timeConstraintStr);
    void stopGame();
    void pauseGame();
    void resumeGame();
    void guiOnOff(const bool isGuiOn);
    void goingDead();
    void waitOnGame();

    void gameStarted();
    void gamePaused();
    void gameResumed();
    void gameStopped();

private:
    CheckerType convertColor(PlayerColor color) const;

    MainWindow* mainWindow;
    GameManager* gameManager;

    tools::Logger& logger;
};

} // namespace controller
