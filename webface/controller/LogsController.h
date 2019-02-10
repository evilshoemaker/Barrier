#ifndef LOGSCONTROLLER_H
#define LOGSCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

class LogsController : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(LogsController)

public:
    LogsController();
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // LOGSCONTROLLER_H
