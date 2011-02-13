#ifndef __MOEIMAGE_UI_CANVAS_H__
#define __MOEIMAGE_UI_CANVAS_H__

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QPaintEvent>
#include <QMouseEvent>

namespace ui {

    class Canvas
        : public QWidget
    {
        Q_OBJECT
    public:
        explicit Canvas(QWidget* parent);
        ~Canvas();

        QSize sizeHint() const;

        void setImage(QString fileName);
        void saveImage(QString fileName) const;

        void setColorTolerance(int t);
    protected:
        QImage coreImage;
        QImage displayImage;

        bool* selectedPointFlags;
        QList<QPoint> selectedPoints;

        int tolerance;
        QPoint lastSelectPoint;
        bool selected;

        void paintEvent(QPaintEvent*);

        template <typename _PixelMaker>
        void swapColor(_PixelMaker pm);

        void selectPoint(QPoint point);
        void resetFlags(QSize size);
        void refreshDisplayImage();
        bool maskAsSelected(QPoint p, QPoint reference) const;
        void findFrom();
        int pointToIndex(QPoint p);

        void mousePressEvent(QMouseEvent* event);
    signals:
        void painted();
    public slots:
        void swapRB();
        void swapGB();
        void swapRG();
        void resetDisplay();
        void saveModify();
    };

}

#endif /* __MOEIMAGE_UI_CANVAS_H__ */
