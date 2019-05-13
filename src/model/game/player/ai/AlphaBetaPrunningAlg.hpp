#pragma once

#include <chrono>
#include <cstdint>

#include "AiAlgorithm.hpp"
#include <src/model/game/player/PlayerColor.hpp>
#include <src/model/game/GameState.hpp>

namespace model {
namespace ai {

class AlphaBetaPrunningAlg : public AiAlgorithm
{
public:
    AlphaBetaPrunningAlg(const PlayerColor who,
                         std::unique_ptr<EvalFunction> evalFn,
                         const uint32_t depth,
                         const std::chrono::seconds searchTimeLimit);
    virtual ~AlphaBetaPrunningAlg() override;

    AlphaBetaPrunningAlg() = delete;
    AlphaBetaPrunningAlg(const AlphaBetaPrunningAlg&) = delete;
    AlphaBetaPrunningAlg& operator=(const AlphaBetaPrunningAlg&) = delete;
    AlphaBetaPrunningAlg(AlphaBetaPrunningAlg&&);
    AlphaBetaPrunningAlg& operator=(AlphaBetaPrunningAlg&&);

    virtual void makeMove(GameState& gameState) override;
    virtual std::string getInfo() const override;
private:
    int minMaxEnhancedAlphaBetaPrunning(GameState& gameState,
                                        const uint32_t currentDepth,
                                        int alpha,
                                        int beta,
                                        bool isMaximizing);
    int evaluate(const GameState& gameState) const;

    uint32_t depth;
};

} // namespace ai
} // namespace model
