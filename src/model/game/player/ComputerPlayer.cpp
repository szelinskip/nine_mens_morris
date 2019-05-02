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
    auto action = std::make_unique<ActionMoveDone>(state.getLastMove());
    gameManager.putAction(std::move(action));
}

void ComputerPlayer::millMove(GameState& /*state*/)
{
    // nothing to do, potential mill move would had been done in makeMove()
}

} // namespace model
