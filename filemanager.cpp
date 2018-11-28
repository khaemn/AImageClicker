#include "filemanager.h"

#include <QImageReader>
#include <QDebug>
#include <QUrl>
#include <QDir>

static const QString DEFAULT_EXTENSION = ".txt";
static const QStringList EXTENSION_FILTERS = { "*.png", "*.jpg", "*.jpeg" };

FileManager::FileManager(QObject *parent) : QObject(parent)
{
    // file:///C:/Users/Vladimir/Pictures/screen1.png
    // openDir("file:///C:/Users/Vladimir/Pictures");
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
    const QUrl url(dir);
    QString dirPath = url.toLocalFile();
    QDir imageFolder(dirPath);

    m_availableImages.clear();
    m_currentImageFileIndex = -1;
    auto availableFiles = imageFolder.entryList(EXTENSION_FILTERS);

    if (availableFiles.empty())
    {
        // TODO: log warning?
        return;
    }

    for (const auto file : availableFiles)
    {
        m_availableImages.append(QUrl::fromLocalFile(imageFolder.path() + "/" + file).toString());
    }

    m_currentImageFileIndex = 0;
    openFile(m_availableImages.at(m_currentImageFileIndex));
}

void FileManager::loadNextImage()
{
    if (++m_currentImageFileIndex >= m_availableImages.size())
    {
        m_currentImageFileIndex = m_availableImages.size() - 1;
    }
    saveSelectionFile();
    openFile(m_availableImages.at(m_currentImageFileIndex));
}

void FileManager::loadPrevImage()
{
    if (--m_currentImageFileIndex < 0)
    {
        m_currentImageFileIndex = 0;
    }
    saveSelectionFile();
    openFile(m_availableImages.at(m_currentImageFileIndex));
}

void FileManager::saveSelectionFile()
{
    QUrl url(m_imagePath);
    QFileInfo pathToImage(url.toLocalFile());

    // Extracting the file name only
    const auto imageFilename = pathToImage.fileName();
    auto withoutExtension = imageFilename.mid(0, imageFilename.indexOf('.'));
    const auto selectionFilename = withoutExtension.append(DEFAULT_EXTENSION);
    auto fullpath = pathToImage.absoluteDir().path().append("/" + selectionFilename);

    writeModelToFile(fullpath);
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

bool FileManager::writeModelToFile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }
    file.flush();

    static const QString LINE_FORMAT("%1,%2,%3\n");
    file.seek(0);

    const auto height = _model->rowCount();
    const auto width = _model->columnCount();

    for (auto y(0); y < height; ++y) {
        for (auto x(0); x < width; ++x) {
            int value = _model->data(_model->index(y, x)).toInt();
            QString line = LINE_FORMAT.arg(x).arg(y).arg(value);
            file.write(line.toLatin1());
        }
    }

    file.close();
}
