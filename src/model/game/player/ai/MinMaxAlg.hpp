#pragma once

#include <chrono>
#include <cstdint>

#include "AiAlgorithm.hpp"
#include <src/model/game/player/PlayerColor.hpp>
#include <src/model/game/GameState.hpp>

namespace model {
namespace ai {

class MinMaxAlg : public AiAlgorithm
{
public:
    MinMaxAlg(const PlayerColor who,
              std::unique_ptr<EvalFunction> evalFn,
              const uint32_t depth,
              const std::chrono::seconds searchTimeLimit);
    virtual ~MinMaxAlg() override;

    MinMaxAlg() = delete;
    MinMaxAlg(const MinMaxAlg&) = delete;
    MinMaxAlg& operator=(const MinMaxAlg&) = delete;
    MinMaxAlg(MinMaxAlg&&);
    MinMaxAlg& operator=(MinMaxAlg&&);

    virtual void makeMove(GameState& gameState) override;
    virtual std::string getInfo() const override;

private:
    int minMax(GameState& gameState, const uint32_t currentDepth, bool isMaximizing);
    int evaluate(const GameState& gameState) const;

    uint32_t depth;
};

} // namespace ai
} // namespace model
