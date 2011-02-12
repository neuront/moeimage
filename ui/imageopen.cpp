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
    fileName = QFileDialog::getOpenFileName(parent, tr("Open Image"), lastPath);
    return !fileName.isNull();
}

QString ImageOpenTrigger::getFileName() const
{
    return fileName;
}
