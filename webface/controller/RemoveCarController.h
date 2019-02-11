#ifndef REMOVECARCONTROLLER_H
#define REMOVECARCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

class RemoveCarController : public HttpRequestHandler
{
	Q_OBJECT
	Q_DISABLE_COPY(RemoveCarController)

public:
	RemoveCarController();
	void service(HttpRequest& request, HttpResponse& response);

private:
	void parseAndRemove(HttpRequest &request, HttpResponse &response);
};

#endif // REMOVECARCONTROLLER_H
