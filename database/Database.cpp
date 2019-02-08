#include "Database.h"

#include "DatabaseThread.h"

Database *Database::instance()
{
	static Database instance;
	return &instance;
}

Database::Database(QObject *parent) :
	QObject(parent),
	databaseThread_(new DatabaseThread(this))
{
	connect(databaseThread_, &DatabaseThread::error, this, &Database::error);
	connect(databaseThread_, &DatabaseThread::results, this, &Database::results);
}
