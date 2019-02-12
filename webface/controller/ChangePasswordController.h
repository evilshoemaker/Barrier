#ifndef CHANGEPASSWORDCONTROLLER_H
#define CHANGEPASSWORDCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

class ChangePasswordController : public HttpRequestHandler
{
	Q_OBJECT
	Q_DISABLE_COPY(ChangePasswordController)

public:
	ChangePasswordController();
	void service(HttpRequest& request, HttpResponse& response);

};

#endif // CHANGEPASSWORDCONTROLLER_H
