#include "GameState.hpp"

namespace model {

GameState::GameState()
    : board()
    , isFirstStage(true)
    , whiteLeftCheckers(9)
    , blackLeftCheckers(9)
{
    // TODO
}

bool GameState::isGameOverState() const
{
    if(whiteLeftCheckers < 3 || blackLeftCheckers < 3)
        return true;
    return false;
}

bool GameState::isBoardEqual(const GameState& other) const
{
    return board == other.board;
}

void GameState::putChecker(const std::string& boardField, PlayerColor color)
{
    board[boardField] = color;
}

GameState::~GameState() = default;
GameState::GameState(const GameState&) = default;
GameState& GameState::operator=(const GameState&) = default;
GameState::GameState(GameState&&) = default;
GameState& GameState::operator=(GameState&&) = default;

} // namesapce model
