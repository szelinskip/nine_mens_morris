#include "GameBoard.hpp"

namespace model {

GameBoard::GameBoard()
    : boardBase{{"1a", {"1a", PlayerColor::None, nullptr, nullptr}}, {"1d", {"1d", PlayerColor::None, nullptr, nullptr}},
                {"1g", {"1g", PlayerColor::None, nullptr, nullptr}}, {"2b", {"2b", PlayerColor::None, nullptr, nullptr}},
                {"2d", {"2d", PlayerColor::None, nullptr, nullptr}}, {"2f", {"2f", PlayerColor::None, nullptr, nullptr}},
                {"3c", {"3c", PlayerColor::None, nullptr, nullptr}}, {"3d", {"3d", PlayerColor::None, nullptr, nullptr}},
                {"3e", {"3e", PlayerColor::None, nullptr, nullptr}}, {"4a", {"4a", PlayerColor::None, nullptr, nullptr}},
                {"4b", {"4b", PlayerColor::None, nullptr, nullptr}}, {"4c", {"4c", PlayerColor::None, nullptr, nullptr}},
                {"4e", {"4e", PlayerColor::None, nullptr, nullptr}}, {"4f", {"4f", PlayerColor::None, nullptr, nullptr}},
                {"4g", {"4g", PlayerColor::None, nullptr, nullptr}}, {"5c", {"5c", PlayerColor::None, nullptr, nullptr}},
                {"5d", {"5d", PlayerColor::None, nullptr, nullptr}}, {"5e", {"5e", PlayerColor::None, nullptr, nullptr}},
                {"6b", {"6b", PlayerColor::None, nullptr, nullptr}}, {"6d", {"6d", PlayerColor::None, nullptr, nullptr}},
                {"6f", {"6f", PlayerColor::None, nullptr, nullptr}}, {"7a", {"7a", PlayerColor::None, nullptr, nullptr}},
                {"7d", {"7d", PlayerColor::None, nullptr, nullptr}}, {"7g", {"7g", PlayerColor::None, nullptr, nullptr}}}
{
    makeFieldsRowsColumnsCoupling();
}

GameBoard::GameBoard(const GameBoard &other)
    : boardBase(other.boardBase)
    , lastMove(other.lastMove)
{
    makeFieldsRowsColumnsCoupling();
}

GameBoard &GameBoard::operator=(const GameBoard &other)
{
    boardBase = other.boardBase;
    lastMove = other.lastMove;
    makeFieldsRowsColumnsCoupling();
    return *this;
}

GameBoard::GameBoard(GameBoard &&other)
    : boardBase(std::move(other.boardBase))
    , lastMove(std::move(other.lastMove))
{
    makeFieldsRowsColumnsCoupling();
}

GameBoard &GameBoard::operator=(GameBoard &&other)
{
    boardBase = std::move(other.boardBase);
    lastMove = std::move(other.lastMove);
    makeFieldsRowsColumnsCoupling();
    return *this;
}

GameBoard::~GameBoard() = default;

void GameBoard::makeFieldsRowsColumnsCoupling()
{
    rows = {{{{&boardBase["1a"], &boardBase["1d"], &boardBase["1g"]}},
            {{&boardBase["2b"], &boardBase["2d"], &boardBase["2f"]}},
            {{&boardBase["3c"], &boardBase["3d"], &boardBase["3e"]}},
            {{&boardBase["4a"], &boardBase["4b"], &boardBase["4c"]}},
            {{&boardBase["4e"], &boardBase["4f"], &boardBase["4g"]}},
            {{&boardBase["5c"], &boardBase["5d"], &boardBase["5e"]}},
            {{&boardBase["6b"], &boardBase["6d"], &boardBase["6f"]}},
            {{&boardBase["7a"], &boardBase["7d"], &boardBase["7g"]}}}};
    columns = {{{{&boardBase["1a"], &boardBase["4a"], &boardBase["7a"]}},
                {{&boardBase["2b"], &boardBase["4b"], &boardBase["6b"]}},
                {{&boardBase["3c"], &boardBase["4c"], &boardBase["5c"]}},
                {{&boardBase["1d"], &boardBase["2d"], &boardBase["3d"]}},
                {{&boardBase["5d"], &boardBase["6d"], &boardBase["7d"]}},
                {{&boardBase["3e"], &boardBase["4e"], &boardBase["5e"]}},
                {{&boardBase["2f"], &boardBase["4f"], &boardBase["6f"]}},
                {{&boardBase["1g"], &boardBase["4g"], &boardBase["7g"]}}}};
    boardBase["1a"].rowFieldLies = &rows[0]; boardBase["1a"].columnFieldLies = &columns[0];
    boardBase["1d"].rowFieldLies = &rows[0]; boardBase["1d"].columnFieldLies = &columns[3];
    boardBase["1g"].rowFieldLies = &rows[0]; boardBase["1g"].columnFieldLies = &columns[7];
    boardBase["2b"].rowFieldLies = &rows[1]; boardBase["2b"].columnFieldLies = &columns[1];
    boardBase["2d"].rowFieldLies = &rows[1]; boardBase["2d"].columnFieldLies = &columns[3];
    boardBase["2f"].rowFieldLies = &rows[1]; boardBase["2f"].columnFieldLies = &columns[6];
    boardBase["3c"].rowFieldLies = &rows[2]; boardBase["3c"].columnFieldLies = &columns[2];
    boardBase["3d"].rowFieldLies = &rows[2]; boardBase["3d"].columnFieldLies = &columns[3];
    boardBase["3e"].rowFieldLies = &rows[2]; boardBase["3e"].columnFieldLies = &columns[5];
    boardBase["4a"].rowFieldLies = &rows[3]; boardBase["4a"].columnFieldLies = &columns[0];
    boardBase["4b"].rowFieldLies = &rows[3]; boardBase["4b"].columnFieldLies = &columns[1];
    boardBase["4c"].rowFieldLies = &rows[3]; boardBase["4c"].columnFieldLies = &columns[2];
    boardBase["4e"].rowFieldLies = &rows[4]; boardBase["4e"].columnFieldLies = &columns[5];
    boardBase["4f"].rowFieldLies = &rows[4]; boardBase["4f"].columnFieldLies = &columns[6];
    boardBase["4g"].rowFieldLies = &rows[4]; boardBase["4g"].columnFieldLies = &columns[7];
    boardBase["5c"].rowFieldLies = &rows[5]; boardBase["5c"].columnFieldLies = &columns[2];
    boardBase["5d"].rowFieldLies = &rows[5]; boardBase["5d"].columnFieldLies = &columns[4];
    boardBase["5e"].rowFieldLies = &rows[5]; boardBase["5e"].columnFieldLies = &columns[5];
    boardBase["6b"].rowFieldLies = &rows[6]; boardBase["6b"].columnFieldLies = &columns[1];
    boardBase["6d"].rowFieldLies = &rows[6]; boardBase["6d"].columnFieldLies = &columns[4];
    boardBase["6f"].rowFieldLies = &rows[6]; boardBase["6f"].columnFieldLies = &columns[6];
    boardBase["7a"].rowFieldLies = &rows[7]; boardBase["7a"].columnFieldLies = &columns[0];
    boardBase["7d"].rowFieldLies = &rows[7]; boardBase["7d"].columnFieldLies = &columns[4];
    boardBase["7g"].rowFieldLies = &rows[7]; boardBase["7g"].columnFieldLies = &columns[7];
}

PlayerColor GameBoard::getColorOnField(const std::string& position) const
{
    return boardBase.at(position).colorOnField;
}

void GameBoard::setColorOnField(const std::string& position, const PlayerColor color)
{
    if(color == PlayerColor::None)  // taking oponents checker cause of mill
        lastMove.fieldOponentsCheckerTaken = position;
    else
        lastMove = {"", position, color, ""};
    boardBase[position].colorOnField = color;
    boardBase[position].position = position;
}

void GameBoard::moveChecker(const std::string &checkerOldPos, const std::string &checkerNewPos)
{
    boardBase[checkerNewPos].colorOnField = boardBase[checkerOldPos].colorOnField;
    boardBase[checkerOldPos].colorOnField = PlayerColor::None;
    lastMove = {checkerOldPos, checkerNewPos, boardBase[checkerNewPos].colorOnField, ""};
}

bool GameBoard::operator==(const GameBoard& other) const
{
    return boardBase == other.boardBase;
}

std::vector<std::string> GameBoard::getFreeFields() const
{
    return getCheckersWithColor(PlayerColor::None);
}

bool GameBoard::lastMoveFormedMill() const
{
    auto& field = boardBase.at(lastMove.toField);
    return field.rowFieldLies->isMill() || field.columnFieldLies->isMill();
}

std::vector<std::string> GameBoard::getCheckersWithColor(const PlayerColor color) const
{
    std::vector<std::string> checkersWithColor;
    for(const auto& pair : boardBase)
    {
        if(pair.second.colorOnField == color)
            checkersWithColor.push_back(pair.first);
    }
    return checkersWithColor;
}

bool GameBoard::isCheckerInMill(const std::string& field) const
{
    return boardBase.at(field).rowFieldLies->isMill() || boardBase.at(field).columnFieldLies->isMill();
}

std::vector<std::string> GameBoard::getFreeNeighbours(const std::string &field) const
{
    std::vector<std::string> freeNeighbours;
    const Field* fieldPtr = &boardBase.at(field);
    const auto& fieldsInRow = fieldPtr->rowFieldLies->fieldsInRow;
    for(const auto& fieldInRow : fieldsInRow)
    {
        if(fieldInRow == fieldPtr)
            continue;
        if(fieldInRow->colorOnField == PlayerColor::None)
        {
            if(areNeighbours(field, fieldInRow->position))
                freeNeighbours.push_back(fieldInRow->position);
        }
    }
    const auto& fieldsInColumn = fieldPtr->columnFieldLies->fieldsInColumn;
    for(const auto& fieldInColumn : fieldsInColumn)
    {
        if(fieldInColumn == fieldPtr)
            continue;
        if(fieldInColumn->colorOnField == PlayerColor::None)
        {
            if(areNeighbours(field, fieldInColumn->position))
                freeNeighbours.push_back(fieldInColumn->position);
        }
    }
    return freeNeighbours;
}

bool GameBoard::areNeighbours(const std::string& field1, const std::string& field2) const
{
    int row1 = std::stoi(field1.substr(0, 1));
    int row2 = std::stoi(field2.substr(0, 1));
    char column1 = field1[1];
    char column2 = field2[1];
    if(row1 == row2)
    {
        if((row1 == 1 && row2 == 1) || (row1 == 7 && row2 == 7))
        {
            return std::abs(column1 - column2) == 3;
        }
        else if((row1 == 2 && row2 == 2) || (row1 == 6 && row2 == 6))
        {
            return std::abs(column1 - column2) == 2;
        }
        else if((row1 == 3 && row2 == 3) || (row1 == 4 && row2 == 4) || (row1 == 5 && row2 == 5))
        {
            return std::abs(column1 - column2) == 1;
        }
        else
            return false;
    }
    else if(column1 == column2)
    {
        if((column1 == 'a' && column2 == 'a') || (column1 == 'g' && column2 == 'g'))
        {
            return std::abs(row1 - row2) == 3;
        }
        else if((column1 == 'b' && column2 == 'b') || (column1 == 'f' && column2 == 'f'))
        {
            return std::abs(row1 - row2) == 2;
        }
        else if((column1 == 'c' && column2 == 'c') || (column1 == 'd' && column2 == 'd') || (column1 == 'e' && column2 == 'e'))
        {
            return std::abs(row1 - row2) == 1;
        }
        else
            return false;
    }
    else
        return false;
}

const Move &GameBoard::getLastMove() const
{
    return lastMove;
}

std::string GameBoard::getStrRepr() const
{
    const std::string spacing = "   ";
    const std::string emptyField = " ";
    std::string str =
        colorToStr(boardBase.at("7a").colorOnField) +
        spacing + emptyField +
        spacing + emptyField +
        spacing + colorToStr(boardBase.at("7d").colorOnField) +
        spacing + emptyField +
        spacing + emptyField +
        spacing + colorToStr(boardBase.at("7g").colorOnField);
    str += "\n\n" + emptyField +
           spacing + colorToStr(boardBase.at("6b").colorOnField) +
           spacing + emptyField +
           spacing + colorToStr(boardBase.at("6d").colorOnField) +
           spacing + emptyField +
           spacing + colorToStr(boardBase.at("6f").colorOnField) +
           spacing + emptyField;
    str += "\n\n" + emptyField +
           spacing + emptyField +
           spacing + colorToStr(boardBase.at("5c").colorOnField) +
           spacing + colorToStr(boardBase.at("5d").colorOnField) +
           spacing + colorToStr(boardBase.at("5e").colorOnField) +
           spacing + emptyField +
           spacing + emptyField;
    str += "\n\n" + colorToStr(boardBase.at("4a").colorOnField) +
           spacing + colorToStr(boardBase.at("4b").colorOnField) +
           spacing + colorToStr(boardBase.at("4c").colorOnField) +
           spacing + emptyField +
           spacing + colorToStr(boardBase.at("4e").colorOnField) +
           spacing + colorToStr(boardBase.at("4f").colorOnField) +
           spacing + colorToStr(boardBase.at("4g").colorOnField);
    str += "\n\n" + emptyField +
           spacing + emptyField +
           spacing + colorToStr(boardBase.at("3c").colorOnField) +
           spacing + colorToStr(boardBase.at("3d").colorOnField) +
           spacing + colorToStr(boardBase.at("3e").colorOnField) +
           spacing + emptyField +
           spacing + emptyField;
    str += "\n\n" + emptyField +
           spacing + colorToStr(boardBase.at("2b").colorOnField) +
           spacing + emptyField +
           spacing + colorToStr(boardBase.at("2d").colorOnField) +
           spacing + emptyField +
           spacing + colorToStr(boardBase.at("2f").colorOnField) +
           spacing + emptyField;
    str += "\n\n" + colorToStr(boardBase.at("1a").colorOnField) +
           spacing + emptyField +
           spacing + emptyField +
           spacing + colorToStr(boardBase.at("1d").colorOnField) +
           spacing + emptyField +
           spacing + emptyField +
           spacing + colorToStr(boardBase.at("1g").colorOnField);
    return str;
}

} // namespace model
