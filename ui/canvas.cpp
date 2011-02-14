#include <QPainter>
#include <algorithm>
#include <data/matrix3.h>
#include "canvas.h"

using namespace ui;

Canvas::Canvas(QWidget* parent)
    : QWidget(parent)
    , selectedPointFlags(NULL)
    , tolerance(256)
    , selected(false)
{
    resetFlags(QSize(0, 0));
}

Canvas::~Canvas()
{
    delete[] selectedPointFlags;
}

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
    displayImage = coreImage.copy(0, 0, coreImage.width(), coreImage.height());
    resetFlags(coreImage.size());
    emit painted();
}

void Canvas::saveImage(QString fileName) const
{
    coreImage.save(fileName);
}

void Canvas::resetDisplay()
{
    displayImage = coreImage.copy(0, 0, coreImage.width(), coreImage.height());
    for (int i = 0; i < (coreImage.size().width() + 2) * (coreImage.size().height() + 2); ++i)
    {
        selectedPointFlags[i] = false;
    }
    selected = false;
    selectedPoints.clear();
    emit painted();
}

void Canvas::saveModify()
{
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
    lastSelectPoint = point;
    selected = true;
    refreshDisplayImage();
}

void Canvas::resetFlags(QSize size)
{
    delete[] selectedPointFlags;
    selectedPointFlags = new bool[(size.width() + 2) * (size.height() + 2)];
    for (int i = 0; i < (size.width() + 2) * (size.height() + 2); ++i)
    {
        selectedPointFlags[i] = false;
    }
}

void Canvas::refreshDisplayImage()
{
    if (!selected)
    {
        return;
    }
    displayImage = coreImage.copy(0, 0, coreImage.width(), coreImage.height());
    findFrom();
    for (int y = 0; y < coreImage.height(); ++y)
    {
        for (int x = 0; x < coreImage.width(); ++x)
        {
            QPoint point(x, y);
            if (!selectedPointFlags[pointToIndex(point)])
            {
                displayImage.setPixel(point, QColor(coreImage.pixel(point)).darker().rgb());
            }
        }
    }
    emit painted();
}

void Canvas::findFrom()
{
    QList<QPair<QPoint, QPoint> > searchQueue;
    searchQueue.push_back(qMakePair(lastSelectPoint, lastSelectPoint));
    for (int i = 0; i < searchQueue.size(); ++i)
    {
        QPoint p = searchQueue[i].first;
        if (p.x() < 0 || p.y() < 0 || p.x() >= coreImage.width() || p.y() >= coreImage.height())
        {
            continue;
        }
        if (selectedPointFlags[pointToIndex(p)])
        {
            continue;
        }
        if (!(selectedPointFlags[pointToIndex(p)] = maskAsSelected(p, searchQueue[i].second)))
        {
            continue;
        }
        selectedPoints.push_back(p);
        searchQueue.push_back(qMakePair(p + QPoint(-1, 0), p));
        searchQueue.push_back(qMakePair(p + QPoint(1, 0), p));
        searchQueue.push_back(qMakePair(p + QPoint(0, 1), p));
        searchQueue.push_back(qMakePair(p + QPoint(0, -1), p));
    }
}

bool Canvas::maskAsSelected(QPoint p, QPoint reference) const
{
    if (p.x() < 0 || p.y() < 0 || p.x() >= coreImage.width() || p.y() >= coreImage.height())
    {
        return true;
    }
    QRgb rgb = coreImage.pixel(p);
    QRgb rgb0 = coreImage.pixel(reference);
    return ((qRed(rgb) - qRed(rgb0)) * (qRed(rgb) - qRed(rgb0))
          + (qBlue(rgb) - qBlue(rgb0)) * (qBlue(rgb) - qBlue(rgb0))
          + (qGreen(rgb) - qGreen(rgb0)) * (qGreen(rgb) - qGreen(rgb0))
           ) < tolerance;
}

int Canvas::pointToIndex(QPoint p)
{
    return (p.x() + 1) * coreImage.height() + (p.y() + 1);
}

void Canvas::mousePressEvent(QMouseEvent* event)
{
    selectPoint(QPoint(event->x(), event->y()));
}

void Canvas::swapRB()
{
    displayImage.apply(selectedPoints, data::rbSwapMatrix());
    emit painted();
}

void Canvas::swapGB()
{
    displayImage.apply(selectedPoints, data::gbSwapMatrix());
    emit painted();
}

void Canvas::swapRG()
{
    displayImage.apply(selectedPoints, data::rgSwapMatrix());
    emit painted();
}
