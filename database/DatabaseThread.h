#ifndef DATABASETHREAD_H
#define DATABASETHREAD_H

#include <QThread>

class DatabaseThread : public QThread
{
    Q_OBJECT
public:
    explicit DatabaseThread(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DATABASETHREAD_H
