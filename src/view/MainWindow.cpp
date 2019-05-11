#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <src/controller/MasterController.hpp>

#include <QMessageBox>
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
    button->setStyleSheet(
        styleProvider.buildStyleSheetCheckerWithBackground(checker, "rgb(52, 101, 164)"));
}

void MainWindow::resetFieldBackground(const std::string &boardField, CheckerType checker)
{
    std::cout << __FUNCTION__ << " boardField: " << boardField << std::endl;
    auto button = boardFieldToButton.at(boardField);
    button->setStyleSheet(
        styleProvider.buildStyleSheetCheckerWithBackground(checker, ""));
}

void MainWindow::updateGameState(const uint32_t whiteLeftCheckersToPut,
                                 const uint32_t blackLeftCheckersToPut,
                                 const uint32_t whiteLeftCheckersOnBoard,
                                 const uint32_t blackLeftCheckersOnBoard,
                                 const uint32_t whiteCheckersKilledByBlack,
                                 const uint32_t blackCheckersKilledByWhite)
{
    std::string whitePlayerInfoStr = "left checkers to put: " +
                                     std::to_string(whiteLeftCheckersToPut) + "\n" +
                                     "white checkers on board: " +
                                     std::to_string(whiteLeftCheckersOnBoard) + "\n" +
                                     "killed black checkers: " +
                                     std::to_string(blackCheckersKilledByWhite);
    QString whitePlayerInfo = QString::fromStdString(whitePlayerInfoStr);

    std::string blackPlayerInfoStr = "left checkers to put: " +
                                     std::to_string(blackLeftCheckersToPut) + "\n" +
                                     "white checkers on board: " +
                                     std::to_string(blackLeftCheckersOnBoard) + "\n" +
                                     "killed white checkers: " +
                                     std::to_string(whiteCheckersKilledByBlack);
    QString blackPlayerInfo = QString::fromStdString(blackPlayerInfoStr);

    ui->whitePlayerInfo->setText(whitePlayerInfo);
    ui->blackPlayerInfo->setText(blackPlayerInfo);
}

void MainWindow::updateLastMove(double elapsedSeconds,
                                const std::string& fromField,
                                const std::string& toField,
                                const std::string& fieldOponentsCheckerTaken,
                                CheckerType who)
{
    QString prologueTime = "Last turn time [s]: ";
    QString seconds;
    seconds.sprintf("%.2f", elapsedSeconds);
    ui->lastTurnTimeText->setText(prologueTime + seconds);
    QString prologueLastMove = "Last turn move:\n";
    std::string lastMove = "Who: ";
    if(who == CheckerType::White)
        lastMove += "White\n";
    else  // (who == CheckerType::Black)
        lastMove += "Black\n";
    if(!fromField.empty())
        lastMove += "From field: " + fromField + "\n";
    if(!toField.empty())
        lastMove += "To field: " + toField + "\n";
    if(!fieldOponentsCheckerTaken.empty())
        lastMove += "Oponent's checker taken: " + fieldOponentsCheckerTaken;
    ui->lastTurnMoveText->setText(prologueLastMove + QString::fromStdString(lastMove));
}

void MainWindow::resetUI()
{
    auto buttons = ui->boardFieldsGroup->buttons();
    for(auto& button : buttons)
    {
        button->setStyleSheet(styleProvider.getButtonStyle(CheckerType::None));
    }
    ui->whitePlayerInfo->setText("");
    ui->blackPlayerInfo->setText("");
    ui->lastTurnMoveText->setText("Last turn move:\n");
    ui->lastTurnTimeText->setText("Last turn time [s]: ");
    ui->gameStatusText->setText("");
    ui->whitePlayerImage->setStyleSheet(
        styleProvider.buildStyleSheetCheckerWithBackground(CheckerType::White, ""));
    ui->blackPlayerImage->setStyleSheet(
        styleProvider.buildStyleSheetCheckerWithBackground(CheckerType::Black, ""));
    clearLogBox();
}

void MainWindow::updateCurrentPlayer(CheckerType checkerColor)
{
    if(checkerColor == CheckerType::White)
    {
        ui->whitePlayerImage->setStyleSheet(
            styleProvider.buildStyleSheetCheckerWithBackground(CheckerType::White, "rgb(78, 154, 6)"));
        ui->blackPlayerImage->setStyleSheet(
            styleProvider.buildStyleSheetCheckerWithBackground(CheckerType::Black, ""));
    }
    else  // checkerColor == CheckerType::Black
    {
        ui->blackPlayerImage->setStyleSheet(
            styleProvider.buildStyleSheetCheckerWithBackground(CheckerType::Black, "rgb(78, 154, 6)"));
        ui->whitePlayerImage->setStyleSheet(
            styleProvider.buildStyleSheetCheckerWithBackground(CheckerType::White, ""));
    }
}

void MainWindow::updateGameFinished(const std::string& winnerName)
{
    ui->gameStatusText->setText(QString::fromStdString("Winner: " + winnerName));
}

void MainWindow::updateGameStarted()
{
    ui->gameStatusText->setText("Game running");
}

void MainWindow::updateGamePaused()
{
    ui->gameStatusText->setText("Game paused");
}

void MainWindow::updateGameResumed()
{
    ui->gameStatusText->setText("Game running");
}

void MainWindow::updateGameStopped()
{
    ui->gameStatusText->setText("Game stopped");
}

void MainWindow::boardFieldClicked(QAbstractButton* button)
{
    const std::string& boardPlace = buttonNameToBoardPlace.at(button->objectName().toStdString());
    controller->userInputField(boardPlace);
}

void MainWindow::startGameClicked()
{
    std::string whitePlayerType = ui->whitePlayerTypeCombo->currentText().toStdString();
    std::string whitePlayerHeurisitc = ui->whitePlayerHeuristicCombo->currentText().toStdString();
    std::string whiteTreeDepth = ui->whitePlayerTreeDepthText->toPlainText().toStdString();

    std::string blackPlayerType = ui->blackPlayerTypeCombo->currentText().toStdString();
    std::string blackPlayerHeurisitc = ui->blackPlayerHeuristicCombo->currentText().toStdString();
    std::string blackTreeDepth = ui->blackPlayerTreeDepthText->toPlainText().toStdString();

    controller->startGame(whitePlayerType, whitePlayerHeurisitc, whiteTreeDepth,
                          blackPlayerType, blackPlayerHeurisitc, blackTreeDepth);
}

void MainWindow::stopGameClicked()
{
    controller->stopGame();
}

void MainWindow::pauseGameClicked()
{
    controller->pauseGame();
}

void MainWindow::resumeGameClicked()
{
    controller->resumeGame();
}

void MainWindow::guiOnOffClicked()
{
    controller->guiOnOff(ui->guiOnCheckBox->isChecked());
}

void MainWindow::initialize()
{
    connectSingalsFromAllButtonsToSingleSlot();
    connect(ui->gameStartButton, SIGNAL(clicked()), this, SLOT(startGameClicked()));
    connect(ui->gameStopButton, SIGNAL(clicked()), this, SLOT(stopGameClicked()));
    connect(ui->gamePauseButton, SIGNAL(clicked()), this, SLOT(pauseGameClicked()));
    connect(ui->gameResumeButton, SIGNAL(clicked()), this, SLOT(resumeGameClicked()));
    connect(ui->guiOnCheckBox, SIGNAL(clicked()), this, SLOT(guiOnOffClicked()));
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

void MainWindow::clearLogBox()
{
    ui->gameLogText->setText("");
}
