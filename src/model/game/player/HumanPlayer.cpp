#include "HumanPlayer.hpp"

#include <memory>

#include <src/model/communication/Action.hpp>
#include <src/model/communication/ActionType.hpp>
#include <src/model/game/GameManager.hpp>
#include <src/model/game/Move.hpp>

#include <iostream>

namespace model {

HumanPlayer::HumanPlayer(GameManager& gameManager, const std::string& name, PlayerColor color, tools::Logger& logger)
    : Player(gameManager, name, color, logger)
{
}

HumanPlayer::~HumanPlayer() = default;

bool HumanPlayer::makeMove(GameState& state)
{
    logger.log("%s", __FUNCTION__);
    auto req = std::make_unique<ActionInputReq>(state.isInFirstStage(color), false);
    gameManager.putAction(std::move(req));
    Move move = gameManager.getInput();
    move.who = color;

    // TODO handle invalid input
    if(move.isEmpty())
        return false;
    state.applyMove(move);
    auto action = std::make_unique<ActionMoveDone>(move);
    gameManager.putAction(std::move(action));
    return true;
}

bool HumanPlayer::millMove(GameState& state)
{
    logger.log("%s", __FUNCTION__);
    auto req = std::make_unique<ActionInputReq>(state.isInFirstStage(color), true);
    gameManager.putAction(std::move(req));
    Move move = gameManager.getInput();
    move.who = color;

    if(move.isEmpty())
        return false;

    // TODO handle invalid input
    state.applyMove(move);
    auto action = std::make_unique<ActionMoveDone>(move);
    gameManager.putAction(std::move(action));
    return true;
}

} // namespace model
