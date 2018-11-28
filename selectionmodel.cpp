#include "selectionmodel.h"
#include <QDebug>

SelectionModel::SelectionModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant SelectionModel::headerData(int, Qt::Orientation, int) const
{
    return QVariant();
}

QModelIndex SelectionModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return createIndex(row, column);;
}

QModelIndex SelectionModel::parent(const QModelIndex &) const
{
    return createIndex(0,0);
}

int SelectionModel::rowCount(const QModelIndex &) const
{
    return _data.size();
}

int SelectionModel::columnCount(const QModelIndex &) const
{
    return _data.at(0).size();
}

QVariant SelectionModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);

    if (!index.isValid()
            || index.row() > rowCount()
            || index.column() > columnCount())
    {
        return QVariant();
    }

    return QVariant::fromValue(_data.at(index.row()).at(index.column()));
}

void SelectionModel::init(int width, int height) // READ FILE HERE
{
    beginResetModel();
    _data.clear();
    for (auto y(0); y < height; ++y) {
        _data.push_back(std::vector<int>(width));
    }
    emit dataChanged(createIndex(0,0), createIndex(columnCount(), rowCount()));
    setWidth(columnCount());
    setHeight(rowCount());
    endResetModel();
}

void SelectionModel::init(PointMatrix &&data)
{
    beginResetModel();
    _data = data;
    emit dataChanged(createIndex(0,0), createIndex(columnCount(), rowCount()));
    setWidth(columnCount());
    setHeight(rowCount());
    endResetModel();
}

void SelectionModel::setChunk(int x, int y, bool selected)
{
    if ((x >= 0 && x < columnCount())
        && (y >= 0 && y < rowCount())) {
        _data[y][x] = selected ? 1 : 0;
        emit dataChanged(this->index(x,y), this->index(x,y));
    }
}

int SelectionModel::width() const
{
    return m_width;
}

int SelectionModel::height() const
{
    return m_height;
}

void SelectionModel::setWidth(int width)
{
    m_width = width;
    emit widthChanged(m_width);
}

void SelectionModel::setHeight(int height)
{
    m_height = height;
    emit heightChanged(m_height);
}
