#include <QPainter>
#include <algorithm>
#include "canvas.h"

using namespace ui;

Canvas::Canvas(QWidget* parent)
    : QWidget(parent)
    , tolerance(256)
{}

void Canvas::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawImage(0, 0, displayImage);
}

QSize Canvas::sizeHint() const
{
    return coreImage.size();
}

void Canvas::setImage(QString fileName)
{
    coreImage = QImage(fileName);
    displayImage = coreImage;
    emit painted();
}

void Canvas::saveImage(QString fileName) const
{
    coreImage.save(fileName);
}

void Canvas::resetDisplay()
{
    displayImage = coreImage;
    coreImage.clearSelection();
    emit painted();
}

void Canvas::saveModify()
{
    QList<QPoint> const& selectedPoints = coreImage.getSelectedPoints();
    for (int i = 0; i < selectedPoints.size(); ++i)
    {
        coreImage.setPixel(selectedPoints[i], displayImage.pixel(selectedPoints[i]));
    }
    resetDisplay();
}

void Canvas::setColorTolerance(int t)
{
    tolerance = t;
}

void Canvas::selectPoint(QPoint point)
{
    for (int y = 0; y < coreImage.height(); ++y)
    {
        for (int x = 0; x < coreImage.width(); ++x)
        {
            displayImage.setPixel(QPoint(x, y), QColor(coreImage.pixel(QPoint(x, y))).darker().rgb());
        }
    }

    coreImage.fromPoint(point, tolerance);
    QList<QPoint> const& selectedPoints = coreImage.getSelectedPoints();
    for (int i = 0; i < selectedPoints.size(); ++i)
    {
        displayImage.setPixel(selectedPoints[i], QColor(coreImage.pixel(selectedPoints[i])).rgb());
    }

    emit painted();
}

void Canvas::mousePressEvent(QMouseEvent* event)
{
    selectPoint(QPoint(event->x(), event->y()));
}

void Canvas::swapRB()
{
    displayImage.swapRB(coreImage.getSelectedPoints());
    emit painted();
}

void Canvas::swapGB()
{
    displayImage.swapGB(coreImage.getSelectedPoints());
    emit painted();
}

void Canvas::swapRG()
{
    displayImage.swapRG(coreImage.getSelectedPoints());
    emit painted();
}
