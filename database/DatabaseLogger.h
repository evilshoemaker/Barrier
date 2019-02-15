#ifndef DATABASELOGGER_H
#define DATABASELOGGER_H

#include <QObject>

class CarNumberInfo;

class DatabaseLogger : public QObject
{
	Q_OBJECT

public:
	static DatabaseLogger *instance();

	static void addedNewCar(CarNumberInfo *info);
	static void removeCar(CarNumberInfo *info);
	static void updateCar(CarNumberInfo *info);

	Q_INVOKABLE void openBarrier(CarNumberInfo *info);

private:
	DatabaseLogger(QObject *parent = nullptr);

	QString sql_;
};

#endif // DATABASELOGGER_H
