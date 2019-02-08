#include "IndexController.h"

#include "../RequestMapper.h"

IndexController::IndexController()
{

}

void IndexController::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray language = request.getHeader("Accept-Language");
    response.setHeader("Content-Type", "text/html; charset=UTF-8");

    Template t = RequestMapper::templateCache->getTemplate("index", language);
	t.setVariable("isActiveMeasurements", "active");
    response.write(t.toUtf8(), true);
}
