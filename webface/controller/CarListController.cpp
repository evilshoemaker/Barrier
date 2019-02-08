#include "CarListController.h"

#include "database/Database.h"
#include "database/SyncQueryHandler.h"

#include "webface/RequestMapper.h"

CarListController::CarListController()
{

}

void CarListController::service(HttpRequest &request, HttpResponse &response)
{
	QByteArray language = request.getHeader("Accept-Language");
	response.setHeader("Content-Type", "text/html; charset=UTF-8");

	Template mainTemplate = RequestMapper::templateCache->getTemplate("index", language);
	Template t = RequestMapper::templateCache->getTemplate(QStringLiteral("car-list"), language);

	QString transactionId = Database::requestAllCarList();

	SyncQueryHandler queryHandler;
	if (!queryHandler.waitResult(transactionId))
	{

	}

	QList<QSqlRecord> records = queryHandler.records();

	mainTemplate.setVariable("content", "<div class=\"animated fadeIn\">" + t.toUtf8() + "</div>");
	response.write(mainTemplate.toUtf8(), true);
}
