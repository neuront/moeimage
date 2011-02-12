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
    , swap_rb(new QPushButton(tr("Swap R&&B"), this))
    , swap_gb(new QPushButton(tr("Swap G&&B"), this))
    , swap_rg(new QPushButton(tr("Swap R&&G"), this))
    , selectionReseter(new QPushButton(tr("&Reset Selection"), this))
    , modifySaver(new QPushButton(tr("Save &Modify"), this))
{
    MainLayoutWrapper(this)
        .Begin<VertLayout>()
            .Begin<HoriLayout>()
                .Begin<VertLayout>()
                    (openImage)
                    (saveImage)
                .End()
                .Begin<VertLayout>()
                    (swap_rb)
                    (swap_gb)
                    (swap_rg)
                .End()
                .Begin<VertLayout>()
                    (selectionReseter)
                    (modifySaver)
                .End()
            .End()
            (canvas)
        .End()
    .End();

    connect(openImage, SIGNAL(clicked()), this, SLOT(tryOpenImage()));
    connect(saveImage, SIGNAL(clicked()), this, SLOT(trySaveImage()));

    connect(swap_rb, SIGNAL(clicked()), canvas, SLOT(SwapRB()));
    connect(swap_gb, SIGNAL(clicked()), canvas, SLOT(SwapGB()));
    connect(swap_rg, SIGNAL(clicked()), canvas, SLOT(SwapRG()));

    connect(selectionReseter, SIGNAL(clicked()), canvas, SLOT(resetDisplay()));
    connect(modifySaver, SIGNAL(clicked()), canvas, SLOT(saveModify()));

    connect(canvas, SIGNAL(Painted()), this, SLOT(repaint()));
}

void MainWindow::tryOpenImage()
{
    if (imageOpener->openFile(this))
    {
        canvas->setImage(imageOpener->getFileName());
    }
}

void MainWindow::trySaveImage()
{
    if (imageSaver->saveFile(this, imageOpener->getFileName()))
    {
        canvas->saveImage(imageSaver->getFileName());
    }
}
