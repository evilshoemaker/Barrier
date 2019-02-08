#include "DatabaseThread.h"

#include "DatabaseAccessor.h"

#include "core/Util.h"

DatabaseThread::DatabaseThread(QObject *parent) :
    QThread(parent)
{

}

DatabaseThread::~DatabaseThread()
{
	delete accessor_;
}

QString DatabaseThread::executeQuery(const QString &query)
{
	QString transactionId = Util::createStringUuid();
	emit execute(query, transactionId);
	return transactionId;
}

void DatabaseThread::run()
{
	accessor_ = new DatabaseAccessor;

	connect(this, static_cast<void (DatabaseThread::*)(const QString &)>(&DatabaseThread::execute),
			accessor_, static_cast<void (DatabaseAccessor::*)(const QString &)>(&DatabaseAccessor::execute));

	/*connect(this, static_cast<void (DatabaseThread::*)(const QStringList &)>(&DatabaseThread::execute),
			accessor_, static_cast<void (DatabaseAccessor::*)(const QStringList &)>(&DatabaseAccessor::execute));*/

	connect(this, static_cast<void (DatabaseThread::*)(const QString &, const QString &)>(&DatabaseThread::execute),
			accessor_, static_cast<void (DatabaseAccessor::*)(const QString &, const QString &)>(&DatabaseAccessor::execute));

	connect(accessor_, static_cast<void (DatabaseAccessor::*)(const QList<QSqlRecord> &, const QString &)>(&DatabaseAccessor::results),
			this, &DatabaseThread::results);

	connect(accessor_, &DatabaseAccessor::error, this, &DatabaseThread::error);

	exec();
}
