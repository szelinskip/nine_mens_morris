#pragma once

#include "EvalFunction.hpp"
#include <src/model/game/player/PlayerColor.hpp>
#include <src/model/game/GameState.hpp>

namespace model {

class GameState;

namespace ai {

class EvalFnCheckersArrangement : public EvalFunction
{
public:
    EvalFnCheckersArrangement();
    virtual ~EvalFnCheckersArrangement() override;

    EvalFnCheckersArrangement(const EvalFnCheckersArrangement&);
    EvalFnCheckersArrangement& operator=(const EvalFnCheckersArrangement&);
    EvalFnCheckersArrangement(EvalFnCheckersArrangement&&);
    EvalFnCheckersArrangement& operator=(EvalFnCheckersArrangement&&);

    virtual int evalGameState(const GameState& gameState, const PlayerColor who) override;
};

} // namespace ai
} // namespace model
