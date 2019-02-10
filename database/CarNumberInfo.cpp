#include "CarNumberInfo.h"

CarNumberInfo::CarNumberInfo(QObject *parent) :
	QObject(parent)
{

}

qlonglong CarNumberInfo::id()
{
	return id_;
}

void CarNumberInfo::setId(qlonglong id)
{
	id_ = id;
}

QString CarNumberInfo::carNumber() const
{
	return carNumber_;
}

void CarNumberInfo::setCarNumber(const QString &carNumber)
{
	if (carNumber_ == carNumber)
		return;

	carNumber_ = carNumber;
	emit carNumberChanged();
}

QString CarNumberInfo::ownerName() const
{
	return ownerName_;
}

void CarNumberInfo::setOwnerName(const QString &ownerName)
{
	if (ownerName_ == ownerName)
		return;

	ownerName_ = ownerName;
	emit ownerNameChanged();
}

QString CarNumberInfo::ownerSurname() const
{
	return ownerSurname_;
}

void CarNumberInfo::setOwnerSurname(const QString &ownerSurname)
{
	if (ownerSurname_ == ownerSurname)
		return;

	ownerSurname_ = ownerSurname;
	emit ownerSurnameChanged();
}

QString CarNumberInfo::ownerPatronymic() const
{
	return ownerPatronymic_;
}

void CarNumberInfo::setOwnerPatronymic(const QString &ownerPatronymic)
{
	if (ownerPatronymic_ == ownerPatronymic)
		return;

	ownerPatronymic_ = ownerPatronymic;
	emit ownerPatronymicChanged();
}

QString CarNumberInfo::apartmentNumber() const
{
	return apartmentNumber_;
}

void CarNumberInfo::setApartmentNumber(const QString &apartmentNumber)
{
	if (apartmentNumber_ == apartmentNumber)
		return;

	apartmentNumber_ = apartmentNumber;
	emit apartmentNumberChanged();
}

QString CarNumberInfo::parkingPlace() const
{
	return parkingPlace_;
}

void CarNumberInfo::setParkingPlace(const QString &parkingPlace)
{
	if (parkingPlace_ == parkingPlace)
		return;

	parkingPlace_ = parkingPlace;
	emit parkingPlaceChanged();
}

QString CarNumberInfo::phoneNumber() const
{
	return phoneNumber_;
}

void CarNumberInfo::setPhoneNumber(const QString &phoneNumber)
{
	if (phoneNumber_ == phoneNumber)
		return;

	phoneNumber_ = phoneNumber;
	emit phoneNumberChanged();
}

QString CarNumberInfo::description() const
{
	return description_;
}

void CarNumberInfo::setDescription(const QString &description)
{
	if (description_ == description)
		return;

	description_ = description;
	emit descriptionChanged();
}
