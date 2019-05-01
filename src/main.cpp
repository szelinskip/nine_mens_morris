#include "view/MainWindow.h"
#include "controller/MasterController.hpp"
#include "controller/AppCleaner.hpp"
#include "model/game/GameManager.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    // view part
    QApplication a(argc, argv);
    MainWindow w;

    // model part
    model::GameManager gameManager;

    // controller part
    controller::MasterController controller(&w, &gameManager);

    controller::AppCleaner cleaner(&controller);

    qApp->setQuitOnLastWindowClosed(true);
    QObject::connect(qApp, SIGNAL(aboutToQuit()), &cleaner, SLOT(handleProperAppQuit()));

    w.show();
    return a.exec();
}
