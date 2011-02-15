#ifndef __MOEIMAGE_UI_CANVAS_H__
#define __MOEIMAGE_UI_CANVAS_H__

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QPaintEvent>
#include <QMouseEvent>
#include <data/coreimage.h>
#include <data/displayimage.h>

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
        data::DisplayImage displayImage;

        int tolerance;

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
