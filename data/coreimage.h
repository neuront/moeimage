#ifndef __MOEIMAGE_DATA_CORE_IMAGE_H__
#define __MOEIMAGE_DATA_CORE_IMAGE_H__

#include <QString>
#include <QList>
#include <QPoint>
#include "imagebase.h"

namespace data {

    struct CoreImage
        : public ImageBase
    {
        CoreImage();
        ~CoreImage();

        CoreImage& operator=(QImage const& rhs);
    public:
        void fromPoint(QPoint const& source, int tolerance);

        QList<QPoint> const& getSelectedPoints() const;

        void clearSelection();
    private:
        bool* selectionFlags;
        QList<QPoint> selectedPoints;

        void resetFlags();
        bool maskAsSelected(QPoint p, QPoint reference, int tolerance) const;
        int pointToIndex(QPoint p) const;
    };

}

#endif /* __MOEIMAGE_DATA_CORE_IMAGE_H__ */
