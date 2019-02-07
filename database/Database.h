#ifndef DATABASEINSTANCE_H
#define DATABASEINSTANCE_H

#include <QObject>

class DatabaseThread;

class Database : public QObject
{
	Q_OBJECT

public:
	static Database &instance();

private:
	explicit Database(QObject *parent = nullptr);

	DatabaseThread *databaseThread_;
};

#endif // DATABASEINSTANCE_H
