#ifndef __MOEIMAGE_UI_CANVAS_H__
#define __MOEIMAGE_UI_CANVAS_H__

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QPaintEvent>
#include <QMouseEvent>
#include <data/imagebase.h>
#include <data/coreimage.h>

namespace ui {

    class Canvas
        : public QWidget
    {
        Q_OBJECT
    public:
        explicit Canvas(QWidget* parent);

        QSize sizeHint() const;

        void setImage(QString fileName);
        void saveImage(QString fileName) const;

        void setColorTolerance(int t);
    protected:
        data::CoreImage coreImage;
        data::ImageBase displayImage;

        int tolerance;
        bool selected;

        template <typename _PixelMaker>
        void swapColor(_PixelMaker pm);

        void selectPoint(QPoint point);
    signals:
        void painted();
    public slots:
        void swapRB();
        void swapGB();
        void swapRG();
        void resetDisplay();
        void saveModify();
    protected:
        void paintEvent(QPaintEvent*);
        void mousePressEvent(QMouseEvent* event);
    };

}

#endif /* __MOEIMAGE_UI_CANVAS_H__ */
