#pragma once

#include <string>

#include <src/model/game/GameState.hpp>
#include "PlayerColor.hpp"

namespace model {
class GameManager;
} // namespace model

namespace model {

class Player
{
public:
    Player(GameManager& gameManager, const std::string& name, PlayerColor color);
    virtual ~Player();

    Player() = delete;
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&) = delete;
    Player& operator=(Player&&) = delete;

    virtual bool makeMove(GameState& state) = 0;
    virtual bool millMove(GameState& state) = 0;
    virtual std::string getName() const;
    virtual PlayerColor getColor() const;

protected:
    GameManager& gameManager;
    std::string name;
    PlayerColor color;
};

} // namespace model
