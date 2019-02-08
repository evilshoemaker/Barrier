#include "SyncQueryHandler.h"

#include "database/Database.h"

SyncQueryHandler::SyncQueryHandler(int timerInterval, QObject *parent) :
	QObject(parent)
{
	timer_.setInterval(timerInterval);
	connect(&timer_, &QTimer::timeout, this, &SyncQueryHandler::onTimeout);
}

QList<QSqlRecord> SyncQueryHandler::records()
{
	return recordList_;
}

void SyncQueryHandler::onQueryResults(const QList<QSqlRecord> &recordList, const QString &transactionId)
{
	if (transactionId != transactionId_)
		return;

	disconnect(Database::instance(), &Database::results, this, &SyncQueryHandler::onQueryResults);
	disconnect(Database::instance(), &Database::error, this, &SyncQueryHandler::onDatabaseError);


	eventLoop_.quit();
	recordList_ = recordList;

	error_ = NoError;
}

void SyncQueryHandler::onTimeout()
{
	eventLoop_.quit();
	error_ = TimeOutError;
}

void SyncQueryHandler::onDatabaseError(const QString &transactionId)
{
	if (transactionId != transactionId_)
		return;

	disconnect(Database::instance(), &Database::results, this, &SyncQueryHandler::onQueryResults);
	disconnect(Database::instance(), &Database::error, this, &SyncQueryHandler::onDatabaseError);

	eventLoop_.quit();
	error_ = DatabaseError;
}

bool SyncQueryHandler::waitResult(const QString &transactionId)
{
	transactionId_ = transactionId;

	connect(Database::instance(), &Database::results, this, &SyncQueryHandler::onQueryResults);
	connect(Database::instance(), &Database::error, this, &SyncQueryHandler::onDatabaseError);

	timer_.start();
	eventLoop_.exec();

	return error_ == NoError;
}
