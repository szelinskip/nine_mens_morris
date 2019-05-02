#pragma once

#include "EvalFunction.hpp"
#include <src/model/game/player/PlayerColor.hpp>
#include <src/model/game/GameState.hpp>

namespace model {

class GameState;

namespace ai {

class EvalFnLeftCheckersDiff : public EvalFunction
{
public:
    virtual int evalGameState(const GameState& gameState, const PlayerColor who) override;
};

} // namespace ai
} // namespace model
