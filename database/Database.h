#ifndef DATABASEINSTANCE_H
#define DATABASEINSTANCE_H

#include <QObject>
#include <QSqlRecord>

#include "CarNumberInfo.h"

class DatabaseThread;

class Database : public QObject
{
	Q_OBJECT

public:
	static Database *instance();

    static QString executeQuery(const QString &query, const QString &transactionId = "");

	static void emptySelect();

    static QString requestAllCarList(const QString &transactionId = "");

	static QString requestCar(qlonglong id);

    static QString addCar(const CarNumberInfo &car);

	static QString updateCar(const CarNumberInfo &car);

	static QString removeCar(qlonglong id);

signals:
	void results(const QList<QSqlRecord> &recordList, const QString &transactionId);
	void error(const QString &transactionId);

private:
	explicit Database(QObject *parent = nullptr);

	DatabaseThread *databaseThread_;
};

#endif // DATABASEINSTANCE_H
