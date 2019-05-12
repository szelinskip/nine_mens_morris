#include "MasterController.hpp"

#include <chrono>

#include <src/model/game/GameManager.hpp>
#include <src/view/MainWindow.h>
#include <src/model/game/player/PlayerInfo.hpp>

#include <QMetaObject>

namespace controller {

MasterController::MasterController(MainWindow* mainWindow, GameManager* gameManager, tools::Logger& logger)
    : mainWindow(mainWindow)
    , gameManager(gameManager)
    , logger(logger)
{
    mainWindow->setController(this);
    gameManager->setController(this);
    gameManager->run();
}

MasterController::~MasterController() = default;

void MasterController::userInputField(const std::string& boardField)
{
    // TODO
    logger.log("%s(): boardfield: %s", __FUNCTION__, boardField.c_str());
    auto action = std::make_unique<ActionInputProvided>(boardField);
    gameManager->putAction(std::move(action));
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

void MasterController::updateUI(const Move& move)
{
    using namespace std::chrono_literals;
    logger.log("%s(): move from: %s to: %s, oponent checker taken: %s", __FUNCTION__, move.fromField.c_str(), move.toField.c_str(), move.fieldOponentsCheckerTaken.c_str());
    CheckerType checker = convertColor(move.who);

    if(!move.fromField.empty())  // NOT first stage
    {
        // erase checker from field
        QMetaObject::invokeMethod(mainWindow, "setCheckerOnField", Q_ARG(const std::string&, move.fromField), Q_ARG(CheckerType, CheckerType::None));
        std::this_thread::sleep_for(500ms);
        QMetaObject::invokeMethod(mainWindow, "resetFieldBackground", Q_ARG(const std::string&, move.fromField), Q_ARG(CheckerType, CheckerType::None));
    }
    if(!move.toField.empty())
    {
        QMetaObject::invokeMethod(mainWindow, "setCheckerOnField", Q_ARG(const std::string&, move.toField), Q_ARG(CheckerType, checker));
        std::this_thread::sleep_for(500ms);
        QMetaObject::invokeMethod(mainWindow, "resetFieldBackground", Q_ARG(const std::string&, move.toField), Q_ARG(CheckerType, checker));
    }
    if(!move.fieldOponentsCheckerTaken.empty())
    {
        QMetaObject::invokeMethod(mainWindow, "setCheckerOnField", Q_ARG(const std::string&, move.fieldOponentsCheckerTaken), Q_ARG(CheckerType, CheckerType::None));
        std::this_thread::sleep_for(500ms);
        QMetaObject::invokeMethod(mainWindow, "resetFieldBackground", Q_ARG(const std::string&, move.fieldOponentsCheckerTaken), Q_ARG(CheckerType, CheckerType::None));
    }
}

void MasterController::updateUI(const uint32_t turnNum,
                                const uint32_t whiteLeftCheckersToPut,
                                const uint32_t blackLeftCheckersToPut,
                                const uint32_t whiteLeftCheckersOnBoard,
                                const uint32_t blackLeftCheckersOnBoard,
                                const uint32_t whiteCheckersKilledByBlack,
                                const uint32_t blackCheckersKilledByWhite)
{
    QMetaObject::invokeMethod(mainWindow, "updateGameState",
                              Q_ARG(uint32_t, turnNum),
                              Q_ARG(uint32_t, whiteLeftCheckersToPut),
                              Q_ARG(uint32_t, blackLeftCheckersToPut),
                              Q_ARG(uint32_t, whiteLeftCheckersOnBoard),
                              Q_ARG(uint32_t, blackLeftCheckersOnBoard),
                              Q_ARG(uint32_t, whiteCheckersKilledByBlack),
                              Q_ARG(uint32_t, blackCheckersKilledByWhite));
}

void MasterController::resetUI()
{
    QMetaObject::invokeMethod(mainWindow, "resetUI");
}

void MasterController::updateCurrentPlayer(const PlayerColor color)
{
    QMetaObject::invokeMethod(mainWindow, "updateCurrentPlayer", Q_ARG(CheckerType, convertColor(color)));
}

void MasterController::updateLastMove(std::chrono::milliseconds elapsed,
                                      const Move& lastMove,
                                      const uint32_t turnNum,
                                      const bool timeConstraintExceeded)
{
    double elapsedSeconds = elapsed.count() / 1000.0;
    QMetaObject::invokeMethod(mainWindow, "updateLastMove",
                              Q_ARG(double, elapsedSeconds),
                              Q_ARG(const std::string&, lastMove.fromField),
                              Q_ARG(const std::string&, lastMove.toField),
                              Q_ARG(const std::string&, lastMove.fieldOponentsCheckerTaken),
                              Q_ARG(CheckerType, convertColor(lastMove.who)),
                              Q_ARG(uint32_t, turnNum),
                              Q_ARG(bool, timeConstraintExceeded));
}

void MasterController::gameFinishedStatus(const std::string& winnerName)
{
    QMetaObject::invokeMethod(mainWindow, "updateGameFinished", Q_ARG(const std::string&, winnerName));
}

void MasterController::startGame(const std::string& whitePlayerTypeStr,
                                 const std::string& whitePlayerHeurisitcStr,
                                 const std::string& whiteTreeDepthStr,
                                 const std::string& blackPlayerTypeStr,
                                 const std::string& blackPlayerHeurisitcStr,
                                 const std::string& blackTreeDepthStr,
                                 const std::string& timeConstraintStr)
{
    logger.log("%s(): whitePlayerType: %s, whitePlayerHeurisitc: %s, whiteTreeDepth: %s, "
               "blackPlayerType: %s, blackPlayerHeuristic: %s, blackTreeDepth: %s",
               __FUNCTION__, whitePlayerTypeStr.c_str(), whitePlayerHeurisitcStr.c_str(), whiteTreeDepthStr.c_str(),
               blackPlayerTypeStr.c_str(), blackPlayerHeurisitcStr.c_str(), blackTreeDepthStr.c_str());

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

    int timeConstraintSeconds = 0;
    if(!timeConstraintStr.empty())
        timeConstraintSeconds = std::stoi(timeConstraintStr);

    auto action = std::make_unique<ActionGameStart>(whitePlayerType,
                                                    whitePlayerHeuristic,
                                                    static_cast<uint32_t>(whitePlayerDepth),
                                                    blackPlayerType,
                                                    blackPlayerHeuristic,
                                                    static_cast<uint32_t>(blackPlayerDepth),
                                                    std::chrono::seconds(timeConstraintSeconds));
    gameManager->putAction(std::move(action));
}

void MasterController::stopGame()
{
    logger.log("%s(): ", __FUNCTION__);
    auto action = std::make_unique<ActionGameStop>();
    gameManager->putAction(std::move(action));
}

void MasterController::pauseGame()
{
    logger.log("%s(): ", __FUNCTION__);
    auto action = std::make_unique<ActionGamePause>();
    gameManager->putAction(std::move(action));
}

void MasterController::resumeGame()
{
    logger.log("%s(): ", __FUNCTION__);
    auto action = std::make_unique<ActionGameResume>();
    gameManager->putAction(std::move(action));
}

void MasterController::guiOnOff(const bool isGuiOn)
{
    logger.log("%s(): isGuiOn=%d", __FUNCTION__, isGuiOn);
    std::unique_ptr<Action> action;
    if(isGuiOn)
        action = std::make_unique<ActionGuiOn>();
    else
        action = std::make_unique<ActionGuiOff>();
    gameManager->putAction(std::move(action));
}

void MasterController::goingDead()
{
    gameManager->stop();
}

void MasterController::waitOnGame()
{
    logger.log("%s(): waitOnGame", __FUNCTION__);
    auto action = std::make_unique<ActionWaitOnGame>();
    gameManager->putAction(std::move(action));
}

void MasterController::gameStarted()
{
    QMetaObject::invokeMethod(mainWindow, "updateGameStarted");
}

void MasterController::gamePaused()
{
    QMetaObject::invokeMethod(mainWindow, "updateGamePaused");
}

void MasterController::gameResumed()
{
    QMetaObject::invokeMethod(mainWindow, "updateGameResumed");
}

void MasterController::gameStopped()
{
    QMetaObject::invokeMethod(mainWindow, "updateGameStopped");
}

} // namespace controller
