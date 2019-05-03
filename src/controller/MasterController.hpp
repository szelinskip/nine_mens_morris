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
    void startGame();
    void goingDead();

private:
    CheckerType convertColor(PlayerColor color) const;

    MainWindow* mainWindow;
    GameManager* gameManager;

    tools::Logger& logger;
};

} // namespace controller
