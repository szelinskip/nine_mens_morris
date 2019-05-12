#include "GameManager.hpp"

namespace model {

using namespace std::chrono_literals;

GameManager::GameManager() = default;
GameManager::~GameManager() = default;

bool GameManager::shouldStopGame() const
{
    return false;
}

void GameManager::putAction(ActionPtr /*action*/)
{
}

Move GameManager::getInput()
{
    return Move{};
}

void GameManager::beforeTurnActions(const uint32_t /*turnNum*/,
                                    const uint32_t /*whiteLeftCheckersToPut*/,
                                    const uint32_t /*blackLeftCheckersToPut*/,
                                    const uint32_t /*whiteLeftCheckersOnBoard*/,
                                    const uint32_t /*blackLeftCheckersOnBoard*/,
                                    const uint32_t /*whiteCheckersKilledByBlack*/,
                                    const uint32_t /*blackCheckersKilledByWhite*/)
{
}

void GameManager::afterTurnActions(std::chrono::milliseconds /*elapsed*/,
                                   const Move& /*lastMove*/,
                                   const uint32_t /*turnNum*/,
                                   const bool /*timeConstraintExceeded*/)
{
}

void GameManager::playersTurnAction(const Player* /*currentPlayer*/)
{
}

void GameManager::gameFinishedActions(const Player* /*winner*/)
{
}

} // namespace model
