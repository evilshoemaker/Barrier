#include "CarNumberInfoMapper.h"

#include <QSqlRecord>
#include <QVariant>
#include <QRegularExpression>

#include "Database.h"
#include "SyncQueryHandler.h"

CarNumberInfoMapper::CarNumberInfoMapper()
{

}

QList<CarNumberInfo *> CarNumberInfoMapper::getByCarNumber(const QString &number, QObject *parent)
{
    QList<CarNumberInfo *> results;

    const QString sql = QString("SELECT * FROM cars"
                                " WHERE car_number LIKE '%%1%'");

    QString transactionId = Database::executeQuery(sql.arg(number));

    SyncQueryHandler syncQueryHandler;
    if (!syncQueryHandler.waitResult(transactionId))
    {
        return results;
    }

    QList<QSqlRecord> records = syncQueryHandler.records();

    QString pattern = QString("^[A-ZА-Я]%1[A-ZА-Я][A-ZА-Я]\\d\\d?[\\d]").arg(number);
    QRegularExpression re(pattern);

    for (const QSqlRecord &record : records)
    {
        QString carNumber = record.value("car_number").toString();

        QRegularExpressionMatch match = re.match(carNumber, 0, QRegularExpression::PartialPreferCompleteMatch);
        if (match.hasMatch())
        {
            CarNumberInfo *info = new CarNumberInfo(parent);

            info->setCarNumber(carNumber);
            info->setOwnerName(record.value("name").toString());
            info->setOwnerSurname(record.value("surname").toString());
            info->setOwnerPatronymic(record.value("patronymic").toString());
            info->setApartmentNumber(record.value("apartment_number").toString());
            info->setParkingPlace(record.value("parking_place").toString());
            info->setPhoneNumber(record.value("phone_number").toString());
            info->setDescription(record.value("description").toString());

            results.append(info);
        }
    }

    return results;
}
