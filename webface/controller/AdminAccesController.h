#ifndef ADMINACCESCONTROLLER_H
#define ADMINACCESCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

class AdminAccesController : public HttpRequestHandler
{
public:
    AdminAccesController();

protected:
    bool isAdminAccess(HttpRequest &request, HttpResponse &response);
};

#endif // ADMINACCESCONTROLLER_H
