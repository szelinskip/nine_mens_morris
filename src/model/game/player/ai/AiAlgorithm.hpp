#pragma once

#include <chrono>
#include <memory>
#include <string>

#include <src/model/game/player/PlayerColor.hpp>
#include "EvalFunction.hpp"
#include <src/model/game/GameState.hpp>

namespace model {
namespace ai {

class AiAlgorithm
{
public:
    AiAlgorithm(const std::string& name,
                const PlayerColor who,
                std::unique_ptr<EvalFunction>&& evalFn,
                const std::chrono::seconds searchTimeLimit);
    virtual ~AiAlgorithm();

    AiAlgorithm() = delete;
    AiAlgorithm(const AiAlgorithm&) = delete;
    AiAlgorithm& operator=(const AiAlgorithm&) = delete;
    AiAlgorithm(AiAlgorithm&&);
    AiAlgorithm& operator=(AiAlgorithm&&);

    virtual void makeMove(GameState& gameState) = 0;
    virtual uint64_t getVisitedStates() const;
    virtual uint64_t getPrunedStates() const;
    virtual bool wasSearchTimeExceeded() const;
    virtual std::string getInfo() const;

protected:
    virtual bool checkTimeConstraint();

    std::string name;
    PlayerColor who;
    std::unique_ptr<EvalFunction> evalFn;

    uint64_t visitedStates;
    uint64_t prunedStates;

    using SteadyClock = std::chrono::steady_clock;
    using Tp = std::chrono::steady_clock::time_point;

    std::chrono::seconds searchTimeLimit;
    Tp startAlgTp;
    bool timeConstraintExceeded;
};

} // namespace ai
} // namespace model
