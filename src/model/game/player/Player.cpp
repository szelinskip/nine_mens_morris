#include "Player.hpp"

#include <src/model/game/GameManager.hpp>

namespace model {

Player::Player(GameManager& gameManager, const std::string& name, PlayerColor color)
    : gameManager(gameManager)
    , name(name)
    , color(color)
{
}

Player::~Player() = default;

std::string Player::getName() const
{
    return name;
}

PlayerColor Player::getColor() const
{
    return color;
}

} // namespace model
