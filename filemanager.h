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

public:
    explicit FileManager(QObject *parent = nullptr);

    void setModel(std::shared_ptr<SelectionModel>model);

    Q_INVOKABLE void openDir(const QString& dir);
    Q_INVOKABLE void openFile(const QString& file);

    Q_INVOKABLE void loadNextImage();
    Q_INVOKABLE void loadPrevImage();

    Q_INVOKABLE void saveSelectionFile();


    QString imagePath() const;

signals:

    void imagePathChanged(QString imagePath);

public slots:

    void setImagePath(QString imagePath);

private:
    std::shared_ptr<SelectionModel> _model;
    QString m_imagePath;
};

#endif // FILEMANAGER_H
