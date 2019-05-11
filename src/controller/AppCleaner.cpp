#include "AppCleaner.hpp"

#include <iostream>

namespace controller {

AppCleaner::AppCleaner(controller::MasterController* controller, tools::Logger& logger)
    : controller(controller)
    , logger(logger)
{
}

AppCleaner::~AppCleaner() = default;

void AppCleaner::handleProperAppQuit()
{
    logger.log("%s()", __FUNCTION__);
    controller->goingDead();
}

} // namespace controller
