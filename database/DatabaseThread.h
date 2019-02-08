#ifndef DATABASETHREAD_H
#define DATABASETHREAD_H

#include <QThread>
#include <QSqlRecord>

class DatabaseAccessor;

class DatabaseThread : public QThread
{
    Q_OBJECT
public:
    explicit DatabaseThread(QObject *parent = nullptr);
	~DatabaseThread() override;

signals:
	void execute(const QString &query);
	void execute(const QString &query, const QString &transactionId);
	void execute(const QStringList &queryList);

	void results(const QList<QSqlRecord> &recordList, const QString &transactionId);
	void error(const QString &transactionId);

public slots:
	QString executeQuery(const QString &query);

protected:
	void run() override;

private:
	DatabaseAccessor *accessor_;
};

#endif // DATABASETHREAD_H
