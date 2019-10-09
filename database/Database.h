#ifndef DATABASEINSTANCE_H
#define DATABASEINSTANCE_H

#include <QObject>
#include <QSqlRecord>
#include <QDateTime>

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

    static QString requestCarByNumber(const QString &number);

    static QString addCar(const CarNumberInfo &car);

	static QString updateCar(const CarNumberInfo &car);

	static QString removeCar(qlonglong id);

	static QString requestAllLogs();

	static QString requestLogForDate(const QDateTime &beginDate, const QDateTime &endDate);

signals:
	void results(const QList<QSqlRecord> &recordList, const QString &transactionId);
	void error(const QString &transactionId);

private:
	explicit Database(QObject *parent = nullptr);

	DatabaseThread *databaseThread_;
};

#endif // DATABASEINSTANCE_H
