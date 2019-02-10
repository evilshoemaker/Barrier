#ifndef CARNUMBERPARSWER_H
#define CARNUMBERPARSWER_H

#include <QObject>

class CarNumberParser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString number READ number WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(QString char1 READ char1 WRITE setChar1 NOTIFY char1Changed)
    Q_PROPERTY(QString char2 READ char2 WRITE setChar2 NOTIFY char2Changed)
    Q_PROPERTY(QString digital READ digital WRITE setDigital NOTIFY digitalChanged)
    Q_PROPERTY(QString region READ region WRITE setRegion NOTIFY regionChanged)

public:
    explicit CarNumberParser(QObject *parent = nullptr);

    QString number();
    void setNumber(const QString &number);

    QString char1();
    void setChar1(const QString &char1);

    QString char2();
    void setChar2(const QString &char2);

    QString digital();
    void setDigital(const QString &digital);

    QString region();
    void setRegion(const QString &region);

signals:
    void numberChanged();
    void char1Changed();
    void char2Changed();
    void digitalChanged();
    void regionChanged();

private:
    QString number_;

    QString char1_;
    QString char2_;
    QString digital_;
    QString region_;
};

#endif // CARNUMBERPARSWER_H
