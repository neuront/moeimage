#include "imagebase.h"

using namespace data;

void ImageBase::apply(QList<QPoint> const& points, Matrix3 const& transformer)
{
    for (int i = 0; i < points.size(); ++i)
    {
        setPixel(points[i], transformer.transform(pixel(points[i])));
    }
}

ImageBase& ImageBase::operator=(QImage const& rhs)
{
    QImage::operator=(rhs);
    return *this;
}
