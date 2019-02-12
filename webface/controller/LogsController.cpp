#include "LogsController.h"

#include "database/Database.h"
#include "database/SyncQueryHandler.h"
#include "database/CarNumberInfo.h"

#include "webface/RequestMapper.h"

LogsController::LogsController()
{

}

void LogsController::service(HttpRequest &request, HttpResponse &response)
{
	QByteArray language = request.getHeader("Accept-Language");
	response.setHeader("Content-Type", "text/html; charset=UTF-8");

	Template main = RequestMapper::templateCache->getTemplate("index", language);
	Template t = RequestMapper::templateCache->getTemplate(QStringLiteral("logs"), language);

	main.setVariable("isActiveLogs", " active");
	main.setVariable("content", "<div class=\"animated fadeIn\">" + t.toUtf8() + "</div>");

	response.write(main.toUtf8(), true);
}
