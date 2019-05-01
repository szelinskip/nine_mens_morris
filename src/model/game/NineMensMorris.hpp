#pragma once

#include <memory>
#include <vector>

#include "GameState.hpp"

namespace model {
class Player;
} // namespace model

namespace model {

class NineMensMorris
{
public:
    NineMensMorris(std::unique_ptr<Player> whitePlayer, std::unique_ptr<Player> blackPlayer);
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
};

} // namespace model
