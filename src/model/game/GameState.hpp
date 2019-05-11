#pragma once

#include <cstdint>
#include <vector>

#include "GameBoard.hpp"

namespace model {

class GameState
{
public:
    GameState();
    GameState(GameBoard&& board,
              const bool isFirstStage,
              const uint8_t whiteLeftCheckersToPut,
              const uint8_t blackLeftCheckersToPut,
              const uint8_t whiteLeftCheckersOnBoard,
              const uint8_t blackLeftCheckersOnBoard,
              const uint8_t whiteCheckersKilledByBlack,
              const uint8_t blackCheckersKilledByWhite);
    GameState(const GameState& otherGameState,
              GameBoard&& board,
              const uint8_t whiteLeftCheckersOnBoard,
              const uint8_t blackLeftCheckersOnBoard);
    GameState(const GameState& otherGameState,
              GameBoard&& board);
    ~GameState();

    GameState(const GameState&);
    GameState& operator=(const GameState&);
    GameState(GameState&&);
    GameState& operator=(GameState&&);

    bool isGameOverState() const;
    bool isBoardEqual(const GameState& other) const;
    void putChecker(const std::string& boardField, const PlayerColor color);
    std::vector<GameState> getAvailableStates(const PlayerColor who) const;

    void setBoard(const GameBoard& gameBoard);
    void setIsFirstStage(const bool isFirstStage);
    void setWhiteLeftCheckersToPut(const uint8_t whiteLeftCheckersToPut);
    void setBlackLeftCheckersToPut(const uint8_t blackLeftCheckersToPut);
    void setWhiteLeftCheckersOnBoard(const uint8_t whiteLeftCheckersOnBoard);
    void setBlackLeftCheckersOnBoard(const uint8_t blackLeftCheckersOnBoard);
    void setWhiteCheckersKilledByBlack(const uint8_t whiteCheckersKilledByBlack);
    void setBlackCheckersKilledByWhite(const uint8_t blackCheckersKilledByWhite);

    uint32_t getWhiteLeftCheckersToPut() const;
    uint32_t getBlackLeftCheckersToPut() const;
    uint32_t getWhiteLeftCheckersOnBoard() const;
    uint32_t getBlackLeftCheckersOnBoard() const;
    uint32_t getWhiteCheckersKilledByBlack() const;
    uint32_t getBlackCheckersKilledByWhite() const;

    bool lastMoveCreatedMill() const;
    int getLeftCheckersOnBoard(const PlayerColor who) const;
    const Move& getLastMove() const;
    bool isInFirstStage(const PlayerColor who) const;
    void applyMove(const Move& move);

    std::string getStrRepr() const;

private:
    PlayerColor getOponent(const PlayerColor color) const;
    std::vector<GameState> getFirstStageAvailableStates(const PlayerColor who) const;
    std::vector<GameState> getMidEndGameAvailableStates(const PlayerColor who) const;
    std::vector<GameState> getStatesAfterMillFormed(const GameState& millState, const PlayerColor who) const;
    std::vector<std::string> getPossibleMoves(const std::string& checker, const PlayerColor color) const;

    GameBoard board;
    bool isFirstStage;
    uint8_t whiteLeftCheckersToPut;
    uint8_t blackLeftCheckersToPut;
    uint8_t whiteLeftCheckersOnBoard;
    uint8_t blackLeftCheckersOnBoard;
    uint8_t whiteCheckersKilledByBlack;
    uint8_t blackCheckersKilledByWhite;
};

} // namespace model
