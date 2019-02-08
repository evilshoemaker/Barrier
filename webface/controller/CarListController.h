#ifndef CARLISTCONTROLLER_H
#define CARLISTCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

class CarListController : public HttpRequestHandler
{
	Q_OBJECT
	Q_DISABLE_COPY(CarListController)

public:
	CarListController();
	void service(HttpRequest& request, HttpResponse& response);

};

#endif // CARLISTCONTROLLER_H
