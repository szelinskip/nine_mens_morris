#include "MasterController.hpp"
#include <src/model/game/GameManager.hpp>
#include <src/view/MainWindow.h>

#include <QMetaObject>

#include <iostream>

namespace controller {

MasterController::MasterController(MainWindow* mainWindow, GameManager* gameManager)
    : mainWindow(mainWindow)
    , gameManager(gameManager)
{
    mainWindow->setController(this);
    gameManager->setController(this);
    gameManager->run();
}

MasterController::~MasterController() = default;

void MasterController::userInputField(const std::string& boardField)
{
    std::cout << __FUNCTION__ << " boardfield: " << boardField << std::endl;
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

void MasterController::updateUI(const std::string& boardField, PlayerColor color)
{
    std::cout << __FUNCTION__ << " board field: " << boardField <<  std::endl;
    CheckerType checker = convertColor(color);
    QMetaObject::invokeMethod(mainWindow, "setCheckerOnField", Q_ARG(const std::string&, boardField), Q_ARG(CheckerType, checker));
}

void MasterController::startGame()
{
    std::cout << "controller " << __FUNCTION__ << std::endl;
    auto action = std::make_unique<ActionGameStart>();
    gameManager->putAction(std::move(action));
}

void MasterController::goingDead()
{
    gameManager->stop();
}

} // namespace controller
