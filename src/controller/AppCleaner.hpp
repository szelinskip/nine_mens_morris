#pragma once

#include "MasterController.hpp"

#include <QObject>

namespace controller {

class AppCleaner : public QObject
{
    Q_OBJECT
public:
    AppCleaner(MasterController* controller);
    ~AppCleaner();

    AppCleaner(const AppCleaner&) = delete;
    AppCleaner& operator=(const AppCleaner&) = delete;
    AppCleaner(AppCleaner&&) = delete;
    AppCleaner& operator=(AppCleaner&&) = delete;

public slots:
    void handleProperAppQuit();

private:
    MasterController* controller;
};

} // namespace controller
