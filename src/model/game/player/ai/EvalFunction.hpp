#pragma once

#include <src/model/game/player/PlayerColor.hpp>
#include <src/model/game/GameState.hpp>

namespace model {

namespace ai {

class EvalFunction
{
public:
    EvalFunction();
    virtual ~EvalFunction();

    EvalFunction(const EvalFunction&);
    EvalFunction& operator=(const EvalFunction&);
    EvalFunction(EvalFunction&&);
    EvalFunction& operator=(EvalFunction&&);

    virtual int evalGameState(const GameState& gameState, const PlayerColor who) = 0;
};

} // namespace ai
} // namespace model
