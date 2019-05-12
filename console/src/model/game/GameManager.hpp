#pragma once

#include <chrono>
#include <memory>

#include <src/model/communication/Action.hpp>

namespace model {

using ActionPtr = std::unique_ptr<Action>;

class Player;

class GameManager
{
public:
    GameManager();
    ~GameManager();

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
    GameManager(GameManager&&) = delete;
    GameManager& operator=(GameManager&&) = delete;

    bool shouldStopGame() const;

    void putAction(ActionPtr action);
    Move getInput();

    void beforeTurnActions(const uint32_t turnNum,
                           const uint32_t whiteLeftCheckersToPut,
                           const uint32_t blackLeftCheckersToPut,
                           const uint32_t whiteLeftCheckersOnBoard,
                           const uint32_t blackLeftCheckersOnBoard,
                           const uint32_t whiteCheckersKilledByBlack,
                           const uint32_t blackCheckersKilledByWhite);
    void afterTurnActions(std::chrono::milliseconds elapsed, const Move& lastMove);
    void playersTurnAction(const Player* currentPlayer);
    void gameFinishedActions(const Player* winner);

};

}
