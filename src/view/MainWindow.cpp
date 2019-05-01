#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <src/controller/MasterController.hpp>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    ui->setupUi(this);
    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setController(controller::MasterController* controller)
{
    this->controller = controller;
}

void MainWindow::setCheckerOnField(const std::string& boardField, CheckerType checker)
{
    std::cout << __FUNCTION__ << " boardField: " << boardField << std::endl;
    auto button = boardFieldToButton.at(boardField);
    button->setStyleSheet(styleProvider.getButtonStyle(checker));
}

void MainWindow::boardFieldClicked(QAbstractButton* button)
{
    const std::string& boardPlace = buttonNameToBoardPlace.at(button->objectName().toStdString());
    controller->userInputField(boardPlace);
}

void MainWindow::startGameClicked()
{
    controller->startGame();
}

void MainWindow::initialize()
{
    connectSingalsFromAllButtonsToSingleSlot();
    connect(ui->gameStartButton, SIGNAL(clicked()), this, SLOT(startGameClicked()));
}

void MainWindow::connectSingalsFromAllButtonsToSingleSlot()
{
    connect(ui->boardFieldsGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(boardFieldClicked(QAbstractButton*)));
    for(auto& button : ui->boardFieldsGroup->buttons())
    {
        buttonNameToBoardPlace.emplace(button->objectName().toStdString(),
                                       getBoardPlaceFromName(button->objectName().toStdString()));
        boardFieldToButton.emplace(getBoardPlaceFromName(button->objectName().toStdString()), button);
    }
}

std::string MainWindow::getBoardPlaceFromName(const std::string& name) const
{
    return name.substr(name.size() - 2, name.size());
}
