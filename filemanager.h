#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <memory>

#include <QObject>
#include <QFile>

#include "selectionmodel.h"


class FileManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString imagePath READ imagePath WRITE setImagePath NOTIFY imagePathChanged)
    Q_PROPERTY(int pixelGridSize READ pixelGridSize WRITE setPixelGridSize NOTIFY pixelGridSizeChanged)

public:
    explicit FileManager(QObject *parent = nullptr);

    void setModel(std::shared_ptr<SelectionModel>model);

    Q_INVOKABLE void openDir(const QString& dir);
    Q_INVOKABLE void openFile(const QString& file);

    Q_INVOKABLE void loadNextImage();
    Q_INVOKABLE void loadPrevImage();

    Q_INVOKABLE void saveSelectionFile();


    QString imagePath() const;
    int pixelGridSize() const;

signals:

    void imagePathChanged(QString imagePath);
    void pixelGridSizeChanged(int pixelGridSize);

public slots:

    void setImagePath(QString imagePath);
    void setPixelGridSize(int pixelGridSize);

private:
    std::shared_ptr<SelectionModel> _model;
    QString m_imagePath;
    int m_pixelGridSize = 100;
};

#endif // FILEMANAGER_H
