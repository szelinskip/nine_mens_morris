#pragma once

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
    AiAlgorithm(const std::string& name, const PlayerColor who, std::unique_ptr<EvalFunction>&& evalFn);
    virtual ~AiAlgorithm();

    AiAlgorithm() = delete;
    AiAlgorithm(const AiAlgorithm&) = delete;
    AiAlgorithm& operator=(const AiAlgorithm&) = delete;
    AiAlgorithm(AiAlgorithm&&);
    AiAlgorithm& operator=(AiAlgorithm&&);

    virtual void makeMove(GameState& gameState) = 0;
    virtual std::string getInfo() const;

protected:
    std::string name;
    PlayerColor who;
    std::unique_ptr<EvalFunction> evalFn;
};

} // namespace ai
} // namespace model
