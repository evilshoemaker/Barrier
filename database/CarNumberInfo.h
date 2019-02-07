#ifndef CARNUMBERINFO_H
#define CARNUMBERINFO_H

#include <QObject>

class CarNumberInfo : public QObject
{
	Q_OBJECT

	Q_PROPERTY(qlonglong id READ id WRITE setId)
	Q_PROPERTY(QString carNumber READ carNumber WRITE setCarNumber NOTIFY carNumberChanged)
	Q_PROPERTY(QString ownerName READ ownerName WRITE setOwnerName NOTIFY ownerNameChanged)
	Q_PROPERTY(QString ownerSurname READ ownerSurname WRITE setOwnerSurname NOTIFY ownerSurnameChanged)
	Q_PROPERTY(QString ownerPatronymic READ ownerPatronymic WRITE setOwnerPatronymic NOTIFY ownerPatronymicChanged)
	Q_PROPERTY(QString apartmentNumber READ apartmentNumber WRITE setApartmentNumber NOTIFY apartmentNumberChanged)
	Q_PROPERTY(QStrign parkingPlace READ parkingPlace WRITE setParkingPlace NOTIFY parkingPlaceChanged)
	Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
	Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
	explicit CarNumberInfo(QObject *parent = nullptr);

	qlonglong id();
	void setId(qlonglong id);

	QString carNumber();
	void setCarNumber(const QString &carNumber);

	QString ownerName();
	void setOwnerName(const QString &ownerName);

	QString ownerSurname();
	void setOwnerSurname(const QString &ownerSurname);

	QString ownerPatronymic();
	void setOwnerPatronymic(const QString &ownerPatronymic);

	QString apartmentNumber();
	void setApartmentNumber(const QString &apartmentNumber);

	QString parkingPlace();
	void setParkingPlace(const QString &parkingPlace);

	QString phoneNumber();
	void setPhoneNumber(const QString &phoneNumber);

	QString description();
	void setDescription(const QString &description);

signals:
	void carNumberChanged();
	void ownerNameChanged();
	void ownerSurnameChanged();
	void ownerPatronymicChanged();
	void apartmentNumberChanged();
	void parkingPlaceChanged();
	void phoneNumberChanged();
	void descriptionChanged();

private:
	qlonglong id_;
	QString carNumber_;
	QString ownerName_;
	QString ownerSurname_;
	QString ownerPatronymic_;
	QString apartmentNumber_;
	QString parkingPlace_;
	QString phoneNumber_;
	QString description_;
};

#endif // CARNUMBERINFO_H
