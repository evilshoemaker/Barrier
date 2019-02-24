#include "Gpio.h"

#include <QProcess>

Gpio::Gpio(QObject *parent) : QObject(parent)
{

}

Gpio::~Gpio()
{

}

void Gpio::init(int pin)
{
    QProcess::execute(QString("gpio mode %1 out").arg(pin));
}

void Gpio::digitalWrite(int pin, int val)
{
    QProcess::execute(QString("gpio write %1 %2").arg(pin).arg(val));
}
