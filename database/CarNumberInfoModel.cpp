#include "CarNumberInfoModel.h"

#include "CarNumberInfo.h"

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

	// FIXME: Implement me!
	return QVariant();
}
