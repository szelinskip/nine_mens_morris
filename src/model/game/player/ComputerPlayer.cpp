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
                               std::unique_ptr<ai::AiAlgorithm> aiAlg,
                               tools::Logger& logger)
    : Player(gameManager, name, color, logger)
    , aiAlg(std::move(aiAlg))
{
}

ComputerPlayer::~ComputerPlayer() = default;

bool ComputerPlayer::makeMove(GameState& state)
{
    aiAlg->makeMove(state);
    visitedStates = aiAlg->getVisitedStates();
    prunedStates = aiAlg->getPrunedStates();
    auto action = std::make_unique<ActionMoveDone>(state.getLastMove());
    gameManager.putAction(std::move(action));
    return true;
}

bool ComputerPlayer::millMove(GameState& /*state*/)
{
    // nothing to do, potential mill move would had been done in makeMove()
    return true;
}

std::string ComputerPlayer::getInfo() const
{
    return Player::getInfo() + ", ai alg: " + aiAlg->getInfo();
}

} // namespace model
