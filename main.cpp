#include <QtGui/QApplication>
#include <QTranslator>
#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator t;
    t.load("lang");
    a.installTranslator(&t);

    ui::MainWindow w;
    w.showMaximized();
    return a.exec();
}
