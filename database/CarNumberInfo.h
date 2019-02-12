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
	Q_PROPERTY(QString parkingPlace READ parkingPlace WRITE setParkingPlace NOTIFY parkingPlaceChanged)
	Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
	Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
	explicit CarNumberInfo(QObject *parent = nullptr);

	qlonglong id() const;
	void setId(qlonglong id);

    QString carNumber() const;
	void setCarNumber(const QString &carNumber);

    QString ownerName() const;
	void setOwnerName(const QString &ownerName);

    QString ownerSurname() const;
	void setOwnerSurname(const QString &ownerSurname);

    QString ownerPatronymic() const;
	void setOwnerPatronymic(const QString &ownerPatronymic);

    QString apartmentNumber() const;
	void setApartmentNumber(const QString &apartmentNumber);

    QString parkingPlace() const;
	void setParkingPlace(const QString &parkingPlace);

    QString phoneNumber() const;
	void setPhoneNumber(const QString &phoneNumber);

    QString description() const;
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
