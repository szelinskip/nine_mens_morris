#include "StyleProvider.hpp"

QString StyleProvider::getButtonStyle(CheckerType checker) const
{
    switch(checker)
    {
        case CheckerType::None:
            return "";
        case CheckerType::White:
            return "border-image: url(:/images/images/white_piece.png) 0 0 0 0 stretch stretch;";
        case CheckerType::Black:
            return "border-image: url(:/images/images/black_piece.png) 0 0 0 0 stretch stretch;";
        default:
            return "";
    }
}

QString StyleProvider::buildStyleSheetCheckerWithBackground(CheckerType checker, const std::string& rgbColor) const
{
    std::string styleSheet;
    switch(checker)
    {
        case CheckerType::None:
            styleSheet = "";
            break;
        case CheckerType::White:
            styleSheet += "border-image: url(:/images/images/white_piece.png) 0 0 0 0 stretch stretch;";
            break;
        case CheckerType::Black:
            styleSheet += "border-image: url(:/images/images/black_piece.png) 0 0 0 0 stretch stretch;";
            break;
    }
    if(!rgbColor.empty())
        styleSheet += "background-color: " + rgbColor;
    return QString::fromStdString(styleSheet);
}
