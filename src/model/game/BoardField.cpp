#include "BoardField.hpp"

#include <algorithm>
#include <map>

namespace model {

bool Row::isMill() const
{
    return fieldsInRow[0]->colorOnField != PlayerColor::None &&
           fieldsInRow[0]->colorOnField == fieldsInRow[1]->colorOnField &&
            fieldsInRow[0]->colorOnField == fieldsInRow[2]->colorOnField;
}

bool Row::oneLeftToMorris() const
{
    return (fieldsInRow[0]->colorOnField == fieldsInRow[1]->colorOnField &&
            fieldsInRow[2]->colorOnField == PlayerColor::None) ||
           (fieldsInRow[1]->colorOnField == fieldsInRow[2]->colorOnField &&
            fieldsInRow[0]->colorOnField == PlayerColor::None) ||
           (fieldsInRow[0]->colorOnField == fieldsInRow[2]->colorOnField &&
            fieldsInRow[1]->colorOnField == PlayerColor::None);
}

PlayerColor Row::getColorDominatingInRow() const
{
    std::map<PlayerColor, uint32_t> colorsNum{{PlayerColor::None, 0},
                                              {PlayerColor::White, 0},
                                              {PlayerColor::Black, 0}};
    for(const auto& field : fieldsInRow)
    {
        colorsNum[field->colorOnField]++;
    }
    auto maxElem = std::max_element(colorsNum.cbegin(), colorsNum.cend(),
                     [](const auto& lhs, const auto& rhs)
                     {
                         return lhs.second < rhs.second;
                     });
    return (*maxElem).first;
}

bool Column::isMill() const
{
    return fieldsInColumn[0]->colorOnField != PlayerColor::None &&
           fieldsInColumn[0]->colorOnField == fieldsInColumn[1]->colorOnField &&
            fieldsInColumn[0]->colorOnField == fieldsInColumn[2]->colorOnField;
}

bool Column::oneLeftToMorris() const
{
    return (fieldsInColumn[0]->colorOnField == fieldsInColumn[1]->colorOnField &&
            fieldsInColumn[2]->colorOnField == PlayerColor::None) ||
           (fieldsInColumn[1]->colorOnField == fieldsInColumn[2]->colorOnField &&
            fieldsInColumn[0]->colorOnField == PlayerColor::None) ||
           (fieldsInColumn[0]->colorOnField == fieldsInColumn[2]->colorOnField &&
            fieldsInColumn[1]->colorOnField == PlayerColor::None);
}

PlayerColor Column::getColorDominatingInColumn() const
{
    std::map<PlayerColor, uint32_t> colorsNum{{PlayerColor::None, 0},
                                              {PlayerColor::White, 0},
                                              {PlayerColor::Black, 0}};
    for(const auto& field : fieldsInColumn)
    {
        colorsNum[field->colorOnField]++;
    }
    auto maxElem = std::max_element(colorsNum.cbegin(), colorsNum.cend(),
                                    [](const auto& lhs, const auto& rhs)
                                    {
                                        return lhs.second < rhs.second;
                                    });
    return (*maxElem).first;
}

bool Field::operator==(const Field &other) const
{
    return position == other.position && colorOnField == other.colorOnField;
}

} // namespace model
