#include "DatabaseAccessor.h"

#include "core/Variables.h"
#include "core/Util.h"

DatabaseAccessor::DatabaseAccessor(QObject *parent) :
    QObject(parent)
{

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
}

void DatabaseAccessor::createTables()
{

}
