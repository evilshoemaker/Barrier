#include "DatabaseImportController.h"

#include "core/Util.h"

#include "database/Database.h"
#include "database/SyncQueryHandler.h"

DatabaseImportController::DatabaseImportController()
{

}

void DatabaseImportController::service(HttpRequest &request, HttpResponse &response)
{
    if (request.getParameter("action") == "upload-file")
    {
        QTemporaryFile* file = request.getUploadedFile("csv-file");

        if (file)
        {
            QByteArray fileBytes;

            while (!file->atEnd() && !file->error())
            {
                fileBytes.append(file->read(65536));
            }

            QString content = QString::fromUtf8(fileBytes);

            QStringList list = content.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);

            for (QString line : list)
            {
                insertOrUpdate(line);
            }
        }


        response.redirect("/settings");
    }
}

void DatabaseImportController::insertOrUpdate(const QString &row)
{
    QStringList items = row.split(";");
    if (items.size() >= 8)
    {
        QString transactionId = Database::requestCarByNumber(items.at(0).trimmed());
        SyncQueryHandler queryHandler;
        if (queryHandler.waitResult(transactionId))
        {
            CarNumberInfo car;
            car.setCarNumber(items.at(0).trimmed());
            car.setOwnerSurname(items.at(1).trimmed());
            car.setOwnerName(items.at(2).trimmed());
            car.setOwnerPatronymic(items.at(3).trimmed());
            car.setPhoneNumber(items.at(4).trimmed());
            car.setApartmentNumber(items.at(5).trimmed());
            car.setParkingPlace(items.at(6).trimmed());
            car.setDescription(items.at(7).trimmed());

            QList<QSqlRecord> records = queryHandler.records();
            if (records.isEmpty())
            {
                transactionId = Database::addCar(car);
                queryHandler.waitResult(transactionId);
            }
            else
            {
                QSqlRecord record = records.first();

                car.setId(record.value("id").toLongLong());

                transactionId = Database::updateCar(car);
                queryHandler.waitResult(transactionId);
            }
        }
    }
}
