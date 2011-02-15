#include "displayimage.h"
#include "matrix3.h"

using namespace data;

DisplayImage& DisplayImage::operator=(QImage const& rhs)
{
    QImage::operator=(rhs);
    return *this;
}

void DisplayImage::swapRB(QList<QPoint> const& applyPoints)
{
    apply(applyPoints, rbSwapMatrix());
}

void DisplayImage::swapGB(QList<QPoint> const& applyPoints)
{
    apply(applyPoints, gbSwapMatrix());
}

void DisplayImage::swapRG(QList<QPoint> const& applyPoints)
{
    apply(applyPoints, rgSwapMatrix());
}
