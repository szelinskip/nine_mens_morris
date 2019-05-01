#pragma once

#include <cstdint>

namespace model {

enum class ActionType : uint8_t
{
    InputProvided,
    InputReq,
    InputResp,
    GameStart,
    MoveDone,
};

} // namespace model
