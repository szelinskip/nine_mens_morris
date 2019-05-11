#pragma once

#include <string>

#include <src/model/game/player/PlayerColor.hpp>
#include <src/model/game/GameState.hpp>

namespace model {

namespace ai {

class EvalFunction
{
public:
    EvalFunction(const std::string& info);
    virtual ~EvalFunction();

    EvalFunction() = delete;
    EvalFunction(const EvalFunction&);
    EvalFunction& operator=(const EvalFunction&);
    EvalFunction(EvalFunction&&);
    EvalFunction& operator=(EvalFunction&&);

    virtual int evalGameState(const GameState& gameState, const PlayerColor who) = 0;
    virtual std::string getInfo() const;

protected:
    std::string info;
};

} // namespace ai
} // namespace model
