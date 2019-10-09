#ifndef DATABASEEXPORTCONTROLLER_H
#define DATABASEEXPORTCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

class DatabaseExportController : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(DatabaseExportController)

public:
    DatabaseExportController();
    void service(HttpRequest& request, HttpResponse& response);

signals:

public slots:
};

#endif // DATABASEEXPORTCONTROLLER_H
