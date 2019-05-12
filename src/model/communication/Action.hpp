#pragma once

#include <chrono>
#include <string>

#include "ActionType.hpp"
#include <src/model/game/GameBoard.hpp>
#include <src/model/game/player/PlayerColor.hpp>
#include <src/model/game/player/PlayerInfo.hpp>

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

class ActionGameStart : public Action
{
public:
    ActionGameStart(const PlayerType whitePlayerType,
                    const PlayerHeuristic whitePlayerHeuristic,
                    const uint32_t whitePlayerDepth,
                    const PlayerType blackPlayerType,
                    const PlayerHeuristic blackPlayerHeuristic,
                    const uint32_t blackPlayerDepth,
                    const std::chrono::seconds timeConstraint);

    virtual ~ActionGameStart();

    ActionGameStart(const ActionGameStart&);
    ActionGameStart& operator=(const ActionGameStart&);
    ActionGameStart(ActionGameStart&&);
    ActionGameStart& operator=(ActionGameStart&&);

    PlayerType whitePlayerType;
    PlayerHeuristic whitePlayerHeuristic;
    uint32_t whitePlayerDepth;

    PlayerType blackPlayerType;
    PlayerHeuristic blackPlayerHeuristic;
    uint32_t blackPlayerDepth;

    std::chrono::seconds timeConstraint;
};

class ActionGameStop : public Action
{
public:
    ActionGameStop();

    virtual ~ActionGameStop();

    ActionGameStop(const ActionGameStop&);
    ActionGameStop& operator=(const ActionGameStop&);
    ActionGameStop(ActionGameStop&&);
    ActionGameStop& operator=(ActionGameStop&&);
};

class ActionGamePause : public Action
{
public:
    ActionGamePause();

    virtual ~ActionGamePause();

    ActionGamePause(const ActionGamePause&);
    ActionGamePause& operator=(const ActionGamePause&);
    ActionGamePause(ActionGamePause&&);
    ActionGamePause& operator=(ActionGamePause&&);
};

class ActionGameResume : public Action
{
public:
    ActionGameResume();

    virtual ~ActionGameResume();

    ActionGameResume(const ActionGameResume&);
    ActionGameResume& operator=(const ActionGameResume&);
    ActionGameResume(ActionGameResume&&);
    ActionGameResume& operator=(ActionGameResume&&);
};

class ActionGuiOn : public Action
{
public:
    ActionGuiOn();

    virtual ~ActionGuiOn();

    ActionGuiOn(const ActionGuiOn&);
    ActionGuiOn& operator=(const ActionGuiOn&);
    ActionGuiOn(ActionGuiOn&&);
    ActionGuiOn& operator=(ActionGuiOn&&);
};

class ActionGuiOff : public Action
{
public:
    ActionGuiOff();

    virtual ~ActionGuiOff();

    ActionGuiOff(const ActionGuiOff&);
    ActionGuiOff& operator=(const ActionGuiOff&);
    ActionGuiOff(ActionGuiOff&&);
    ActionGuiOff& operator=(ActionGuiOff&&);
};

class ActionWaitOnGame : public Action
{
public:
    ActionWaitOnGame();

    virtual ~ActionWaitOnGame();

    ActionWaitOnGame(const ActionWaitOnGame&);
    ActionWaitOnGame& operator=(const ActionWaitOnGame&);
    ActionWaitOnGame(ActionWaitOnGame&&);
    ActionWaitOnGame& operator=(ActionWaitOnGame&&);
};

} // namespace model
