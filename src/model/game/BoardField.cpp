#include "BoardField.hpp"

namespace model {

bool Row::isMill() const
{
    return fieldsInRow[0]->colorOnField != PlayerColor::None &&
           fieldsInRow[0]->colorOnField == fieldsInRow[1]->colorOnField &&
           fieldsInRow[0]->colorOnField == fieldsInRow[2]->colorOnField;
}

bool Column::isMill() const
{
    return fieldsInColumn[0]->colorOnField != PlayerColor::None &&
           fieldsInColumn[0]->colorOnField == fieldsInColumn[1]->colorOnField &&
            fieldsInColumn[0]->colorOnField == fieldsInColumn[2]->colorOnField;
}

bool Field::operator==(const Field &other) const
{
    return position == other.position && colorOnField == other.colorOnField;
}

} // namespace model
