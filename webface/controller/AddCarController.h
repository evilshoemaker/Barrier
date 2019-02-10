#ifndef ADDCARLIST_H
#define ADDCARLIST_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

class AddCarController : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(AddCarController)

public:
    AddCarController();
    void service(HttpRequest& request, HttpResponse& response);

private:
    void parseAndSave(HttpRequest &request, HttpResponse &response);
    void writeResult(HttpResponse &response, const QString &result, const QString &message);
};

#endif // ADDCARLIST_H
