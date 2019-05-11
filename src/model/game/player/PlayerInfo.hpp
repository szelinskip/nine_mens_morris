#pragma once

#include <string>

namespace model {

enum class PlayerType
{
    HumanPlayer,
    AiMinMax,
    AiAlphaBeta,
    Unsupported,
};

PlayerType convertStringToPlayerType(const std::string& playerTypeStr);

enum class PlayerHeuristic
{
    None,
    LeftCheckersDiff,
    Unsupported,
};

PlayerHeuristic convertStringToPlayerHeuristic(const std::string& playerHeuristicStr);

} // namespace model
