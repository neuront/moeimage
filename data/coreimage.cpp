#include <QPair>
#include <algorithm>
#include "coreimage.h"

using namespace data;

CoreImage::CoreImage()
    : selectionFlags(NULL)
{
    resetFlags();
}

CoreImage::~CoreImage()
{
    delete selectionFlags;
}

CoreImage& CoreImage::operator=(QImage const& rhs)
{
    ImageBase::operator=(rhs);
    resetFlags();
    return *this;
}

void CoreImage::fromPoint(QPoint const& source, int tolerance)
{
    QList<QPair<QPoint, QPoint> > searchQueue;
    searchQueue.push_back(qMakePair(source, source));
    for (int i = 0; i < searchQueue.size(); ++i)
    {
        QPoint p = searchQueue[i].first;
        if (p.x() < 0 || p.y() < 0 || p.x() >= width() || p.y() >= height())
        {
            continue;
        }
        if (selectionFlags[pointToIndex(p)])
        {
            continue;
        }
        if (!(selectionFlags[pointToIndex(p)] = maskAsSelected(p, searchQueue[i].second, tolerance)))
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

QList<QPoint> const& CoreImage::getSelectedPoints() const
{
    return selectedPoints;
}

void CoreImage::clearSelection()
{
    for (int i = 0; i < size().width() * size().height() + 1; ++i)
    {
        selectionFlags[i] = false;
    }
    selectedPoints.clear();
}

void CoreImage::resetFlags()
{
    delete selectionFlags;
    int size = width() * height() + 1;
    selectionFlags = new bool[size];
    clearSelection();
}

bool CoreImage::maskAsSelected(QPoint p, QPoint reference, int tolerance) const
{
    if (p.x() < 0 || p.y() < 0 || p.x() >= width() || p.y() >= height())
    {
        return true;
    }
    QRgb rgb = pixel(p);
    QRgb rgb0 = pixel(reference);
    return ((qRed(rgb) - qRed(rgb0)) * (qRed(rgb) - qRed(rgb0))
          + (qBlue(rgb) - qBlue(rgb0)) * (qBlue(rgb) - qBlue(rgb0))
          + (qGreen(rgb) - qGreen(rgb0)) * (qGreen(rgb) - qGreen(rgb0))
           ) < tolerance;
}

int CoreImage::pointToIndex(QPoint p) const
{
    return p.x() * height() + p.y();
}
