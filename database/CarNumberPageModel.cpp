#include "CarNumberPageModel.h"

CarNumberPageModel::CarNumberPageModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int CarNumberPageModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return data_.size();
}

QVariant CarNumberPageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    CarNumberInfoModel *carNumberInfoModel = data_.at(index.row());
    if (carNumberInfoModel == nullptr) {
        return QVariant();
    }

    switch (role) {
    case CarNumberModel:
        return QVariant::fromValue(carNumberInfoModel);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> CarNumberPageModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[CarNumberModel] = "carNumberModel";

    return roles;
}

void CarNumberPageModel::search(const QString &number)
{
    clear();

    QList<CarNumberInfo *> list = mapper_.getByCarNumber(number, this);

    if (list.isEmpty()) {
        emit searchCompleted(false);
        return;
    }

    int count = list.size() / 10;

    QList<CarNumberInfoModel *> tmpList;

    for (int i = 0; i <= count; i++)
    {
        CarNumberInfoModel *model = new CarNumberInfoModel(this);
        tmpList.append(model);
        model->append(list.mid(i * 10, 10));

    }



    /*int i = 0;
    for (int modelIndex = 0; modelIndex < count; modelIndex++)
    {
        CarNumberInfoModel *model = new CarNumberInfoModel(this);

        for (; i < list.size(); i++)
        {
            if (i / 10 != i)
            {
                break;
            }

            CarNumberInfo *info = list.at(i);
            model->append(info);
        }
    }*/

    beginInsertRows(QModelIndex(), 0, tmpList.size() - 1);
    data_.append(tmpList);
    endInsertRows();

    emit dataChanged(createIndex(0, 0, static_cast<void *>(nullptr)),
                     createIndex(data_.size() - 1, 0, static_cast<void *>(nullptr)));
    emit countChanged();
    emit searchCompleted(true);
}

CarNumberInfoModel *CarNumberPageModel::at(int index)
{
    if (index < 0 || index > data_.size())
        return nullptr;

    return data_.at(index);
}

void CarNumberPageModel::clear()
{
    if (data_.isEmpty())
        return;

    beginRemoveRows(QModelIndex(), 0, data_.size());
    data_.clear();
    endRemoveRows();

    QModelIndex index = createIndex(0, 0, static_cast<void *>(nullptr));
    emit dataChanged(index, index);
    emit countChanged();
}
