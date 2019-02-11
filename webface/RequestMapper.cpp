#include "RequestMapper.h"

#include "controller/LoginController.h"
#include "controller/IndexController.h"
#include "controller/CarListController.h"
#include "controller/SettingsController.h"
#include "controller/LogsController.h"
#include "controller/AddCarController.h"
#include "controller/EditCarController.h"
#include "controller/RemoveCarController.h"

HttpSessionStore *RequestMapper::sessionStore = nullptr;
TemplateCache *RequestMapper::templateCache = nullptr;
StaticFileController *RequestMapper::staticFileController = nullptr;

RequestMapper::RequestMapper(QObject* parent)
    :HttpRequestHandler(parent)
{

}

RequestMapper::~RequestMapper()
{

}

void RequestMapper::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray path = request.getPath();

	if (path.startsWith("/css") || path.startsWith("/fonts")
            || path.startsWith("/js") || path.startsWith("/img")
            || path.startsWith("/amcharts") || path.startsWith("/chart"))
    {
        staticFileController->service(request, response);
        return;
    }


	/*QByteArray sessionId = sessionStore->getSessionId(request, response);
    if (sessionId.isEmpty() && path != "/login")
    {
        //qDebug("RequestMapper: redirect to login page");
        response.redirect("/login");
        return;
	}*/

    if (path == "/")
    {
		response.redirect("/car-list");
		return;
    }
	else if (path == "/login")
    {
		LoginController().service(request, response);
    }
	else if (path == "/car-list")
	{
		CarListController().service(request, response);
	}
    else if (path == "/logs")
    {
        LogsController().service(request, response);
    }
    else if (path == "/settings")
    {
        SettingsController().service(request, response);
    }
    else if (path == "/car-list/add-car")
    {
        AddCarController().service(request, response);
    }
	else if (path == "/car-list/remove-car")
	{
		RemoveCarController().service(request, response);
	}
	else if (path == "/car-list/edit-car")
	{
		EditCarController().service(request, response);
	}
    else if (path == "/logout")
    {
        HttpSession session = sessionStore->getSession(request, response);
        sessionStore->removeSession(session);

        response.redirect("/");
    }
    else
    {
        response.setStatus(404, "Page not found");
    }
}
