#include "GameState.hpp"

namespace model {

GameState::GameState()
    : board()
    , isFirstStage(true)
    , whiteLeftCheckersToPut(9)
    , blackLeftCheckersToPut(9)
    , whiteLeftCheckersOnBoard(0)
    , blackLeftCheckersOnBoard(0)
    , whiteCheckersKilledByBlack(0)
    , blackCheckersKilledByWhite(0)
{
}

GameState::GameState(GameBoard&& board,
                     const bool isFirstStage,
                     const uint8_t whiteLeftCheckersToPut,
                     const uint8_t blackLeftCheckersToPut,
                     const uint8_t whiteLeftCheckersOnBoard,
                     const uint8_t blackLeftCheckersOnBoard,
                     const uint8_t whiteCheckersKilledByBlack,
                     const uint8_t blackCheckersKilledByWhite)
    : board(std::move(board))
    , isFirstStage(isFirstStage)
    , whiteLeftCheckersToPut(whiteLeftCheckersToPut)
    , blackLeftCheckersToPut(blackLeftCheckersToPut)
    , whiteLeftCheckersOnBoard(whiteLeftCheckersOnBoard)
    , blackLeftCheckersOnBoard(blackLeftCheckersOnBoard)
    , whiteCheckersKilledByBlack(whiteCheckersKilledByBlack)
    , blackCheckersKilledByWhite(blackCheckersKilledByWhite)
{

}

GameState::GameState(const GameState &otherGameState,
                     GameBoard &&board,
                     const uint8_t whiteLeftCheckersOnBoard,
                     const uint8_t blackLeftCheckersOnBoard,
                     const uint8_t whiteCheckersKilledByBlack,
                     const uint8_t blackCheckersKilledByWhite)
    : board(std::move(board))
    , isFirstStage(otherGameState.isFirstStage)
    , whiteLeftCheckersToPut(otherGameState.whiteLeftCheckersToPut)
    , blackLeftCheckersToPut(otherGameState.blackLeftCheckersToPut)
    , whiteLeftCheckersOnBoard(whiteLeftCheckersOnBoard)
    , blackLeftCheckersOnBoard(blackLeftCheckersOnBoard)
    , whiteCheckersKilledByBlack(whiteCheckersKilledByBlack)
    , blackCheckersKilledByWhite(blackCheckersKilledByWhite)
{
}

GameState::GameState(const GameState &otherGameState, GameBoard &&board)
    : board(std::move(board))
    , isFirstStage(otherGameState.isFirstStage)
    , whiteLeftCheckersToPut(otherGameState.whiteLeftCheckersToPut)
    , blackLeftCheckersToPut(otherGameState.blackLeftCheckersToPut)
    , whiteLeftCheckersOnBoard(otherGameState.whiteLeftCheckersOnBoard)
    , blackLeftCheckersOnBoard(otherGameState.blackLeftCheckersOnBoard)
    , whiteCheckersKilledByBlack(otherGameState.whiteCheckersKilledByBlack)
    , blackCheckersKilledByWhite(otherGameState.blackCheckersKilledByWhite)
{

}

GameState::~GameState() = default;
GameState::GameState(const GameState&) = default;
GameState& GameState::operator=(const GameState&) = default;
GameState::GameState(GameState&&) = default;
GameState& GameState::operator=(GameState&&) = default;

bool GameState::isGameOverState() const
{
    if((whiteLeftCheckersOnBoard < 3 || blackLeftCheckersOnBoard < 3) && whiteLeftCheckersToPut == 0 && blackLeftCheckersToPut == 0)
        return true;
    return false;
}

bool GameState::isBoardEqual(const GameState& other) const
{
    return board == other.board;
}

void GameState::putChecker(const std::string& boardField, const PlayerColor color)
{
    board.setColorOnField(boardField, color);
}

std::vector<GameState> GameState::getAvailableStates(const PlayerColor who) const
{
    uint8_t leftCheckersToPut;
//    uint8_t leftCheckersOnBoard;
//    uint8_t oponentKilledCheckers;
    if(who == PlayerColor::White)
    {
        leftCheckersToPut = whiteLeftCheckersToPut;
//        leftCheckersOnBoard = whiteLeftCheckersOnBoard;
//        oponentKilledCheckers = blackCheckersKilledByWhite;
    }
    else // who == PlayerColor::Black
    {
        leftCheckersToPut = blackLeftCheckersToPut;
//        leftCheckersOnBoard = blackLeftCheckersOnBoard;
//        oponentKilledCheckers = whiteCheckersKilledByBlack;
    }

    if(isFirstStage && leftCheckersToPut > 0)
        return getFirstStageAvailableStates(who);
    else
        return getMidEndGameAvailableStates(who);
}

void GameState::setBoard(const GameBoard &gameBoard)
{
    this->board = gameBoard;
}

void GameState::setIsFirstStage(const bool isFirstStage)
{
    this->isFirstStage = isFirstStage;
}

void GameState::setWhiteLeftCheckersToPut(const uint8_t whiteLeftCheckersToPut)
{
    this->whiteLeftCheckersToPut = whiteLeftCheckersToPut;
}

void GameState::setBlackLeftCheckersToPut(const uint8_t blackLeftCheckersToPut)
{
    this->blackLeftCheckersToPut = blackLeftCheckersToPut;
}

void GameState::setWhiteLeftCheckersOnBoard(const uint8_t whiteLeftCheckersOnBoard)
{
    this->whiteLeftCheckersOnBoard = whiteLeftCheckersOnBoard;
}

void GameState::setBlackLeftCheckersOnBoard(const uint8_t blackLeftCheckersOnBoard)
{
    this->blackLeftCheckersOnBoard = blackLeftCheckersOnBoard;
}

void GameState::setWhiteCheckersKilledByBlack(const uint8_t whiteCheckersKilledByBlack)
{
    this->whiteCheckersKilledByBlack = whiteCheckersKilledByBlack;
}

void GameState::setBlackCheckersKilledByWhite(const uint8_t blackCheckersKilledByWhite)
{
    this->blackCheckersKilledByWhite = blackCheckersKilledByWhite;
}

uint32_t GameState::getWhiteLeftCheckersToPut() const
{
    return static_cast<uint32_t>(whiteLeftCheckersToPut);
}

uint32_t GameState::getBlackLeftCheckersToPut() const
{
    return static_cast<uint32_t>(blackLeftCheckersToPut);
}

uint32_t GameState::getWhiteLeftCheckersOnBoard() const
{
    return static_cast<uint32_t>(whiteLeftCheckersOnBoard);
}

uint32_t GameState::getBlackLeftCheckersOnBoard() const
{
    return static_cast<uint32_t>(blackLeftCheckersOnBoard);
}

uint32_t GameState::getWhiteCheckersKilledByBlack() const
{
    return static_cast<uint32_t>(whiteCheckersKilledByBlack);
}

uint32_t GameState::getBlackCheckersKilledByWhite() const
{
    return static_cast<uint32_t>(blackCheckersKilledByWhite);
}

bool GameState::lastMoveCreatedMill() const
{
    return board.lastMoveFormedMill();
}

int GameState::getLeftCheckersOnBoard(const PlayerColor who) const
{
    if(who == PlayerColor::White)
    {
        return static_cast<int>(whiteLeftCheckersOnBoard);
    }
    else // who == PlayerColor::Black
    {
        return static_cast<int>(blackLeftCheckersOnBoard);
    }
}

const Move &GameState::getLastMove() const
{
    return board.getLastMove();
}

bool GameState::isInFirstStage(const PlayerColor who) const
{
    if(who == PlayerColor::White)
    {
        return whiteLeftCheckersToPut > 0u;
    }
    else // who == PlayerColor::Black
    {
        return blackLeftCheckersToPut > 0u;
    }
}

void GameState::applyMove(const Move& move)
{
    if(move.fromField.empty())  // first stage move
    {
        if(!move.toField.empty())
        {
            if(move.who == PlayerColor::White)
            {
                whiteLeftCheckersToPut--;
                whiteLeftCheckersOnBoard++;
            }
            else // who == PlayerColor::Black
            {
                blackLeftCheckersToPut--;
                blackLeftCheckersOnBoard++;
            }
            board.setColorOnField(move.toField, move.who);
        }
    }
    else  // regular checker move
    {
        if(!move.toField.empty())
        {
            board.moveChecker(move.fromField, move.toField);
        }
    }
    // oponent checker taken cause of mill
    if(!move.fieldOponentsCheckerTaken.empty())
    {
        if(move.who == PlayerColor::White)
        {
            blackLeftCheckersOnBoard--;
        }
        else // who == PlayerColor::Black
        {
            whiteLeftCheckersOnBoard--;
        }
        board.setColorOnField(move.fieldOponentsCheckerTaken, PlayerColor::None);
    }
}

std::string GameState::getStrRepr() const
{
    std::string boardStr = board.getStrRepr();
    boardStr += "\n\nwhite left checkers to put: " + std::to_string(static_cast<uint32_t>(whiteLeftCheckersToPut)) +
                "\nblack left checkers to put: " + std::to_string(static_cast<uint32_t>(blackLeftCheckersToPut)) +
                "\nwhite left checkers on board: " + std::to_string(static_cast<uint32_t>(whiteLeftCheckersOnBoard)) +
                "\nblack left checkers on board: " + std::to_string(static_cast<uint32_t>(blackLeftCheckersOnBoard)) +
                "\nwhite checkers killed by black: " + std::to_string(static_cast<uint32_t>(whiteCheckersKilledByBlack)) +
                "\nblack checkers killed by white: " + std::to_string(static_cast<uint32_t>(blackCheckersKilledByWhite));
    return boardStr;
}

PlayerColor GameState::getOponent(const PlayerColor color) const
{
    if(color == PlayerColor::White)
        return PlayerColor::Black;
    else  // color == PlayerColor::Black
        return PlayerColor::White;
}

std::vector<GameState> GameState::getFirstStageAvailableStates(const PlayerColor who) const
{
    std::vector<std::string> freeBoardFields = board.getFreeFields();
    std::vector<GameState> possibleStates;
    possibleStates.reserve(freeBoardFields.size());
    uint8_t whiteLeftCheckersToPut;
    uint8_t whiteLeftCheckersOnBoard;
    uint8_t blackLeftCheckersToPut;
    uint8_t blackLeftCheckersOnBoard;
    if(who == PlayerColor::White)
    {
        whiteLeftCheckersToPut = this->whiteLeftCheckersToPut - 1;
        blackLeftCheckersToPut = this->blackLeftCheckersToPut;
        whiteLeftCheckersOnBoard = this->whiteLeftCheckersOnBoard + 1;
        blackLeftCheckersOnBoard = this->blackLeftCheckersOnBoard;
    }
    else
    {
        whiteLeftCheckersToPut = this->whiteLeftCheckersToPut;
        blackLeftCheckersToPut = this->blackLeftCheckersToPut - 1;
        whiteLeftCheckersOnBoard = this->whiteLeftCheckersOnBoard;
        blackLeftCheckersOnBoard = this->blackLeftCheckersOnBoard + 1;
    }
    for(const auto& freeField : freeBoardFields)
    {
        GameBoard possibleBoard{board};
        possibleBoard.setColorOnField(freeField, who);
        GameState possibleState(std::move(possibleBoard),
                                this->isFirstStage,
                                whiteLeftCheckersToPut,
                                blackLeftCheckersToPut,
                                whiteLeftCheckersOnBoard,
                                blackLeftCheckersOnBoard,
                                this->whiteCheckersKilledByBlack,
                                this->blackCheckersKilledByWhite);
        if(!possibleState.lastMoveCreatedMill())
        {
            possibleStates.emplace_back(std::move(possibleState));
        }
        else
        {
            std::vector<GameState> possibleStatesAfterMill = getStatesAfterMillFormed(possibleState, who);
            possibleStates.reserve(static_cast<uint32_t>(possibleStates.size()) +
                                   static_cast<uint32_t>(
                                       distance(possibleStatesAfterMill.begin(),
                                                possibleStatesAfterMill.end())));
            possibleStates.insert(possibleStates.end(),
                                  std::make_move_iterator(possibleStatesAfterMill.begin()),
                                  std::make_move_iterator(possibleStatesAfterMill.end()));
        }
    }

    return possibleStates;
}

std::vector<GameState> GameState::getMidEndGameAvailableStates(const PlayerColor who) const
{
    std::vector<GameState> possibleStates;
    std::vector<std::string> playerCheckers = board.getCheckersWithColor(who);
    for(const auto& checker : playerCheckers)
    {
        std::vector<std::string> possibleMoves = getPossibleMoves(checker, who);
        for(const auto& possibleMove : possibleMoves)
        {
            GameBoard possibleBoard{board};
            possibleBoard.moveChecker(checker, possibleMove);
            GameState possibleState(*this, std::move(possibleBoard));
            if(!possibleState.lastMoveCreatedMill())
            {
                possibleStates.emplace_back(std::move(possibleState));
            }
            else
            {
                std::vector<GameState> possibleStatesAfterMill = getStatesAfterMillFormed(possibleState, who);
                possibleStates.reserve(static_cast<uint32_t>(possibleStates.size()) +
                                       static_cast<uint32_t>(
                                           distance(possibleStatesAfterMill.begin(),
                                                    possibleStatesAfterMill.end())));
                possibleStates.insert(possibleStates.end(),
                                      std::make_move_iterator(possibleStatesAfterMill.begin()),
                                      std::make_move_iterator(possibleStatesAfterMill.end()));
            }
        }
    }
    return possibleStates;
}

std::vector<GameState> GameState::getStatesAfterMillFormed(const GameState& millState, const PlayerColor who) const
{
    std::vector<GameState> possibleStates;
    PlayerColor oponent = getOponent(who);
    std::vector<std::string> oponentsCheckers = board.getCheckersWithColor(oponent);
    std::vector<std::string> oponentCheckersNotInMill;
    for(auto& checker : oponentsCheckers)
    {
        if(!board.isCheckerInMill(checker))
            oponentCheckersNotInMill.push_back(std::move(checker));
    }
    std::vector<std::string>* checkersPossibleToTake;
    if(!oponentCheckersNotInMill.empty())
        checkersPossibleToTake = &oponentCheckersNotInMill;
    else
        checkersPossibleToTake = &oponentsCheckers;
    possibleStates.reserve((*checkersPossibleToTake).size());
    uint8_t whiteLeftCheckersOnBoard;
    uint8_t blackLeftCheckersOnBoard;
    uint8_t whiteCheckersKilledByBlack;
    uint8_t blackCheckersKilledByWhite;
    if(who == PlayerColor::White)
    {
        whiteLeftCheckersOnBoard = millState.whiteLeftCheckersOnBoard;
        blackLeftCheckersOnBoard = millState.blackLeftCheckersOnBoard - 1;
        blackCheckersKilledByWhite = millState.blackCheckersKilledByWhite + 1;
    }
    else
    {
        whiteLeftCheckersOnBoard = millState.whiteLeftCheckersOnBoard - 1;
        blackLeftCheckersOnBoard = millState.blackLeftCheckersOnBoard;
        whiteCheckersKilledByBlack = millState.whiteCheckersKilledByBlack + 1;
    }
    for(const auto& checker : *checkersPossibleToTake)
    {
        GameBoard gameBoard{millState.board};
        gameBoard.setColorOnField(checker, PlayerColor::None);
        possibleStates.emplace_back(millState,
                                    std::move(gameBoard),
                                    whiteLeftCheckersOnBoard,
                                    blackLeftCheckersOnBoard,
                                    whiteCheckersKilledByBlack,
                                    blackCheckersKilledByWhite);
    }
    return possibleStates;
}

std::vector<std::string> GameState::getPossibleMoves(const std::string &checker, const PlayerColor who) const
{
    uint8_t leftCheckersOnBoard;
    if(who == PlayerColor::White)
    {
        leftCheckersOnBoard = this->whiteLeftCheckersOnBoard;
    }
    else
    {
        leftCheckersOnBoard = this->blackLeftCheckersOnBoard;
    }
    if(leftCheckersOnBoard > 3)
    {
        return board.getFreeNeighbours(checker);
    }
    else
    {
        return board.getFreeFields();
    }

}

} // namesapce model
