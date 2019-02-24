#include "DatabaseLogger.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

#include "database/CarNumberInfo.h"
#include "database/Database.h"

DatabaseLogger *DatabaseLogger::instance()
{
	static DatabaseLogger instance;
	return &instance;
}

void DatabaseLogger::addedNewCar(CarNumberInfo *info)
{
	if (info == nullptr)
		return;

	QJsonObject jsonObj;
    jsonObj["id"] = info->id();
	jsonObj["number"] = info->carNumber();
	jsonObj["surname"] = info->ownerSurname();
	jsonObj["name"] = info->ownerName();
    jsonObj["patronymic"] = info->ownerPatronymic();
    jsonObj["apartment_number"] = info->apartmentNumber();
    jsonObj["parking_place"] = info->parkingPlace();
    jsonObj["phone_number"] = info->phoneNumber();

	QJsonDocument jsonDoc(jsonObj);

	Database::executeQuery(DatabaseLogger::instance()->sql_
						   .arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs),
								"add_car",
								QString(jsonDoc.toJson())));
}

void DatabaseLogger::removeCar(CarNumberInfo *info)
{
	if (info == nullptr)
		return;

	QJsonObject jsonObj;
    jsonObj["id"] = info->id();
    jsonObj["number"] = info->carNumber();
    jsonObj["surname"] = info->ownerSurname();
    jsonObj["name"] = info->ownerName();
    jsonObj["patronymic"] = info->ownerPatronymic();
    jsonObj["apartment_number"] = info->apartmentNumber();
    jsonObj["parking_place"] = info->parkingPlace();
    jsonObj["phone_number"] = info->phoneNumber();

	QJsonDocument jsonDoc(jsonObj);

	Database::executeQuery(DatabaseLogger::instance()->sql_
						   .arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs),
								"remove_car",
								QString(jsonDoc.toJson())));
}

void DatabaseLogger::updateCar(CarNumberInfo *info)
{
	if (info == nullptr)
		return;

	QJsonObject jsonObj;
    jsonObj["id"] = info->id();
    jsonObj["number"] = info->carNumber();
    jsonObj["surname"] = info->ownerSurname();
    jsonObj["name"] = info->ownerName();
    jsonObj["patronymic"] = info->ownerPatronymic();
    jsonObj["apartment_number"] = info->apartmentNumber();
    jsonObj["parking_place"] = info->parkingPlace();
    jsonObj["phone_number"] = info->phoneNumber();

	QJsonDocument jsonDoc(jsonObj);

	Database::executeQuery(DatabaseLogger::instance()->sql_
						   .arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs),
								"update_car",
								QString(jsonDoc.toJson())));
}

void DatabaseLogger::openBarrier(CarNumberInfo *info)
{
	if (info == nullptr)
		return;

	QJsonObject jsonObj;
    jsonObj["id"] = info->id();
    jsonObj["number"] = info->carNumber();
    jsonObj["surname"] = info->ownerSurname();
    jsonObj["name"] = info->ownerName();
    jsonObj["patronymic"] = info->ownerPatronymic();
    jsonObj["apartment_number"] = info->apartmentNumber();
    jsonObj["parking_place"] = info->parkingPlace();
    jsonObj["phone_number"] = info->phoneNumber();

	QJsonDocument jsonDoc(jsonObj);

	Database::executeQuery(DatabaseLogger::instance()->sql_
						   .arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs),
								"open_barrier",
								QString(jsonDoc.toJson())));
}

DatabaseLogger::DatabaseLogger(QObject *parent)
	: QObject (parent)
{
	sql_ = QString("INSERT INTO logs (date_time, action, value) VALUES ('%1', '%2', '%3')");
}
