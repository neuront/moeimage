#include <QDir>
#include <QFileDialog>
#include "imagesave.h"

using namespace ui;

ImageSaveTrigger::ImageSaveTrigger(QObject* parent)
    : QObject(parent)
{}

bool ImageSaveTrigger::selectFile(QWidget* parent, QString defaultName)
{
    fileName = QFileDialog::getSaveFileName(parent, tr("Select File to Save"), defaultName);
    return !fileName.isNull();
}

QString ImageSaveTrigger::getFileName() const
{
    return fileName;
}
