#include <QDir>
#include <QFileDialog>
#include "imageopen.h"

using namespace ui;

ImageOpenTrigger::ImageOpenTrigger(QObject* parent)
    : QObject(parent)
    , lastPath(QDir::currentPath())
{}

bool ImageOpenTrigger::openFile(QWidget* parent)
{
    fileName = QFileDialog::getOpenFileName(parent, tr("Open Image"), lastPath, tr("PNG Image (*.png);;"
                                                                                   "JPEG Image (*.jpg *.jpeg);;"
                                                                                   "Bitmap (*.bmp);;"
                                                                                   "All files (*.*)"));
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
