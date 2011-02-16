#include <QDir>
#include <QFileDialog>
#include "imageopen.h"

using namespace ui;

ImageOpenTrigger::ImageOpenTrigger(QObject* parent)
    : QObject(parent)
    , lastPath(QDir::currentPath())
{}

bool ImageOpenTrigger::selectFile(QWidget* parent)
{
    fileName = QFileDialog::getOpenFileName(parent
                                          , tr("Open Image")
                                          , lastPath
                                          , tr("Any file") + QString(" (*.*);;")
                                          + tr("PNG image") + QString(" (*.png);;")
                                          + tr("JPEG image") + QString(" (*.jpg *.jpeg);;")
                                          + tr("Bitmap") + QString(" (*.bmp)"));
    if (!fileName.isNull())
    {
        lastPath = fileName;
    }
    return !fileName.isNull();
}

QString ImageOpenTrigger::getFileName() const
{
    return fileName;
}
