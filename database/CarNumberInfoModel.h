#ifndef CARNUMBERINFOMODEL_H
#define CARNUMBERINFOMODEL_H

#include <QAbstractListModel>

class CarNumberInfo;

class CarNumberInfoModel : public QAbstractListModel
{
	Q_OBJECT

public:
	explicit CarNumberInfoModel(QObject *parent = nullptr);

	enum Roles {
		IdRole = Qt::UserRole + 1,
		CarNumberRole,
		OwnerNameRole,
		OwnerSurnameRole,
		OwnerPatronymicRole,
		ApartmentNumberRole,
		ParkingPlaceRole,
		PhoneNumberRole,
		DescriptionRole
	};

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
	QList<CarNumberInfo *> data_;
};

#endif // CARNUMBERINFOMODEL_H
