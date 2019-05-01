#include "view/MainWindow.h"
#include "controller/MasterController.hpp"
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

    qApp->setQuitOnLastWindowClosed(true);
    w.show();
    return a.exec();
}
