#pragma once

#include <string>

#include "player/PlayerColor.hpp"

namespace model {

struct Move
{
    std::string fromField;
    std::string toField;
    PlayerColor who;

    std::string fieldOponentsCheckerTaken;
};

} // namespace model
