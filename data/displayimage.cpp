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

void DisplayImage::darkerAs(QImage const& baseImage, QList<QPoint> const& noDarkenPoints)
{
    for (int y = 0; y < baseImage.height(); ++y)
    {
        for (int x = 0; x < baseImage.width(); ++x)
        {
            setPixel(QPoint(x, y), QColor(baseImage.pixel(QPoint(x, y))).darker().rgb());
        }
    }
    for (int i = 0; i < noDarkenPoints.size(); ++i)
    {
        setPixel(noDarkenPoints[i], baseImage.pixel(noDarkenPoints[i]));
    }
}
