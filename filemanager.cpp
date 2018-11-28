#include "filemanager.h"

#include <QImageReader>
#include <QDebug>

FileManager::FileManager(QObject *parent) : QObject(parent)
{

}

void FileManager::setModel(std::shared_ptr<SelectionModel> model)
{
    _model = model;
}

void FileManager::openFile(const QString &file)
{
    // TODO: temporary dummy.
    setImagePath(file);

    QImageReader reader(file);
    QSize sizeOfImage = reader.size();
    int height = sizeOfImage.height();
    int width = sizeOfImage.width();

    qDebug() << "Loaded an image " << file << " with size " << width << "x" << height;
    // TODO: impl. model initing with a proper size.
}

void FileManager::openDir(const QString &dir)
{

}

void FileManager::loadNextImage()
{

}

void FileManager::loadPrevImage()
{

}

void FileManager::saveSelectionFile()
{

}

QString FileManager::imagePath() const
{
    return m_imagePath;
}

void FileManager::setImagePath(QString imagePath)
{
    if (m_imagePath == imagePath)
        return;

    m_imagePath = imagePath;
    emit imagePathChanged(m_imagePath);
}
