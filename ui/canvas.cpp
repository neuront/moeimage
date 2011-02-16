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
    coreImage.saveImageOnSelected(displayImage);
    resetDisplay();
}

void Canvas::setColorTolerance(int t)
{
    tolerance = t;
}

void Canvas::selectPoint(QPoint point)
{
    coreImage.fromPoint(point, tolerance);
    displayImage.darkerAs(coreImage, coreImage.getSelectedPoints());
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
