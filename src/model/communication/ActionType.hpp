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
    WaitOnGame,
};

constexpr const char* actionTypeToString(const ActionType actionType)
{
    switch(actionType)
    {
        case ActionType::InputProvided:
            return "ActionType::InputProvided";
        case ActionType::InputReq:
            return "ActionType::InputReq";
        case ActionType::InputResp:
            return "ActionType::InputResp";
        case ActionType::MoveDone:
            return "ActionType::MoveDone";
        case ActionType::GameStart:
            return "ActionType::GameStart";
        case ActionType::GameStop:
            return "ActionType::GameStop";
        case ActionType::GamePause:
            return "ActionType::GamePause";
        case ActionType::GameResume:
            return "ActionType::GameResume";
        case ActionType::GuiOn:
            return "ActionType::GuiOn";
        case ActionType::GuiOff:
            return "ActionType::GuiOff";
        default:
            return "Unknown ActionType";
    }
}

} // namespace model
