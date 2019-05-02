#include "Action.hpp"

namespace model {

Action::Action(ActionType actionType)
    : actionType(actionType)
{
}

Action::~Action() = default;
Action::Action() = default;
Action::Action(const Action &) = default;
Action& Action::operator=(const Action &) = default;
Action::Action(Action &&) = default;
Action& Action::operator=(Action&&) = default;

ActionType Action::getType() const
{
    return actionType;
}

ActionInputProvided::ActionInputProvided(const std::string& boardField)
    : Action(ActionType::InputProvided)
    , boardField(boardField)
{
}

ActionInputProvided::~ActionInputProvided() = default;
ActionInputProvided::ActionInputProvided() = default;
ActionInputProvided::ActionInputProvided(const ActionInputProvided &) = default;
ActionInputProvided& ActionInputProvided::operator=(const ActionInputProvided &) = default;
ActionInputProvided::ActionInputProvided(ActionInputProvided &&) = default;
ActionInputProvided& ActionInputProvided::operator=(ActionInputProvided&&) = default;

const std::string& ActionInputProvided::getBoardField() const
{
    return boardField;
}

ActionInputReq::ActionInputReq(const bool firstStage, const bool millMove)
    : Action(ActionType::InputReq)
    , firstStage(firstStage)
    , millMove(millMove)
{
}

bool ActionInputReq::isFirstStage() const
{
    return firstStage;
}

bool ActionInputReq::isMillMove() const
{
    return millMove;
}

ActionInputReq::~ActionInputReq() = default;
ActionInputReq::ActionInputReq(const ActionInputReq &) = default;
ActionInputReq& ActionInputReq::operator=(const ActionInputReq &) = default;
ActionInputReq::ActionInputReq(ActionInputReq &&) = default;
ActionInputReq& ActionInputReq::operator=(ActionInputReq&&) = default;

ActionGameStart::ActionGameStart()
    : Action(ActionType::GameStart)
{
}

ActionGameStart::~ActionGameStart() = default;
ActionGameStart::ActionGameStart(const ActionGameStart &) = default;
ActionGameStart& ActionGameStart::operator=(const ActionGameStart &) = default;
ActionGameStart::ActionGameStart(ActionGameStart &&) = default;
ActionGameStart& ActionGameStart::operator=(ActionGameStart&&) = default;

ActionMoveDone::ActionMoveDone(const Move& move)
    : Action(ActionType::MoveDone)
    , move(move)
{
}

ActionMoveDone::~ActionMoveDone() = default;
ActionMoveDone::ActionMoveDone(const ActionMoveDone &) = default;
ActionMoveDone& ActionMoveDone::operator=(const ActionMoveDone &) = default;
ActionMoveDone::ActionMoveDone(ActionMoveDone &&) = default;
ActionMoveDone& ActionMoveDone::operator=(ActionMoveDone&&) = default;

const Move &ActionMoveDone::getMove() const
{
    return move;
}

} // namespace model
