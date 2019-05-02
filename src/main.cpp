#include "view/MainWindow.h"
#include "controller/MasterController.hpp"
#include "controller/AppCleaner.hpp"
#include "model/game/GameManager.hpp"

#include <QApplication>
#include <iostream>

int main(/*int argc, char *argv[]*/)
{
//    // view part
//    QApplication a(argc, argv);
//    MainWindow w;

//    // model part
//    model::GameManager gameManager;

//    // controller part
//    controller::MasterController controller(&w, &gameManager);

//    controller::AppCleaner cleaner(&controller);

//    qApp->setQuitOnLastWindowClosed(true);
//    QObject::connect(qApp, SIGNAL(aboutToQuit()), &cleaner, SLOT(handleProperAppQuit()));

//    w.show();
//    return a.exec();

    GameState state;

    std::cout << "initial state: " << std::endl << state.getStrRepr() << std::endl;

    auto possibleStates = state.getAvailableStates(PlayerColor::White);
    int counter = 0;
    for(const auto& possibleState : possibleStates)
    {
        counter++;
        std::cout << std::endl << "state: " << counter << std::endl;
        std::cout << possibleState.getStrRepr() << std::endl;
    }

    return 0;
}
