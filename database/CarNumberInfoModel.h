#ifndef CARNUMBERINFOMODEL_H
#define CARNUMBERINFOMODEL_H

#include <QAbstractListModel>

#include "CarNumberInfoMapper.h"

class CarNumberInfo;

class CarNumberInfoModel : public QAbstractListModel
{
	Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

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

    QHash<int, QByteArray> roleNames() const override;

	Q_INVOKABLE CarNumberInfo *at(int index);

    //Q_INVOKABLE void search(const QString &number);

    void clear();

    void append(CarNumberInfo *info);
    void append(const QList<CarNumberInfo *> &data);

signals:
    void countChanged();
    //void searchCompleted(bool isSearch);

private:
	QList<CarNumberInfo *> data_;
    CarNumberInfoMapper mapper_;
};

#endif // CARNUMBERINFOMODEL_H
