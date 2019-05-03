#include "MasterController.hpp"
#include <src/model/game/GameManager.hpp>
#include <src/view/MainWindow.h>

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
    logger.log("%s(): move from: %s to: %s, oponent checker taken: %s", __FUNCTION__, move.fromField.c_str(), move.toField.c_str(), move.fieldOponentsCheckerTaken.c_str());
    CheckerType checker = convertColor(move.who);

    if(!move.fromField.empty())  // NOT first stage
    {
        // erase checker from field
        QMetaObject::invokeMethod(mainWindow, "setCheckerOnField", Q_ARG(const std::string&, move.fromField), Q_ARG(CheckerType, CheckerType::None));
    }
    if(!move.toField.empty())
    {
        QMetaObject::invokeMethod(mainWindow, "setCheckerOnField", Q_ARG(const std::string&, move.toField), Q_ARG(CheckerType, checker));
    }
    if(!move.fieldOponentsCheckerTaken.empty())
    {
        QMetaObject::invokeMethod(mainWindow, "setCheckerOnField", Q_ARG(const std::string&, move.fieldOponentsCheckerTaken), Q_ARG(CheckerType, CheckerType::None));
    }
}

void MasterController::startGame()
{
    logger.log("%s(): ", __FUNCTION__);
    auto action = std::make_unique<ActionGameStart>();
    gameManager->putAction(std::move(action));
}

void MasterController::goingDead()
{
    gameManager->stop();
}

} // namespace controller
