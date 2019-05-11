#pragma once

#include <cstdint>

namespace model {

enum class ActionType : uint8_t
{
    InputProvided,
    InputReq,
    InputResp,
    MoveDone,
    GameStart,
    GameStop,
    GamePause,
    GameResume,
    GuiOn,
    GuiOff,
};

} // namespace model
