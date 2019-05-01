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
