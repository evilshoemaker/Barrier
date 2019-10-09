#ifndef DATABASEIMPORTCONTROLLER_H
#define DATABASEIMPORTCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

class DatabaseImportController : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(DatabaseImportController)

public:
    DatabaseImportController();
    void service(HttpRequest& request, HttpResponse& response);

signals:

public slots:

private:
    void insertOrUpdate(const QString &row);
};

#endif // DATABASEIMPORTCONTROLLER_H
