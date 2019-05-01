#pragma once

#include <array>
#include <unordered_map>
#include <string>

#include "player/PlayerColor.hpp"

namespace model {

class GameBoard
{
public:
    GameBoard();
    ~GameBoard();

    GameBoard(const GameBoard&);
    GameBoard& operator=(const GameBoard&);
    GameBoard(GameBoard&&);
    GameBoard& operator=(GameBoard&&);

    PlayerColor& operator[](const std::string& position);

    bool operator==(const GameBoard& other) const;

private:
//    /std::array<PlayerColor, 24> boardBase;
    std::unordered_map<std::string, PlayerColor> boardBase;
};

} // namespace model
