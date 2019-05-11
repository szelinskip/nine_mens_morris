#pragma once

#include <functional>

#include "EvalFunction.hpp"
#include <src/model/game/player/PlayerColor.hpp>
#include <src/model/game/GameState.hpp>

namespace model {

class GameState;

namespace ai {

class EvalFnGenericLambda : public EvalFunction
{
public:
    EvalFnGenericLambda(const std::function<int(const GameState&, const PlayerColor)>& evalFn,
                        const std::string& info);
    virtual ~EvalFnGenericLambda() override;

    EvalFnGenericLambda() = delete;
    EvalFnGenericLambda(const EvalFnGenericLambda&);
    EvalFnGenericLambda& operator=(const EvalFnGenericLambda&);
    EvalFnGenericLambda(EvalFnGenericLambda&&);
    EvalFnGenericLambda& operator=(EvalFnGenericLambda&&);

    virtual int evalGameState(const GameState& gameState, const PlayerColor who) override;

private:
    std::function<int(const GameState&, const PlayerColor)> evalFn;
};

} // namespace ai
} // namespace model
