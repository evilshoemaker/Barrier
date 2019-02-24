#ifndef GPIO_H
#define GPIO_H

#include <QObject>

class Gpio : public QObject
{
    Q_OBJECT
public:
    explicit Gpio(QObject *parent = nullptr);

    Q_INVOKABLE void init(int pin);

    Q_INVOKABLE void digitalWrite(int pin, int val);
};

#endif // GPIO_H
