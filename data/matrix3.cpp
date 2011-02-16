#include "matrix3.h"
#include "constants.h"

using namespace data;

QRgb Matrix3::transform(QRgb original) const
{
    int red = qRed(original);
    int green = qGreen(original);
    int blue = qBlue(original);
    return QColor::fromRgb((_00 * red + _10 * green + _20 * blue) / RGB_MODULUS
                         , (_01 * red + _11 * green + _21 * blue) / RGB_MODULUS
                         , (_02 * red + _12 * green + _22 * blue) / RGB_MODULUS
                          ).rgb();
}

static Matrix3 const RG_SWAPPER(0, RGB_MODULUS, 0
                              , RGB_MODULUS, 0, 0
                              , 0, 0, RGB_MODULUS);

static Matrix3 const GB_SWAPPER(RGB_MODULUS, 0, 0
                              , 0, 0, RGB_MODULUS
                              , 0, RGB_MODULUS, 0);

static Matrix3 const RB_SWAPPER(0, 0, RGB_MODULUS
                              , 0, RGB_MODULUS, 0
                              , RGB_MODULUS, 0, 0);

Matrix3 const& data::rgSwapMatrix()
{
    return RG_SWAPPER;
}

Matrix3 const& data::gbSwapMatrix()
{
    return GB_SWAPPER;
}

Matrix3 const& data::rbSwapMatrix()
{
    return RB_SWAPPER;
}
