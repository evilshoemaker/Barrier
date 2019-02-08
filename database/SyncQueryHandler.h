#ifndef CONTROLLERQUERYHANDLER_H
#define CONTROLLERQUERYHANDLER_H

#include <QObject>
#include <QEventLoop>
#include <QTimer>
#include <QSqlRecord>

class SyncQueryHandler : public QObject
{
	Q_OBJECT
public:
	explicit SyncQueryHandler(int timerInterval = 3000, QObject *parent = nullptr);

	enum QueryHandlerError {
		NoError = 0,
		TimeOutError,
		DatabaseError
	};

	bool waitResult(const QString &transactionId);

	QueryHandlerError error();
	QList<QSqlRecord> records();

private slots:
	void onQueryResults(const QList<QSqlRecord> &recordList, const QString &transactionId);
	void onTimeout();
	void onDatabaseError(const QString &transactionId);

private:
	QueryHandlerError error_;
	QEventLoop eventLoop_;
	QTimer timer_;
	QString transactionId_;
	QList<QSqlRecord> recordList_;
};

#endif // CONTROLLERQUERYHANDLER_H
