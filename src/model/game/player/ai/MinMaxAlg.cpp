#include "MinMaxAlg.hpp"

#include <limits>

#include <src/model/game/GameState.hpp>

namespace model {
namespace ai {

MinMaxAlg::MinMaxAlg(const PlayerColor who, std::unique_ptr<EvalFunction> evalFn, const uint32_t depth)
    : AiAlgorithm(who, std::move(evalFn))
    , depth(depth)
{
}

MinMaxAlg::~MinMaxAlg() = default;
MinMaxAlg::MinMaxAlg(MinMaxAlg &&) = default;
MinMaxAlg &MinMaxAlg::operator=(MinMaxAlg &&) = default;

void MinMaxAlg::makeMove(GameState& gameState)
{
    // if below condition is true it means state provided for move make is already game over state
    if(gameState.isGameOverState())
        return;

    // maximizing
    int maxEval = std::numeric_limits<int>::min();
    uint32_t index = 0;
    std::vector<GameState> possibleStates = gameState.getAvailableStates(who);
    for(auto i = 0u; i < possibleStates.size(); i++)
    {
        int eval = minMax(possibleStates[i], 1, false);
        if(eval > maxEval)
        {
            maxEval = eval;
            index = i;
        }
    }
    gameState = possibleStates[index];
}

int MinMaxAlg::minMax(const GameState& gameState, const uint32_t currentDepth, bool isMaximizing)
{
    if(currentDepth == depth || gameState.isGameOverState())
        return evaluate(gameState);

    if(isMaximizing)
    {
        int maxEval = std::numeric_limits<int>::min();
        std::vector<GameState> possibleStates = gameState.getAvailableStates(who);
        for(auto& possibleState : possibleStates)
        {
            int eval = minMax(possibleState, depth + 1, false);
            maxEval = std::max(maxEval, eval);
        }
        return maxEval;
    }
    else  // minimizing
    {
        int minEval = std::numeric_limits<int>::max();
        std::vector<GameState> possibleStates = gameState.getAvailableStates(getOponent(who));
        for(auto& possibleState : possibleStates)
        {
            int eval = minMax(possibleState, depth + 1, true);
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }
}

int MinMaxAlg::evaluate(const GameState& gameState) const
{
    return evalFn->evalGameState(gameState, who);
}

} // namespace ai
} // namespace model
