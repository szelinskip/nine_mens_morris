#pragma once

#include <cstdint>
#include <string>

namespace model {

enum class PlayerColor : uint8_t
{
    None,
    White,
    Black
};

std::string colorToStr(const PlayerColor color);

PlayerColor getOponent(const PlayerColor who);

} // namespace model
