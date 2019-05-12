#pragma once

#include "EvalFunction.hpp"
#include <src/model/game/player/PlayerColor.hpp>
#include <src/model/game/GameState.hpp>

namespace model {

class GameState;

namespace ai {

class EvalFnLeftCheckersDiffAndMorris : public EvalFunction
{
public:
    EvalFnLeftCheckersDiffAndMorris();
    virtual ~EvalFnLeftCheckersDiffAndMorris() override;

    EvalFnLeftCheckersDiffAndMorris(const EvalFnLeftCheckersDiffAndMorris&);
    EvalFnLeftCheckersDiffAndMorris& operator=(const EvalFnLeftCheckersDiffAndMorris&);
    EvalFnLeftCheckersDiffAndMorris(EvalFnLeftCheckersDiffAndMorris&&);
    EvalFnLeftCheckersDiffAndMorris& operator=(EvalFnLeftCheckersDiffAndMorris&&);

    virtual int evalGameState(const GameState& gameState, const PlayerColor who) override;
};

} // namespace ai
} // namespace model
