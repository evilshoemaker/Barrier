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

QString Database::requestAllCarList(const QString &transactionId)
{
	QString sql = QString("SELECT * FROM cars");
    return Database::instance()->databaseThread_->executeQuery(sql, transactionId);
}

QString Database::addCar(const CarNumberInfo &car)
{
    QString sql = QString("INSERT INTO cars ("
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

Database::Database(QObject *parent) :
	QObject(parent),
	databaseThread_(new DatabaseThread(this))
{
	connect(databaseThread_, &DatabaseThread::error, this, &Database::error);
	connect(databaseThread_, &DatabaseThread::results, this, &Database::results);

	databaseThread_->start();
}
