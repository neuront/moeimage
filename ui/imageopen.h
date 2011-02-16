#ifndef __MOEIMAGE_UI_IMAGEOPEN_H__
#define __MOEIMAGE_UI_IMAGEOPEN_H__

#include <QObject>
#include <QWidget>

namespace ui {

    struct ImageOpenTrigger
        : public QObject
    {
        Q_OBJECT
    public:
        explicit ImageOpenTrigger(QObject* parent);

        bool selectFile(QWidget* parent);
        QString getFileName() const;
    private:
        QString fileName;
        QString lastPath;
    };

}

#endif /* __MOEIMAGE_UI_IMAGEOPEN_H__ */
