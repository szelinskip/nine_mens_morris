#include "view/MainWindow.h"
#include "controller/MasterController.hpp"
#include "controller/AppCleaner.hpp"
#include "model/game/GameManager.hpp"
#include "tools/logging/Logger.hpp"
#include "tools/logging/ConsoleLoggingPolicy.hpp"
#include "tools/logging/FileLoggingPolicy.hpp"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    tools::Logger logger(std::make_unique<tools::ConsoleLoggingPolicy>());
    logger.addLoggingPolicy(std::make_unique<tools::FileLoggingPolicy>("log", true));
    // view part
    QApplication a(argc, argv);
    MainWindow w;

    // model part
    model::GameManager gameManager(logger);

    // controller part

    controller::MasterController controller(&w, &gameManager, logger);

    controller::AppCleaner cleaner(&controller);

    qApp->setQuitOnLastWindowClosed(true);
    QObject::connect(qApp, SIGNAL(aboutToQuit()), &cleaner, SLOT(handleProperAppQuit()));
    w.show();
    return a.exec();

//    GameState state;

//    std::cout << "initial state: " << std::endl << state.getStrRepr() << std::endl;

//    auto possibleStates = state.getAvailableStates(PlayerColor::White);
//    int counter = 0;
//    for(const auto& possibleState : possibleStates)
//    {
//        counter++;
//        std::cout << std::endl << "state: " << counter << std::endl;
//        std::cout << possibleState.getStrRepr() << std::endl;
//    }

//    return 0;
}
