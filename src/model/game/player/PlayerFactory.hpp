#pragma once

#include <chrono>
#include <cstdint>
#include <memory>

#include <src/tools/logging/Logger.hpp>
#include "PlayerColor.hpp"
#include "PlayerInfo.hpp"

namespace model {

class GameManager;
class Player;

class PlayerFactory
{
public:
    PlayerFactory(tools::Logger& logger, const std::chrono::seconds timeConstraint);
    ~PlayerFactory();

    PlayerFactory() = delete;
    PlayerFactory(const PlayerFactory&) = delete;
    PlayerFactory& operator=(const PlayerFactory&) = delete;
    PlayerFactory(PlayerFactory&&) = delete;
    PlayerFactory& operator=(PlayerFactory&&) = delete;

    std::unique_ptr<Player> makePlayer(GameManager& gameManager,
                                       const std::string& name,
                                       const PlayerColor color,
                                       const PlayerType playerType,
                                       const PlayerHeuristic playerHeuristic,
                                       const uint32_t playerDepth) const;
private:
    std::unique_ptr<Player> makeHumanPlayer(GameManager& gameManager,
                                            const std::string& name,
                                            const PlayerColor color) const;
    std::unique_ptr<Player> makeComputerPlayer(GameManager& gameManager,
                                               const std::string &name,
                                               PlayerColor color,
                                               const std::string& algType,
                                               const PlayerHeuristic playerHeuristic,
                                               const uint32_t playerDepth) const;

    std::chrono::seconds timeConstraint;
    tools::Logger& logger;
};

} // namespace model
