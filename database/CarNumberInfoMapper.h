#ifndef CARNUMBERINFOMAPPER_H
#define CARNUMBERINFOMAPPER_H

#include "CarNumberInfo.h"

class CarNumberInfoMapper
{
public:
    CarNumberInfoMapper();

    QList<CarNumberInfo *> getByCarNumber(const QString &number, QObject *parent);
};

#endif // CARNUMBERINFOMAPPER_H
