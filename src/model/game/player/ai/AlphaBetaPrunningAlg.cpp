#include "AlphaBetaPrunningAlg.hpp"

#include <algorithm>
#include <limits>

#include <src/model/game/GameState.hpp>

#include <iostream>

namespace model {
namespace ai {

AlphaBetaPrunningAlg::AlphaBetaPrunningAlg(const PlayerColor who,
                                           std::unique_ptr<EvalFunction> evalFn,
                                           const uint32_t depth,
                                           const std::chrono::seconds searchTimeLimit)
    : AiAlgorithm("AlphaBeta", who, std::move(evalFn), searchTimeLimit)
    , depth(depth)
{
}

AlphaBetaPrunningAlg::~AlphaBetaPrunningAlg() = default;
AlphaBetaPrunningAlg::AlphaBetaPrunningAlg(AlphaBetaPrunningAlg &&) = default;
AlphaBetaPrunningAlg &AlphaBetaPrunningAlg::operator=(AlphaBetaPrunningAlg &&) = default;

void AlphaBetaPrunningAlg::makeMove(GameState& gameState)
{
    visitedStates = 0;
    prunedStates = 0;
    timeConstraintExceeded = false;
    // if below condition is true it means state provided for move make is already game over state
    if(gameState.isGameOverState())
        return;

    // maximizing
    int maxEval = std::numeric_limits<int>::min();
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    uint32_t index = 0;

    // start time measure
    startAlgTp = SteadyClock::now();

    std::vector<GameState> possibleStates = gameState.getAvailableStates(who);

//    std::stable_sort(possibleStates.begin(),
//                     possibleStates.end(),
//                     [this](const auto& lhs, const auto& rhs)
//                     {
//                         return evaluate(lhs) > evaluate(rhs);
//                     });

    if(possibleStates.size() == 0)
    {
        gameState.setGameOverDueToNoPossibleMovements();
        return;
    }

    for(auto i = 0u; i < possibleStates.size(); i++)
    {
        int eval = minMaxEnhancedAlphaBetaPrunning(possibleStates[i], 1, alpha, beta, false);
        if(eval > maxEval)
        {
            maxEval = eval;
            index = i;
        }
        alpha = std::max(alpha, eval);
        if(beta <= alpha)
        {
            prunedStates += (possibleStates.size() - i - 1);
            break;
        }
    }
    gameState = possibleStates[index];
}

std::string AlphaBetaPrunningAlg::getInfo() const
{
    return AiAlgorithm::getInfo() + ", depth: " + std::to_string(depth);
}

int AlphaBetaPrunningAlg::minMaxEnhancedAlphaBetaPrunning(GameState& gameState,
                                                          const uint32_t currentDepth,
                                                          int alpha,
                                                          int beta,
                                                          bool isMaximizing)
{
    visitedStates++;
    if(currentDepth == depth || gameState.isGameOverState() || checkTimeConstraint())
        return evaluate(gameState);

    if(isMaximizing)
    {
        std::vector<GameState> possibleStates = gameState.getAvailableStates(who);
        if(possibleStates.size() == 0)
        {
            gameState.setGameOverDueToNoPossibleMovements();
            return evaluate(gameState);
        }

        int maxEval = std::numeric_limits<int>::min();

//        std::stable_sort(possibleStates.begin(),
//                         possibleStates.end(),
//                         [this](const auto& lhs, const auto& rhs)
//                         {
//                             return evaluate(lhs) > evaluate(rhs);
//                         });

        for(auto i = 0u; i < possibleStates.size(); i++)
        {
            int eval = minMaxEnhancedAlphaBetaPrunning(possibleStates[i], currentDepth + 1, alpha, beta, false);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if(beta <= alpha)
            {
                prunedStates += (possibleStates.size() - i - 1);
                break;
            }
        }
        return maxEval;
    }
    else  // minimizing
    {
        std::vector<GameState> possibleStates = gameState.getAvailableStates(getOponent(who));
        if(possibleStates.size() == 0)
        {
            gameState.setGameOverDueToNoPossibleMovements();
            return evaluate(gameState);
        }

        int minEval = std::numeric_limits<int>::max();

//        std::stable_sort(possibleStates.begin(),
//                         possibleStates.end(),
//                         [this](const auto& lhs, const auto& rhs)
//                         {
//                             return evaluate(lhs) < evaluate(rhs);
//                         });

        for(auto i = 0u; i < possibleStates.size(); i++)
        {
            int eval = minMaxEnhancedAlphaBetaPrunning(possibleStates[i], currentDepth + 1, alpha, beta, true);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if(beta <= alpha)
            {
                prunedStates += (possibleStates.size() - i - 1);
                break;
            }
        }
        return minEval;
    }
}

int AlphaBetaPrunningAlg::evaluate(const GameState& gameState) const
{
    return evalFn->evalGameState(gameState, who);
}

} // namespace ai
} // namespace model
