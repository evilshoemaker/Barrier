#include "CarNumberInfoModel.h"

#include "CarNumberInfo.h"
#include "CarNumberInfoMapper.h"

CarNumberInfoModel::CarNumberInfoModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int CarNumberInfoModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return data_.size();
}

QVariant CarNumberInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    CarNumberInfo *carNumberInfo = data_.at(index.row());
    if (carNumberInfo == nullptr) {
        return QVariant();
    }

    switch (role) {
    case IdRole:
        return carNumberInfo->id();
    case CarNumberRole:
        return carNumberInfo->carNumber();
    case OwnerNameRole:
        return carNumberInfo->ownerName();
    case OwnerSurnameRole:
        return carNumberInfo->ownerSurname();
    case OwnerPatronymicRole:
        return carNumberInfo->ownerPatronymic();
    case ApartmentNumberRole:
        return carNumberInfo->apartmentNumber();
    case ParkingPlaceRole:
        return carNumberInfo->parkingPlace();
    case PhoneNumberRole:
        return carNumberInfo->phoneNumber();
    case DescriptionRole:
        return carNumberInfo->description();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> CarNumberInfoModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[IdRole] = "id";
    roles[CarNumberRole] = "carNumber";
    roles[OwnerNameRole] = "ownerName";
    roles[OwnerSurnameRole] = "ownerSurname";
    roles[OwnerPatronymicRole] = "ownerPatronymic";
    roles[ApartmentNumberRole] = "apartmentNumber";
    roles[ParkingPlaceRole] = "parkingPlace";
    roles[PhoneNumberRole] = "phoneNumber";
    roles[DescriptionRole] = "description";

	return roles;
}

CarNumberInfo *CarNumberInfoModel::at(int index)
{
	if (index < 0 || index > data_.size())
		return nullptr;

	return data_.at(index);
}

void CarNumberInfoModel::search(const QString &number)
{
    clear();

    QList<CarNumberInfo *> list = mapper_.getByCarNumber(number, this);

    if (list.isEmpty()) {
        emit searchCompleted(false);
        return;
    }

	beginInsertRows(QModelIndex(), 0, list.size() - 1);
    data_.append(list);
    endInsertRows();

	emit dataChanged(createIndex(0, 0, static_cast<void *>(0)),
					 createIndex(data_.size() - 1, 0, static_cast<void *>(0)));
    emit countChanged();
    emit searchCompleted(true);
}

void CarNumberInfoModel::clear()
{
    if (data_.isEmpty())
        return;

    beginRemoveRows(QModelIndex(), 0, data_.size());
    data_.clear();
    endRemoveRows();

	QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
	emit dataChanged(index, index);
    emit countChanged();
}
