#include "PlayerColor.hpp"

namespace model {

std::string colorToStr(const model::PlayerColor color)
{
    switch (color)
    {
        case PlayerColor::White :
            return "W";
        case PlayerColor::Black :
            return "B";
        default:
            return "_";
    }
}

PlayerColor getOponent(const PlayerColor who)
{
    switch (who)
    {
        case PlayerColor::White :
            return PlayerColor::Black;
        case PlayerColor::Black :
            return PlayerColor::White;
        default:
            return PlayerColor::None;
    }
}

} // namespace model
