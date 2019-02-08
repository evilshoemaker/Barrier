#ifndef DATABASEINSTANCE_H
#define DATABASEINSTANCE_H

#include <QObject>
#include <QSqlRecord>

class DatabaseThread;

class Database : public QObject
{
	Q_OBJECT

public:
	static Database *instance();

	static QString requestAllCarList();

signals:
	void results(const QList<QSqlRecord> &recordList, const QString &transactionId);
	void error(const QString &transactionId);

private:
	explicit Database(QObject *parent = nullptr);

	DatabaseThread *databaseThread_;
};

#endif // DATABASEINSTANCE_H
