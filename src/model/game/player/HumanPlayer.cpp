#include "HumanPlayer.hpp"

#include <memory>

#include <src/model/communication/Action.hpp>
#include <src/model/communication/ActionType.hpp>
#include <src/model/game/GameManager.hpp>
#include <src/model/game/Move.hpp>

#include <iostream>

namespace model {

HumanPlayer::HumanPlayer(GameManager& gameManager, const std::string& name, PlayerColor color)
    : Player(gameManager, name, color)
{
}

HumanPlayer::~HumanPlayer() = default;

void HumanPlayer::makeMove(GameState& state)
{
    std::cout << __FUNCTION__ << std::endl;
    auto req = std::make_unique<ActionInputReq>(state.isInFirstStage(color), false);
    gameManager.putAction(std::move(req));
    Move move = gameManager.getInput();
    move.who = color;

    // TODO handle invalid input
    state.applyMove(move);
    auto action = std::make_unique<ActionMoveDone>(move);
    gameManager.putAction(std::move(action));
}

void HumanPlayer::millMove(GameState& state)
{
    std::cout << __FUNCTION__ << std::endl;
    auto req = std::make_unique<ActionInputReq>(state.isInFirstStage(color), true);
    gameManager.putAction(std::move(req));
    Move move = gameManager.getInput();
    move.who = color;

    // TODO handle invalid input
    state.applyMove(move);
    auto action = std::make_unique<ActionMoveDone>(move);
    gameManager.putAction(std::move(action));
}

} // namespace model
