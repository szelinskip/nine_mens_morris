#pragma once

#include <memory>

#include "Player.hpp"
#include "ai/AiAlgorithm.hpp"

namespace model {
class GameManager;
} // namespace model

namespace model {

class ComputerPlayer : public Player
{
public:
    ComputerPlayer(GameManager& gameManager,
                   const std::string& name,
                   PlayerColor color,
                   std::unique_ptr<ai::AiAlgorithm> aiAlg);
    virtual ~ComputerPlayer() override;

    ComputerPlayer() = delete;
    ComputerPlayer(const ComputerPlayer&) = delete;
    ComputerPlayer& operator=(const ComputerPlayer&) = delete;
    ComputerPlayer(ComputerPlayer&&) = delete;
    ComputerPlayer& operator=(ComputerPlayer&&) = delete;

    virtual bool makeMove(GameState& state) override;
    virtual bool millMove(GameState& state) override;

private:
    std::unique_ptr<ai::AiAlgorithm> aiAlg;
};

} // namespace model
