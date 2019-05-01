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
    void setCheckerOnField(const std::string& boardField, CheckerType checker);

private:
    void initialize();
    void connectSingalsFromAllButtonsToSingleSlot();
    std::string getBoardPlaceFromName(const std::string& name) const;

    Ui::MainWindow* ui;

    StyleProvider styleProvider;

    std::unordered_map<std::string, std::string> buttonNameToBoardPlace;
    std::unordered_map<std::string, QAbstractButton*> boardFieldToButton;
    controller::MasterController* controller;
};
