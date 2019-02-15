#include "DatabaseAccessor.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include "core/Variables.h"
#include "core/Util.h"

DatabaseAccessor::DatabaseAccessor(QObject *parent) :
    QObject(parent)
{
    if (initialize()) {
        createTables();
    }
}

void DatabaseAccessor::execute(const QString &query)
{
    QList<QSqlRecord> recordList;
    QSqlQuery q(database_);

    if (!q.exec(query))
    {
        qWarning() << "Failed to execute SQL query:" << q.lastError().text();
		emit error("");
        return;
    }
    else
    {
        while (q.next())
        {
            recordList.append(q.record());
        }
    }

    emit results(recordList);
}

void DatabaseAccessor::execute(const QString &query, const QString &transactionId)
{
    QList<QSqlRecord> recordList;
    QSqlQuery q(database_);

    if (!q.exec(query))
    {
        qWarning() << "Failed to execute SQL query:" << q.lastError().text();
		emit error(transactionId);
        return;
    }
    else
    {
        while (q.next())
        {
            recordList.append(q.record());
        }
    }

    emit results(recordList, transactionId);
}

bool DatabaseAccessor::initialize()
{
    QString databaseName = Variables::databaseFilePath();
    QString connectonName = Util::createStringUuid();

    database_ = QSqlDatabase::addDatabase(DATABASE_DRIVER, connectonName);
    database_.setDatabaseName(databaseName);
    database_.setHostName(DATABASE_HOST);
    database_.setUserName(DATABASE_USER);
    database_.setPassword(DATABASE_PASS);
    database_.setConnectOptions("QSQLITE_BUSY_TIMEOUT=10000");

    if (!database_.open())
    {
        qWarning() << "Unable to connect to database, giving up:" << database_.lastError().text();
        return false;
    }

    return true;
}

void DatabaseAccessor::createTables()
{
    createCarsTable();
    createLogsTable();
}

void DatabaseAccessor::createLogsTable()
{
    if (database_.tables().contains("logs"))
    {
        return;
    }

    QStringList queryList;
    queryList.append("CREATE TABLE logs ("
					 " id INTEGER NOT NULL PRIMARY KEY,"
					 " date_time TEXT NOT NULL, "
					 " action TEXT NOT NULL, "
					 " value TEXT NOT NULL);");

    QSqlQuery q(database_);

    for (int i = 0; i < queryList.count(); ++i)
    {
        if (!q.exec(queryList.at(i).toLocal8Bit().constData()))
        {
            qWarning() << "Failed to create table:" << q.lastError().text();
            continue;
        }
    }
}

void DatabaseAccessor::createCarsTable()
{
    if (database_.tables().contains("cars"))
    {
        return;
    }

    QStringList queryList;
    queryList.append("CREATE TABLE cars ("
                     " id INTEGER NOT NULL PRIMARY KEY,"
                     " car_number TEXT NOT NULL,"
                     " name TEXT NOT NULL,"
                     " surname TEXT NOT NULL,"
                     " patronymic TEXT NOT NULL,"
                     " apartment_number DEFAULT NULL,"
                     " parking_place DEFAULT NULL,"
                     " phone_number DEFAULT NULL,"
                     " description TEXT DEFAULT '',"
                     " CONSTRAINT unique_car_number UNIQUE (car_number));");

    QSqlQuery q(database_);

    for (int i = 0; i < queryList.count(); ++i)
    {
        if (!q.exec(queryList.at(i).toLocal8Bit().constData()))
        {
            qWarning() << "Failed to create table:" << q.lastError().text();
            continue;
        }
    }
}
