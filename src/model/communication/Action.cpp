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

ActionGameStart::ActionGameStart(const PlayerType whitePlayerType,
                                 const PlayerHeuristic whitePlayerHeuristic,
                                 const uint32_t whitePlayerDepth,
                                 const PlayerType blackPlayerType,
                                 const PlayerHeuristic blackPlayerHeuristic,
                                 const uint32_t blackPlayerDepth)
    : Action(ActionType::GameStart)
    , whitePlayerType(whitePlayerType)
    , whitePlayerHeuristic(whitePlayerHeuristic)
    , whitePlayerDepth(whitePlayerDepth)
    , blackPlayerType(blackPlayerType)
    , blackPlayerHeuristic(blackPlayerHeuristic)
    , blackPlayerDepth(blackPlayerDepth)
{
}

ActionGameStart::~ActionGameStart() = default;
ActionGameStart::ActionGameStart(const ActionGameStart &) = default;
ActionGameStart& ActionGameStart::operator=(const ActionGameStart &) = default;
ActionGameStart::ActionGameStart(ActionGameStart &&) = default;
ActionGameStart& ActionGameStart::operator=(ActionGameStart&&) = default;

ActionGameStop::ActionGameStop()
    : Action(ActionType::GameStop)
{
}

ActionGameStop::~ActionGameStop() = default;
ActionGameStop::ActionGameStop(const ActionGameStop &) = default;
ActionGameStop& ActionGameStop::operator=(const ActionGameStop &) = default;
ActionGameStop::ActionGameStop(ActionGameStop &&) = default;
ActionGameStop& ActionGameStop::operator=(ActionGameStop&&) = default;

ActionGamePause::ActionGamePause()
    : Action(ActionType::GamePause)
{
}

ActionGamePause::~ActionGamePause() = default;
ActionGamePause::ActionGamePause(const ActionGamePause &) = default;
ActionGamePause& ActionGamePause::operator=(const ActionGamePause &) = default;
ActionGamePause::ActionGamePause(ActionGamePause &&) = default;
ActionGamePause& ActionGamePause::operator=(ActionGamePause&&) = default;

ActionGameResume::ActionGameResume()
    : Action(ActionType::GameResume)
{
}

ActionGameResume::~ActionGameResume() = default;
ActionGameResume::ActionGameResume(const ActionGameResume &) = default;
ActionGameResume& ActionGameResume::operator=(const ActionGameResume &) = default;
ActionGameResume::ActionGameResume(ActionGameResume &&) = default;
ActionGameResume& ActionGameResume::operator=(ActionGameResume&&) = default;

ActionGuiOn::ActionGuiOn()
    : Action(ActionType::GuiOn)
{
}

ActionGuiOn::~ActionGuiOn() = default;
ActionGuiOn::ActionGuiOn(const ActionGuiOn &) = default;
ActionGuiOn& ActionGuiOn::operator=(const ActionGuiOn &) = default;
ActionGuiOn::ActionGuiOn(ActionGuiOn &&) = default;
ActionGuiOn& ActionGuiOn::operator=(ActionGuiOn&&) = default;

ActionGuiOff::ActionGuiOff()
    : Action(ActionType::GuiOff)
{
}

ActionGuiOff::~ActionGuiOff() = default;
ActionGuiOff::ActionGuiOff(const ActionGuiOff &) = default;
ActionGuiOff& ActionGuiOff::operator=(const ActionGuiOff &) = default;
ActionGuiOff::ActionGuiOff(ActionGuiOff &&) = default;
ActionGuiOff& ActionGuiOff::operator=(ActionGuiOff&&) = default;

ActionWaitOnGame::ActionWaitOnGame()
    : Action(ActionType::WaitOnGame)
{
}

ActionWaitOnGame::~ActionWaitOnGame() = default;
ActionWaitOnGame::ActionWaitOnGame(const ActionWaitOnGame &) = default;
ActionWaitOnGame& ActionWaitOnGame::operator=(const ActionWaitOnGame &) = default;
ActionWaitOnGame::ActionWaitOnGame(ActionWaitOnGame &&) = default;
ActionWaitOnGame& ActionWaitOnGame::operator=(ActionWaitOnGame&&) = default;

} // namespace model
