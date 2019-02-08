#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

class LoginController : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(LoginController)

public:
    LoginController();
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // LOGINCONTROLLER_H
