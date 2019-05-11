#pragma once

#include <string>

#include <src/model/game/GameState.hpp>
#include <src/tools/logging/Logger.hpp>
#include "PlayerColor.hpp"

namespace model {
class GameManager;
} // namespace model

namespace model {

class Player
{
public:
    Player(GameManager& gameManager, const std::string& name, PlayerColor color, tools::Logger& logger);
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
    virtual std::string getInfo() const;
    void incrementMovesNumber();
    uint32_t getMovesNumber() const;

protected:
    GameManager& gameManager;
    std::string name;
    PlayerColor color;
    uint32_t movesNumber;

    tools::Logger& logger;
};

} // namespace model
