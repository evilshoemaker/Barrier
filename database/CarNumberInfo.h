#ifndef CARNUMBERINFO_H
#define CARNUMBERINFO_H

#include <QObject>

class CarNumberInfo : public QObject
{
	Q_OBJECT
public:
	explicit CarNumberInfo(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CARNUMBERINFO_H