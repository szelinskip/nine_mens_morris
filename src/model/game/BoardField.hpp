#pragma once

#include <array>
#include <array>
#include "player/PlayerColor.hpp"

namespace model {

struct Row;
struct Column;
struct Field;

struct Row
{
    std::array<Field*, 3> fieldsInRow;
    bool isMill() const;
};

struct Column
{
    std::array<Field*, 3> fieldsInColumn;
    bool isMill() const;
};

struct Field
{
    std::string position;
    PlayerColor colorOnField;
    Row* rowFieldLies;
    Column* columnFieldLies;

    bool operator==(const Field& other) const;
};

} // namespace model
