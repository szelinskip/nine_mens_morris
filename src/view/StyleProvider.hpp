#pragma once

#include "CheckerType.hpp"

#include <QString>

class StyleProvider
{
public:
    QString getButtonStyle(CheckerType checker) const;
};
