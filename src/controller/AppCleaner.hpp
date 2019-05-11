#pragma once

#include "MasterController.hpp"

#include <src/tools/logging/Logger.hpp>

#include <QObject>

namespace controller {

class AppCleaner : public QObject
{
    Q_OBJECT
public:
    AppCleaner(MasterController* controller, tools::Logger& logger);
    ~AppCleaner();

    AppCleaner(const AppCleaner&) = delete;
    AppCleaner& operator=(const AppCleaner&) = delete;
    AppCleaner(AppCleaner&&) = delete;
    AppCleaner& operator=(AppCleaner&&) = delete;

public slots:
    void handleProperAppQuit();

private:
    MasterController* controller;
    tools::Logger& logger;
};

} // namespace controller
