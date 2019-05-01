#include "GameBoard.hpp"

namespace model {

GameBoard::GameBoard()
    : boardBase{{"1a", PlayerColor::None}, {"1d", PlayerColor::None}, {"1g", PlayerColor::None},
                {"2b", PlayerColor::None}, {"2d", PlayerColor::None}, {"2f", PlayerColor::None},
                {"3c", PlayerColor::None}, {"3d", PlayerColor::None}, {"3e", PlayerColor::None},
                {"4a", PlayerColor::None}, {"4b", PlayerColor::None}, {"4c", PlayerColor::None},
                {"4e", PlayerColor::None}, {"4f", PlayerColor::None}, {"4g", PlayerColor::None},
                {"5c", PlayerColor::None}, {"5d", PlayerColor::None}, {"5e", PlayerColor::None},
                {"6b", PlayerColor::None}, {"6d", PlayerColor::None}, {"6f", PlayerColor::None},
                {"7a", PlayerColor::None}, {"7a", PlayerColor::None}, {"7g", PlayerColor::None}}
{
}

PlayerColor& GameBoard::operator[](const std::string& position)
{
    return boardBase[position];
}

bool GameBoard::operator==(const GameBoard& other) const
{
    return boardBase == other.boardBase;
}

GameBoard::~GameBoard() = default;
GameBoard::GameBoard(const GameBoard&) = default;
GameBoard& GameBoard::operator=(const GameBoard&) = default;
GameBoard::GameBoard(GameBoard&&) = default;
GameBoard& GameBoard::operator=(GameBoard&&) = default;

}
