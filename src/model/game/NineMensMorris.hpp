#pragma once

#include <memory>
#include <chrono>
#include <vector>

#include "GameState.hpp"
#include <src/tools/logging/Logger.hpp>

namespace model {
class Player;
class GameManager;
} // namespace model

namespace model {

class NineMensMorris
{
public:
    NineMensMorris(std::unique_ptr<Player> whitePlayer,
                   std::unique_ptr<Player> blackPlayer,
                   GameManager* gameManager,
                   tools::Logger& logger);
    ~NineMensMorris();

    NineMensMorris() = delete;
    NineMensMorris(const NineMensMorris&) = delete;
    NineMensMorris& operator=(const NineMensMorris&) = delete;
    NineMensMorris(NineMensMorris&&) = delete;
    NineMensMorris& operator=(NineMensMorris&&) = delete;

    void startGame();

private:
    bool checkGameOverCondition() const;
    Player* getCurrentPlayer() const;
    bool isGameEndedWithDraw() const;
    bool lastMoveCreatedMill() const;

    std::unique_ptr<Player> whitePlayer;
    std::unique_ptr<Player> blackPlayer;
    Player* currentPlayer;
    GameState gameState;
    std::vector<GameState> gameStatesHistory;

    GameManager* gameManager;

    uint32_t turnNum;

    tools::Logger& logger;
    tools::Logger gameMovesLogger;
    tools::Logger gameStatesLogger;
};

} // namespace model
