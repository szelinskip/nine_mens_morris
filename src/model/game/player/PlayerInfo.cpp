#include "PlayerInfo.hpp"

namespace model {

PlayerType convertStringToPlayerType(const std::string& playerTypeStr)
{
    if(playerTypeStr == "Human player")
        return PlayerType::HumanPlayer;
    else if(playerTypeStr == "AI MinMax")
        return PlayerType::AiMinMax;
    else if(playerTypeStr == "AI AlphaBeta")
        return PlayerType::AiAlphaBeta;
    else
        return PlayerType::Unsupported;
}

PlayerHeuristic convertStringToPlayerHeuristic(const std::string &playerHeuristicStr)
{
    if(playerHeuristicStr == "None")
        return PlayerHeuristic::None;
    else if(playerHeuristicStr == "Left checkers diff")
        return PlayerHeuristic::LeftCheckersDiff;
    else
        return PlayerHeuristic::Unsupported;
}

} // namespace model
