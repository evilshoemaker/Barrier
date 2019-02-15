#include "LogsController.h"

#include <QDateTime>

#include "database/Database.h"
#include "database/SyncQueryHandler.h"
#include "database/CarNumberInfo.h"

#include "webface/RequestMapper.h"

LogsController::LogsController()
{

}

void LogsController::service(HttpRequest &request, HttpResponse &response)
{
	bool isExtraOptions = false;

	QString isShowAllStr = request.getParameter("show_all");
	bool isShowAll = isShowAllStr == "true" || isExtraOptions;

	QByteArray language = request.getHeader("Accept-Language");
	response.setHeader("Content-Type", "text/html; charset=UTF-8");

	Template main = RequestMapper::templateCache->getTemplate("index", language);
	Template t = RequestMapper::templateCache->getTemplate(QStringLiteral("logs"), language);

	QString transactionId = Database::requestAllLogs();

	QString tableBody;

	SyncQueryHandler queryHandler;
	if (queryHandler.waitResult(transactionId))
	{
		QList<QSqlRecord> records = queryHandler.records();

		for (const QSqlRecord &record : records)
		{
			QString carId = record.value("id").toString();

			tableBody.append("<tr class=\"user-item\">");

			tableBody.append(QString("<form id=\"row_form_id_%1\"></form>"
									 "<input type=\"hidden\" name=\"id\" value=\"%1\" form=\"row_form_id_%1\"/>")
							 .arg(carId));

			QDateTime time = QDateTime::fromString(record.value("date_time").toString(), Qt::ISODateWithMs);
			tableBody.append(QString("<td>%1</td>").arg(time.toString("yyyy-MM-dd HH:mm:ss")));

			QString action = record.value("action").toString();
			if (action == "add_car")
			{
				tableBody.append(QString("<td>%1</td>").arg("Добавлена запись"));
			}
			else if (action == "remove_car")
			{
				tableBody.append(QString("<td>%1</td>").arg("Удалена запись"));
			}
			else if (action == "update_car")
			{
				tableBody.append(QString("<td>%1</td>").arg("Обновлена запись"));
			}
			else if (action == "open_barrier")
			{
				tableBody.append(QString("<td>%1</td>").arg("Открыт шлагбаум"));
			}

			tableBody.append(QString("<td>%1</td>").arg(record.value("value").toString()));

			tableBody.append("</tr>");
		}
	}

	t.setVariable("logsTableBody", tableBody.toUtf8());

	main.setVariable("isActiveLogs", " active");
	main.setVariable("content", "<div class=\"animated fadeIn\">" + t.toUtf8() + "</div>");

	response.write(main.toUtf8(), true);
}
