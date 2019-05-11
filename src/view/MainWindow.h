#pragma once

#include <cstdint>
#include <unordered_map>
#include <string>

#include "CheckerType.hpp"
#include "StyleProvider.hpp"

#include <QMainWindow>
#include <QAbstractButton>

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(CheckerType)
Q_DECLARE_METATYPE(uint32_t)

namespace Ui {
class MainWindow;
}

namespace controller {
class MasterController;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;
    MainWindow(MainWindow&&) = delete;
    MainWindow& operator=(MainWindow&&) = delete;

    void setController(controller::MasterController* controller);

public slots:
    void boardFieldClicked(QAbstractButton* button);
    void startGameClicked();
    void stopGameClicked();
    void pauseGameClicked();
    void resumeGameClicked();
    void guiOnOffClicked();
    void setCheckerOnField(const std::string& boardField, CheckerType checker);
    void resetFieldBackground(const std::string& boardField, CheckerType checker);
    void updateGameState(const uint32_t whiteLeftCheckersToPut,
                         const uint32_t blackLeftCheckersToPut,
                         const uint32_t whiteLeftCheckersOnBoard,
                         const uint32_t blackLeftCheckersOnBoard,
                         const uint32_t whiteCheckersKilledByBlack,
                         const uint32_t blackCheckersKilledByWhite);
    void updateLastMove(double elapsedSeconds,
                        const std::string& fromField,
                        const std::string& toField,
                        const std::string& fieldOponentsCheckerTaken,
                        CheckerType who);
    void resetUI();
    void updateCurrentPlayer(CheckerType checkerColor);
    void updateGameFinished(const std::string& winnerName);
    void updateGameStarted();
    void updateGamePaused();
    void updateGameResumed();
    void updateGameStopped();

private:
    void initialize();
    void connectSingalsFromAllButtonsToSingleSlot();
    std::string getBoardPlaceFromName(const std::string& name) const;
    void clearLogBox();

    Ui::MainWindow* ui;

    StyleProvider styleProvider;

    std::unordered_map<std::string, std::string> buttonNameToBoardPlace;
    std::unordered_map<std::string, QAbstractButton*> boardFieldToButton;
    controller::MasterController* controller;
};
