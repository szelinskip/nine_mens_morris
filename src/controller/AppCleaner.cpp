#include "AppCleaner.hpp"

#include <iostream>

namespace controller {

AppCleaner::AppCleaner(controller::MasterController* controller)
    : controller(controller)
{
}

AppCleaner::~AppCleaner() = default;

void AppCleaner::handleProperAppQuit()
{
    std::cout << __FUNCTION__ << std::endl;
    controller->goingDead();
}

} // namespace controller
