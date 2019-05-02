#pragma once

#include <string>

#include "ActionType.hpp"
#include <src/model/game/GameBoard.hpp>
#include <src/model/game/player/PlayerColor.hpp>

namespace model {

class Action
{
public:
    Action(ActionType actionType);
    virtual ~Action();

    Action();
    Action(const Action&);
    Action& operator=(const Action&);
    Action(Action&&);
    Action& operator=(Action&&);

    ActionType getType() const;

private:
    ActionType actionType;
};

class ActionInputProvided : public Action
{
public:
    ActionInputProvided(const std::string& boardField);

    virtual ~ActionInputProvided();

    ActionInputProvided();
    ActionInputProvided(const ActionInputProvided&);
    ActionInputProvided& operator=(const ActionInputProvided&);
    ActionInputProvided(ActionInputProvided&&);
    ActionInputProvided& operator=(ActionInputProvided&&);

    const std::string& getBoardField() const;

private:
    std::string boardField;
};

class ActionInputReq : public Action
{
public:
    ActionInputReq(const bool firstStage, const bool millMove);

    virtual ~ActionInputReq();

    ActionInputReq(const ActionInputReq&);
    ActionInputReq& operator=(const ActionInputReq&);
    ActionInputReq(ActionInputReq&&);
    ActionInputReq& operator=(ActionInputReq&&);

    bool isFirstStage() const;
    bool isMillMove() const;
private:
    bool firstStage;
    bool millMove;
};

class ActionGameStart : public Action
{
public:
    ActionGameStart();

    virtual ~ActionGameStart();

    ActionGameStart(const ActionGameStart&);
    ActionGameStart& operator=(const ActionGameStart&);
    ActionGameStart(ActionGameStart&&);
    ActionGameStart& operator=(ActionGameStart&&);
};

class ActionMoveDone : public Action
{
public:
    ActionMoveDone(const Move& move);

    virtual ~ActionMoveDone();

    ActionMoveDone() = delete;
    ActionMoveDone(const ActionMoveDone&);
    ActionMoveDone& operator=(const ActionMoveDone&);
    ActionMoveDone(ActionMoveDone&&);
    ActionMoveDone& operator=(ActionMoveDone&&);

    const Move& getMove() const;

private:
    Move move;
};

} // namespace model
