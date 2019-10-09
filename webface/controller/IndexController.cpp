#include "IndexController.h"


IndexController::IndexController()
{

}

void IndexController::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray language = request.getHeader("Accept-Language");
    response.setHeader("Content-Type", "text/html; charset=UTF-8");

    Template t = getTemplate(request, response);

    response.write(t.toUtf8(), true);
}

Template IndexController::getTemplate(HttpRequest &request, HttpResponse &response)
{
    HttpSession session = RequestMapper::sessionStore->getSession(request, response, true);
    QByteArray language = request.getHeader("Accept-Language");

    Template t = RequestMapper::templateCache->getTemplate("index", language);

    if (!isAdminAccess(request, response))
    {
        t.setVariable("isVisibleLogs", "invisible");
        t.setVariable("isVisibleSettings", "invisible");
    }

    t.setVariable("isActiveCarList", "active");

    return t;
}

bool IndexController::isAdminAccess(HttpRequest &request, HttpResponse &response)
{
    HttpSession session = RequestMapper::sessionStore->getSession(request, response, true);

    return session.contains("type") && (session.get("type") == "all");
}
