#ifndef __MOEIMAGE_UI_MAINWINDOW_H__
#define __MOEIMAGE_UI_MAINWINDOW_H__

#include <QWidget>
#include <QTimer>
#include <QLineEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "canvas.h"
#include "imageopen.h"
#include "imagesave.h"

namespace ui {

    class MainWindow
        : public QWidget
    {
        Q_OBJECT
    public:
        MainWindow();
    private:
        ImageOpenTrigger* imageOpener;
        ImageSaveTrigger* imageSaver;

        QPushButton* openImage;
        QPushButton* saveImage;
        Canvas* canvas;
        QPushButton* swap_rb;
        QPushButton* swap_gb;
        QPushButton* swap_rg;

        QPushButton* selectionReseter;
        QPushButton* modifySaver;
        QLabel* toleranceHint;
        QLineEdit* toleranceEditor;
    private slots:
        void tryOpenImage();
        void trySaveImage();

        void toleranceChange(QString const& tolerance);
    };

}

#endif /* __MOEIMAGE_UI_MAINWINDOW_H__ */
