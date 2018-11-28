#include "filemanager.h"

#include <QImageReader>
#include <QDebug>
#include <QUrl>
#include <QDir>

static const QString DEFAULT_EXTENSION = ".txt";

FileManager::FileManager(QObject *parent) : QObject(parent)
{
}

void FileManager::setModel(std::shared_ptr<SelectionModel> model)
{
    _model = model;
}

void FileManager::openFile(const QString &file)
{
    if (file.isEmpty())
    {
        return;
    }

    const QUrl url(file);

    auto path = url.path();
    while (!path.isEmpty() && path.at(0) == '/') {
        // Erasing extra "/" character.
        // TODO: check on linux!
        path.remove(0,1);
    }
    QImageReader reader(path);
    const QSize sizeOfImage = reader.size();
    const int height = sizeOfImage.height();
    const int width = sizeOfImage.width();

    qDebug() << "Loaded an image " << path << " with size " << width << "x" << height;

    const auto gridWidth = roundf(static_cast<float>(width) / m_pixelGridSize);
    const auto gridHeight = roundf(static_cast<float>(height) / m_pixelGridSize);
    qDebug() << "Initing model grid with size " << m_pixelGridSize << ":" << gridWidth << "x" << gridHeight;
    _model->init(gridWidth, gridHeight);

    setImagePath(file);
}

void FileManager::openDir(const QString &dir)
{

}

void FileManager::loadNextImage()
{
    saveSelectionFile();
    // TODO: impl. loading
}

void FileManager::loadPrevImage()
{
    saveSelectionFile();
    // TODO: impl. loading
}

void FileManager::saveSelectionFile()
{
    QUrl path(m_imagePath);
    QFileInfo pathToImage(path.toLocalFile());

    // Extracting the file name only
    const auto imageFilename = pathToImage.fileName();
    auto withoutExtension = imageFilename.mid(0, imageFilename.indexOf('.'));
    const auto selectionFilename = withoutExtension.append(DEFAULT_EXTENSION);
    auto fullpath = pathToImage.absoluteDir().path().append("/" + selectionFilename);

    QFile txtFile(fullpath);
    if (!txtFile.open(QIODevice::WriteOnly))
    {
        return;
    }

    // TODO: impl filewriting

    txtFile.close();
}

QString FileManager::imagePath() const
{
    return m_imagePath;
}

int FileManager::pixelGridSize() const
{
    return m_pixelGridSize;
}

void FileManager::setImagePath(QString imagePath)
{
    if (m_imagePath == imagePath)
        return;

    m_imagePath = imagePath;
    emit imagePathChanged(m_imagePath);
}

void FileManager::setPixelGridSize(int pixelGridSize)
{
    if (m_pixelGridSize == pixelGridSize)
        return;

    m_pixelGridSize = pixelGridSize;
    emit pixelGridSizeChanged(m_pixelGridSize);
}
