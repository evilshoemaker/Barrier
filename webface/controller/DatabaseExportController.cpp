#include "DatabaseExportController.h"

#include "database/Database.h"
#include "database/SyncQueryHandler.h"

DatabaseExportController::DatabaseExportController()
{

}

void DatabaseExportController::service(HttpRequest &request, HttpResponse &response)
{
    QString metod = request.getMethod();

    QString transactionId = Database::requestAllCarList();

    QString csvFileContent;

    SyncQueryHandler queryHandler;
    if (queryHandler.waitResult(transactionId))
    {
        QList<QSqlRecord> records = queryHandler.records();

        for (const QSqlRecord &record : records)
        {
            csvFileContent.append(
                        QString("%1;%2;%3;%4;%5;%6;%7;%8\n")
                        .arg(record.value("car_number").toString())
                        .arg(record.value("surname").toString())
                        .arg(record.value("name").toString())
                        .arg(record.value("patronymic").toString())
                        .arg(record.value("phone_number").toString())
                        .arg(record.value("apartment_number").toString())
                        .arg(record.value("parking_place").toString())
                        .arg(record.value("description").toString())
                        );
        }
    }

    response.setHeader("Content-Description", "File Transfer");
    response.setHeader("Pragma", "public");
    response.setHeader("Expires", "0");
    response.setHeader("Cache-Control", "must-revalidate, post-check=0, pre-check=0");
    response.setHeader("Cache-Control", "public");
    response.setHeader("Content-Type", "text/plain; charset=UTF-8");

    QString contentDisposition = QString("attachment; filename=\"%1-backup.csv\"")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"));
    response.setHeader("Content-Disposition", contentDisposition.toUtf8());

    response.write(csvFileContent.toUtf8(), true);
}
