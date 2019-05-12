#include "Player.hpp"

#include <src/model/game/GameManager.hpp>

namespace model {

Player::Player(GameManager& gameManager, const std::string& name, PlayerColor color, tools::Logger& logger)
    : gameManager(gameManager)
    , name(name)
    , color(color)
    , movesNumber(0)
    , visitedStates(0)
    , prunedStates(0)
    , logger(logger)
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

std::string Player::getInfo() const
{
    return "Color: " + colorToStr(color) + ", name: " + name;
}

uint32_t Player::getVisitedStates() const
{
    return visitedStates;
}

uint32_t Player::getPrunedStates() const
{
    return prunedStates;
}

void Player::incrementMovesNumber()
{
    movesNumber++;
}

uint32_t Player::getMovesNumber() const
{
    return movesNumber;
}

} // namespace model
