#include "selectionmodel.h"
#include <QDebug>

SelectionModel::SelectionModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant SelectionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex SelectionModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return createIndex(row, column);;
}

QModelIndex SelectionModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
    return createIndex(0,0);
}

int SelectionModel::rowCount(const QModelIndex &parent) const
{
    return _data.size();
}

int SelectionModel::columnCount(const QModelIndex &parent) const
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
    _data.clear();
    for (auto y(0); y < height; ++y) {
        _data.push_back(std::vector<int>(width));
    }
    _data[0][1] = 1;
    _data[height-1][width-1] = 1;
    emit dataChanged(createIndex(0,0), createIndex(columnCount(), rowCount()));
}

void SelectionModel::setChunk(int x, int y, bool selected)
{
    if ((x >= 0 && x < columnCount())
        && (y >= 0 && y < rowCount())) {
        _data[y][x] = selected ? 1 : 0;
        emit dataChanged(this->index(x,y), this->index(x,y));
        //emit dataChanged(createIndex(0,0), createIndex(columnCount(), rowCount()));
    }

    qDebug() << "Chunk changed " << x << y << selected;
}
