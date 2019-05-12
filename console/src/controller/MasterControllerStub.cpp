#include <src/controller/MasterController.hpp>

#include <src/model/game/GameManager.hpp>
#include <console/src/view/MainWindow.h>
#include <src/model/game/player/PlayerInfo.hpp>

namespace controller {

MasterController::MasterController(MainWindow* /*mainWindow*/, GameManager* gameManager, tools::Logger& logger)
    : mainWindow(nullptr)
    , gameManager(gameManager)
    , logger(logger)
{
    gameManager->setController(this);
    gameManager->run();
}

MasterController::~MasterController() = default;

void MasterController::userInputField(const std::string& /*boardField*/)
{
}

CheckerType MasterController::convertColor(PlayerColor color) const
{
    switch(color)
    {
    case PlayerColor::None:
        return CheckerType::None;
    case PlayerColor::White:
        return CheckerType::White;
    case PlayerColor::Black:
        return CheckerType::Black;
    default:
        return CheckerType::None;
    }
}

void MasterController::updateUI(const Move& /*move*/)
{
}

void MasterController::updateUI(const uint32_t /*turnNum*/,
                                const uint32_t /*whiteLeftCheckersToPut*/,
                                const uint32_t /*blackLeftCheckersToPut*/,
                                const uint32_t /*whiteLeftCheckersOnBoard*/,
                                const uint32_t /*blackLeftCheckersOnBoard*/,
                                const uint32_t /*whiteCheckersKilledByBlack*/,
                                const uint32_t /*blackCheckersKilledByWhite*/)
{
}

void MasterController::resetUI()
{
}

void MasterController::updateCurrentPlayer(const PlayerColor /*color*/)
{
}

void MasterController::updateLastMove(std::chrono::milliseconds /*elapsed*/, const Move& /*lastMove*/)
{
}

void MasterController::gameFinishedStatus(const std::string& /*winnerName*/)
{
}

void MasterController::startGame(const std::string& whitePlayerTypeStr,
                                 const std::string& whitePlayerHeurisitcStr,
                                 const std::string& whiteTreeDepthStr,
                                 const std::string& blackPlayerTypeStr,
                                 const std::string& blackPlayerHeurisitcStr,
                                 const std::string& blackTreeDepthStr)
{
    PlayerType whitePlayerType = convertStringToPlayerType(whitePlayerTypeStr);
    PlayerHeuristic whitePlayerHeuristic = convertStringToPlayerHeuristic(whitePlayerHeurisitcStr);
    int whitePlayerDepth = 0;
    if(!whiteTreeDepthStr.empty())
        whitePlayerDepth = std::stoi(whiteTreeDepthStr);

    PlayerType blackPlayerType = convertStringToPlayerType(blackPlayerTypeStr);
    PlayerHeuristic blackPlayerHeuristic = convertStringToPlayerHeuristic(blackPlayerHeurisitcStr);
    int blackPlayerDepth = 0;
    if(!blackTreeDepthStr.empty())
        blackPlayerDepth = std::stoi(blackTreeDepthStr);

    auto action = std::make_unique<ActionGameStart>(whitePlayerType,
                                                    whitePlayerHeuristic,
                                                    static_cast<uint32_t>(whitePlayerDepth),
                                                    blackPlayerType,
                                                    blackPlayerHeuristic,
                                                    static_cast<uint32_t>(blackPlayerDepth));
    gameManager->putAction(std::move(action));
}

void MasterController::waitOnGame()
{
    auto action = std::make_unique<ActionWaitOnGame>();
    gameManager->putAction(std::move(action));
}

void MasterController::stopGame()
{
}

void MasterController::pauseGame()
{
}

void MasterController::resumeGame()
{
}

void MasterController::guiOnOff(const bool /*isGuiOn*/)
{
}

void MasterController::goingDead()
{
}

void MasterController::gameStarted()
{
}

void MasterController::gamePaused()
{
}

void MasterController::gameResumed()
{
}

void MasterController::gameStopped()
{
}

} // namespace controller
