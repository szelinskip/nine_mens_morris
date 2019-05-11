#pragma once

#include <memory>

#include <src/tools/logging/Logger.hpp>
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
                   std::unique_ptr<ai::AiAlgorithm> aiAlg,
                   tools::Logger& logger);
    virtual ~ComputerPlayer() override;

    ComputerPlayer() = delete;
    ComputerPlayer(const ComputerPlayer&) = delete;
    ComputerPlayer& operator=(const ComputerPlayer&) = delete;
    ComputerPlayer(ComputerPlayer&&) = delete;
    ComputerPlayer& operator=(ComputerPlayer&&) = delete;

    virtual bool makeMove(GameState& state) override;
    virtual bool millMove(GameState& state) override;
    virtual std::string getInfo() const override;

private:
    std::unique_ptr<ai::AiAlgorithm> aiAlg;
};

} // namespace model
