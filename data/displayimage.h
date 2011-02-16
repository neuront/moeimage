#ifndef __MOEIMAGE_DATA_DISPLAY_IMAGE_H__
#define __MOEIMAGE_DATA_DISPLAY_IMAGE_H__

#include "imagebase.h"

namespace data {

    struct DisplayImage
        : public ImageBase
    {
        DisplayImage& operator=(QImage const& rhs);
    public:
        void swapRB(QList<QPoint> const& applyPoints);
        void swapGB(QList<QPoint> const& applyPoints);
        void swapRG(QList<QPoint> const& applyPoints);
    public:
        void darkerAs(QImage const& baseImage, QList<QPoint> const& noDarkenPoints);
    };

}

#endif /* __MOEIMAGE_DATA_DISPLAY_IMAGE_H__ */
