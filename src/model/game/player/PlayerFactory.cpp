#include "PlayerFactory.hpp"

#include "Player.hpp"
#include "HumanPlayer.hpp"
#include "ComputerPlayer.hpp"
#include <src/model/game/GameManager.hpp>
#include "ai/EvalFunction.hpp"
#include "ai/EvalFnLeftCheckersDiff.hpp"
#include "ai/EvalFnLeftCheckersDiffAndMorris.hpp"
#include "ai/EvalFnCheckersArrangement.hpp"
#include "ai/AiAlgorithm.hpp"
#include "ai/MinMaxAlg.hpp"
#include "ai/AlphaBetaPrunningAlg.hpp"

namespace model {

PlayerFactory::PlayerFactory(tools::Logger& logger)
    : logger(logger)
{
}

PlayerFactory::~PlayerFactory() = default;

std::unique_ptr<Player> PlayerFactory::makePlayer(GameManager& gameManager,
                                                  const std::string& name,
                                                  const PlayerColor color,
                                                  const PlayerType playerType,
                                                  const PlayerHeuristic playerHeuristic,
                                                  const uint32_t playerDepth) const
{
    switch (playerType)
    {
        case PlayerType::HumanPlayer:
            return makeHumanPlayer(gameManager, name, color);
        case PlayerType::AiMinMax:
            return makeComputerPlayer(gameManager, name, color, "MinMax", playerHeuristic, playerDepth);
        case PlayerType::AiAlphaBeta:
            return makeComputerPlayer(gameManager, name, color, "AlphaBeta", playerHeuristic, playerDepth);
        default:
            return nullptr;
    }
}

std::unique_ptr<Player> PlayerFactory::makeHumanPlayer(GameManager& gameManager,
                                                       const std::string& name,
                                                       const PlayerColor color) const
{
    return std::make_unique<HumanPlayer>(gameManager, name, color, logger);
}

std::unique_ptr<Player> PlayerFactory::makeComputerPlayer(GameManager& gameManager,
                                                          const std::string &name,
                                                          PlayerColor color,
                                                          const std::string& algType,
                                                          const PlayerHeuristic playerHeuristic,
                                                          const uint32_t playerDepth) const
{
    std::unique_ptr<ai::EvalFunction> evalFn;
    switch(playerHeuristic)
    {
        case PlayerHeuristic::LeftCheckersDiff:
            evalFn = std::make_unique<ai::EvalFnLeftCheckersDiff>();
            break;
        case PlayerHeuristic::LeftCheckersDiffAndMorris:
            evalFn = std::make_unique<ai::EvalFnLeftCheckersDiffAndMorris>();
            break;
        case PlayerHeuristic::CheckersArrangement:
            evalFn = std::make_unique<ai::EvalFnCheckersArrangement>();
            break;
        default:
            evalFn = nullptr;
            break;
    }
    std::unique_ptr<ai::AiAlgorithm> aiAlg;
    if(algType == "MinMax")
        aiAlg = std::make_unique<ai::MinMaxAlg>(color, std::move(evalFn), playerDepth);
    else  // (algType == "AlphaBeta")
        aiAlg = std::make_unique<ai::AlphaBetaPrunningAlg>(color, std::move(evalFn), playerDepth);

    return std::make_unique<ComputerPlayer>(gameManager, name, color, std::move(aiAlg), logger);
}

} // namespace model
