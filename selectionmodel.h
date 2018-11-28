#ifndef SELECTIONMODEL_H
#define SELECTIONMODEL_H

#include <QAbstractItemModel>

#include <vector>
#include <map>

using Point = std::pair<int, int>; // x, y

class SelectionModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit SelectionModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// Inits the model with proper size.
    Q_INVOKABLE void init(int width, int height);
    Q_INVOKABLE void setChunk(int x, int y, bool selected);


private:
    std::vector<std::vector<int>> _data;
};

#endif // SELECTIONMODEL_H
