#ifndef __MOEIMAGE_UI_IMAGESAVE_H__
#define __MOEIMAGE_UI_IMAGESAVE_H__

#include <QObject>
#include <QWidget>
#include <QString>

namespace ui {

    struct ImageSaveTrigger
        : public QObject
    {
        Q_OBJECT
    public:
        explicit ImageSaveTrigger(QObject* parent);

        bool saveFile(QWidget* parent, QString defaultName);
        QString getFileName() const;
    private:
        QString fileName;
    };

}

#endif /* __MOEIMAGE_UI_IMAGESAVE_H__ */
