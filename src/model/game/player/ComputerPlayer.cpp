#include "ComputerPlayer.hpp"

#include <memory>

#include <src/model/communication/Action.hpp>
#include <src/model/communication/ActionType.hpp>
#include <src/model/game/GameManager.hpp>

#include <iostream>

namespace model {

ComputerPlayer::ComputerPlayer(GameManager& gameManager,
                               const std::string& name,
                               PlayerColor color,
                               std::unique_ptr<ai::AiAlgorithm> aiAlg)
    : Player(gameManager, name, color)
    , aiAlg(std::move(aiAlg))
{
}

ComputerPlayer::~ComputerPlayer() = default;

void ComputerPlayer::makeMove(GameState& state)
{
    aiAlg->makeMove(state);
    // TODO send proper gui update

//    std::cout << __FUNCTION__ << std::endl;
//    auto req = std::make_unique<ActionInputReq>();
//    gameManager.putAction(std::move(req));
//    std::string boardField = gameManager.getInput();

//    // TODO handle invalid input
//    state.putChecker(boardField, color);
//    auto action = std::make_unique<ActionMoveDone>(boardField, color);
//    gameManager.putAction(std::move(action));
}

void ComputerPlayer::millMove(GameState& /*state*/)
{
    // nothing to do, potential mill move would had been done in makeMove()
}

} // namespace model
