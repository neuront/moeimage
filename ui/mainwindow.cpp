#include <QString>
#include "mainwindow.h"
#include "layouts.h"

using namespace ui;

MainWindow::MainWindow()
    : QWidget(NULL)
    , imageOpener(new ImageOpenTrigger(this))
    , imageSaver(new ImageSaveTrigger(this))
    , openImage(new QPushButton(tr("&Open Image"), this))
    , saveImage(new QPushButton(tr("&Save Image"), this))
    , canvas(new Canvas(this))
    , rbSwapper(new QPushButton(tr("Swap R&&B"), this))
    , gbSwapper(new QPushButton(tr("Swap G&&B"), this))
    , rgSwapper(new QPushButton(tr("Swap R&&G"), this))
    , selectionReseter(new QPushButton(tr("&Reset Selection"), this))
    , modifySaver(new QPushButton(tr("Save &Modify"), this))
    , toleranceHint(new QLabel(tr("Color Tolerance"), this))
    , toleranceEditor(new QLineEdit("256", this))
{
    MainLayoutWrapper(this)
        .begin<VertLayout>()
            .begin<HoriLayout>()
                .begin<VertLayout>()
                    (openImage)
                    (saveImage)
                .end()
                .begin<VertLayout>()
                    (rbSwapper)
                    (gbSwapper)
                    (rgSwapper)
                .end()
                .begin<VertLayout>()
                    (selectionReseter)
                    .begin<HoriLayout>()
                        (toleranceHint)
                        (toleranceEditor)
                    .end()
                    (modifySaver)
                .end()
            .end()
            (canvas)
        .end()
    .end();

    connect(openImage, SIGNAL(clicked()), this, SLOT(tryOpenImage()));
    connect(saveImage, SIGNAL(clicked()), this, SLOT(trySaveImage()));

    connect(rbSwapper, SIGNAL(clicked()), canvas, SLOT(swapRB()));
    connect(gbSwapper, SIGNAL(clicked()), canvas, SLOT(swapGB()));
    connect(rgSwapper, SIGNAL(clicked()), canvas, SLOT(swapRG()));

    connect(selectionReseter, SIGNAL(clicked()), canvas, SLOT(resetDisplay()));
    connect(modifySaver, SIGNAL(clicked()), canvas, SLOT(saveModify()));

    connect(toleranceEditor, SIGNAL(textChanged(QString const&)), this, SLOT(toleranceChange(QString const&)));

    connect(canvas, SIGNAL(painted()), this, SLOT(refreshUi()));

    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    setWindowTitle(tr("Moe Image"));
}

void MainWindow::tryOpenImage()
{
    if (imageOpener->selectFile(this))
    {
        canvas->setImage(imageOpener->getFileName());
    }
}

void MainWindow::trySaveImage()
{
    if (imageSaver->selectFile(this, imageOpener->getFileName()))
    {
        canvas->saveImage(imageSaver->getFileName());
    }
}

void MainWindow::toleranceChange(QString const& tolerance)
{
    bool ok;
    int newValue = tolerance.toInt(&ok);
    if (ok && newValue >= 0)
    {
        canvas->setColorTolerance(newValue);
    }
}

void MainWindow::refreshUi()
{
    repaint();
}
