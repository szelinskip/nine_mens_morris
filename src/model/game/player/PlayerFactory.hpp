#pragma once

#include <cstdint>
#include <memory>

#include "PlayerColor.hpp"
#include "PlayerInfo.hpp"

namespace model {

class GameManager;
class Player;

class PlayerFactory
{
public:
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
};

} // namespace model
