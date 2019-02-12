#include "Database.h"

#include "DatabaseThread.h"

Database *Database::instance()
{
	static Database instance;
    return &instance;
}

QString Database::executeQuery(const QString &query, const QString &transactionId)
{
	return Database::instance()->databaseThread_->executeQuery(query, transactionId);
}

void Database::emptySelect()
{
	QString sql = QString("SELECT 1");
	Database::instance()->databaseThread_->executeQuery(sql);
}

QString Database::requestAllCarList(const QString &transactionId)
{
	QString sql = QString("SELECT * FROM cars");
	return Database::instance()->databaseThread_->executeQuery(sql, transactionId);
}

QString Database::requestCar(qlonglong id)
{
	QString sql = QString("SELECT * FROM cars WHERE id = %1");
	return Database::instance()->databaseThread_->executeQuery(sql.arg(id));
}

QString Database::addCar(const CarNumberInfo &car)
{
	const QString sql = QString("INSERT INTO cars ("
                          " car_number, "
                          " surname, "
                          " name, "
                          " patronymic,"
                          " apartment_number, "
                          " parking_place, "
                          " phone_number, "
                          " description) "
                          "VALUES ("
                          " '%1', "
                          " '%2', "
                          " '%3', "
                          " '%4', "
                          " '%5', "
                          " '%6', "
                          " '%7', "
                          " '%8')");
    return Database::instance()->
            databaseThread_->executeQuery(sql
                                          .arg(car.carNumber(),
                                               car.ownerSurname(),
                                               car.ownerName(),
                                               car.ownerPatronymic(),
                                               car.apartmentNumber(),
                                               car.parkingPlace(),
                                               car.phoneNumber(),
                                               car.phoneNumber())
										  );
}

QString Database::updateCar(const CarNumberInfo &car)
{
	const QString sql = QString("UPDATE cars SET"
						  " car_number = '%1', "
						  " surname = '%2'"
						  " name = '%3', "
						  " patronymic = '%4, "
						  " apartment_number = '%5', "
						  " parking_place = '%6', "
						  " phone_number = '%7', "
						  " description = '%8' "
						  " WHERE id = %9");
	return Database::instance()->
			databaseThread_->executeQuery(sql
										  .arg(car.carNumber(),
											   car.ownerSurname(),
											   car.ownerName(),
											   car.ownerPatronymic(),
											   car.apartmentNumber(),
											   car.parkingPlace(),
											   car.phoneNumber(),
											   car.phoneNumber())
										  .arg(car.id())
										  );
}

QString Database::removeCar(qlonglong id)
{
	const QString sql = QString("DELETE FROM cars WHERE id=%1");
	return Database::instance()->
			databaseThread_->executeQuery(sql.arg(id));
}

Database::Database(QObject *parent) :
	QObject(parent),
	databaseThread_(new DatabaseThread(this))
{
	connect(databaseThread_, &DatabaseThread::error, this, &Database::error);
	connect(databaseThread_, &DatabaseThread::results, this, &Database::results);

	databaseThread_->start();
}
