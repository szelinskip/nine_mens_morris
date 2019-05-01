#pragma once

#include <cstdint>

#include "GameBoard.hpp"

namespace model {

class GameState
{
public:
    GameState();
    ~GameState();

    GameState(const GameState&);
    GameState& operator=(const GameState&);
    GameState(GameState&&);
    GameState& operator=(GameState&&);

    bool isGameOverState() const;
    bool isBoardEqual(const GameState& other) const;
    void putChecker(const std::string& boardField, PlayerColor color);
private:
    GameBoard board;
    bool isFirstStage;
    uint8_t whiteLeftCheckers;
    uint8_t blackLeftCheckers;
};

} // namespace model
