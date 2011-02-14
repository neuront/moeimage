#ifndef __MOEIMAGE_DATA_CORE_IMAGE_H__
#define __MOEIMAGE_DATA_CORE_IMAGE_H__

#include <QImage>
#include <QList>
#include <QPoint>
#include "matrix3.h"

namespace data {

    struct ImageBase
        : public QImage
    {
        void apply(QList<QPoint> const& points, Matrix3 const& transformer);

        ImageBase& operator=(QImage const& rhs);
    };

}

#endif /* __MOEIMAGE_DATA_CORE_IMAGE_H__ */
