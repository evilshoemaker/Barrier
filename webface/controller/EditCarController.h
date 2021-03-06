#ifndef EDITCARCONTROLLER_H
#define EDITCARCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

#include "webface/RequestMapper.h"

class EditCarController : public HttpRequestHandler
{
	Q_OBJECT
	Q_DISABLE_COPY(EditCarController)

public:
	EditCarController();
	void service(HttpRequest& request, HttpResponse& response);
	bool fillTemplateFromDb(Template &t, qlonglong id, QString &error);
	void parseAndSave(HttpRequest &request, HttpResponse &response);
};

#endif // EDITCARCONTROLLER_H
