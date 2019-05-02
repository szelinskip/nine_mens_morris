#pragma once

#include <memory>

#include <src/model/game/player/PlayerColor.hpp>
#include "EvalFunction.hpp"
#include <src/model/game/GameState.hpp>

namespace model {
namespace ai {

class AiAlgorithm
{
public:
    AiAlgorithm(const PlayerColor who, std::unique_ptr<EvalFunction>&& evalFn);
    virtual ~AiAlgorithm();

    AiAlgorithm() = delete;
    AiAlgorithm(const AiAlgorithm&) = delete;
    AiAlgorithm& operator=(const AiAlgorithm&) = delete;
    AiAlgorithm(AiAlgorithm&&);
    AiAlgorithm& operator=(AiAlgorithm&&);

    virtual void makeMove(GameState& gameState) = 0;

protected:
    PlayerColor who;
    std::unique_ptr<EvalFunction> evalFn;
};

} // namespace ai
} // namespace model
