#pragma once

#include "CheckerType.hpp"

#include <QString>
#include <string>

class StyleProvider
{
public:
    QString getButtonStyle(CheckerType checker) const;
    QString buildStyleSheetCheckerWithBackground(CheckerType checker, const std::string& rgbColor) const;
};
