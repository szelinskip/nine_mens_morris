#pragma once

#include "Player.hpp"

namespace model {
class GameManager;
} // namespace model

namespace model {

class HumanPlayer : public Player
{
public:
    HumanPlayer(GameManager& gameManager, const std::string& name, PlayerColor color);
    virtual ~HumanPlayer() override;

    HumanPlayer() = delete;
    HumanPlayer(const HumanPlayer&) = delete;
    HumanPlayer& operator=(const HumanPlayer&) = delete;
    HumanPlayer(HumanPlayer&&) = delete;
    HumanPlayer& operator=(HumanPlayer&&) = delete;

    virtual bool makeMove(GameState& state) override;
    virtual bool millMove(GameState& state) override;
};

} // namespace model
