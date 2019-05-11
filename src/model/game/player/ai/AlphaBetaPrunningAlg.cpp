#include "AlphaBetaPrunningAlg.hpp"

#include <limits>

#include <src/model/game/GameState.hpp>

#include <iostream>

namespace model {
namespace ai {

AlphaBetaPrunningAlg::AlphaBetaPrunningAlg(const PlayerColor who, std::unique_ptr<EvalFunction> evalFn, const uint32_t depth)
    : AiAlgorithm(who, std::move(evalFn))
    , depth(depth)
{
}

AlphaBetaPrunningAlg::~AlphaBetaPrunningAlg() = default;
AlphaBetaPrunningAlg::AlphaBetaPrunningAlg(AlphaBetaPrunningAlg &&) = default;
AlphaBetaPrunningAlg &AlphaBetaPrunningAlg::operator=(AlphaBetaPrunningAlg &&) = default;

void AlphaBetaPrunningAlg::makeMove(GameState& gameState)
{
    // if below condition is true it means state provided for move make is already game over state
    if(gameState.isGameOverState())
        return;

    // maximizing
    int maxEval = std::numeric_limits<int>::min();
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    uint32_t index = 0;
    std::vector<GameState> possibleStates = gameState.getAvailableStates(who);
//    std::cout << "Possible states (" << possibleStates.size() << ") at depth 0 from base state: " << std::endl;
//    std::cout << gameState.getStrRepr() << std::endl;
//    for(auto i = 0u; i < possibleStates.size(); i++)
//    {
//        std::cout << "num: " << (i+1) << std::endl;
//        std::cout << possibleStates[i].getStrRepr() << std::endl;
//    }
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
            break;
    }
    gameState = possibleStates[index];
}

int AlphaBetaPrunningAlg::minMaxEnhancedAlphaBetaPrunning(const GameState& gameState,
                                                          const uint32_t currentDepth,
                                                          int alpha,
                                                          int beta,
                                                          bool isMaximizing)
{
    if(currentDepth == depth || gameState.isGameOverState())
        return evaluate(gameState);

    if(isMaximizing)
    {
        int maxEval = std::numeric_limits<int>::min();
        std::vector<GameState> possibleStates = gameState.getAvailableStates(who);
//        std::cout << "Possible states (" << possibleStates.size() << ") at depth " << currentDepth << " from base state: " << std::endl;
//        std::cout << gameState.getStrRepr() << std::endl;
//        for(auto i = 0u; i < possibleStates.size(); i++)
//        {
//            std::cout << "num: " << (i+1) << std::endl;
//            std::cout << possibleStates[i].getStrRepr() << std::endl;
//        }
        for(auto& possibleState : possibleStates)
        {
            int eval = minMaxEnhancedAlphaBetaPrunning(possibleState, currentDepth + 1, alpha, beta, false);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if(beta <= alpha)
                break;
        }
        return maxEval;
    }
    else  // minimizing
    {
        int minEval = std::numeric_limits<int>::max();
        std::vector<GameState> possibleStates = gameState.getAvailableStates(getOponent(who));
//        std::cout << "Possible states (" << possibleStates.size() << ") at depth " << currentDepth << " from base state: " << std::endl;
//        std::cout << gameState.getStrRepr() << std::endl;
//        for(auto i = 0u; i < possibleStates.size(); i++)
//        {
//            std::cout << "num: " << (i+1) << std::endl;
//            std::cout << possibleStates[i].getStrRepr() << std::endl;
//        }
        for(auto& possibleState : possibleStates)
        {
            int eval = minMaxEnhancedAlphaBetaPrunning(possibleState, currentDepth + 1, alpha, beta, true);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if(beta <= alpha)
                break;
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
