#include "HumanPlayer.hpp"

#include <memory>

#include <src/model/communication/Action.hpp>
#include <src/model/communication/ActionType.hpp>
#include <src/model/game/GameManager.hpp>

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
    auto req = std::make_unique<ActionInputReq>();
    gameManager.putAction(std::move(req));
    std::string boardField = gameManager.getInput();

    // TODO handle invalid input
    state.putChecker(boardField, color);
    auto action = std::make_unique<ActionMoveDone>(boardField, color);
    gameManager.putAction(std::move(action));
}

void HumanPlayer::millMove(GameState& /*state*/)
{
    //TODO
}

} // namespace model
