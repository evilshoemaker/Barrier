#ifndef DATABASEACCESSOR_H
#define DATABASEACCESSOR_H

#include <QObject>
#include <QSqlDatabase>

class DatabaseAccessor : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseAccessor(QObject *parent = nullptr);

signals:

public slots:

private:
    bool initialize();

    void createTables();
    void createLogsTable();
    void createCarsTable();

    QSqlDatabase database_;

    const QString DATABASE_DRIVER = "QSQLITE";
    const QString DATABASE_HOST = "";
    const QString DATABASE_NAME = "database.db";
    const QString DATABASE_USER = "";
    const QString DATABASE_PASS = "";
};

#endif // DATABASEACCESSOR_H
