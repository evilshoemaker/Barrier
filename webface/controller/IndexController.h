#ifndef INDEXCONTROLLER_H
#define INDEXCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

class IndexController : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(IndexController)
public:
    IndexController();
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // INDEXCONTROLLER_H
