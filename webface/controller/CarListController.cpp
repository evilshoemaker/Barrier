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

            tableBody.append(QString("<td>%1</td>").arg(record.value("car_number").toString()));
            tableBody.append(QString("<td>%1 %2 %3</td>")
                             .arg(record.value("surname").toString())
                             .arg(record.value("name").toString())
                             .arg(record.value("patronymic").toString()));
            tableBody.append(QString("<td>%1</td>").arg(record.value("phone_number").toString()));
            tableBody.append(QString("<td>%1</td>").arg(record.value("apartment_number").toString()));
            tableBody.append(QString("<td>%1</td>").arg(record.value("parking_place").toString()));
            tableBody.append(QString("<td>%1</td>").arg(record.value("description").toString()));
			tableBody.append(QString("<td class=\"action-btns\" width=\"210\"> "
							 "  <button type=\"submit\" name=\"car_edit_button\" class=\"mr-1 btn btn-info btn-sm\" form=\"row_form_id_%1\" onclick=\"return editCar();\" value=\"%1\">Редактировать</button>"
							 "  <button type=\"submit\" name=\"car_remove_button\" class=\"btn btn-warning btn-sm\" form=\"row_form_id_%1\" onclick=\"return tryingToRemoveCar();\" value=\"%1\">Удалить</button>"
							 "</td>").arg(carId));

            tableBody.append("</tr>");
        }
	}

    t.setVariable("carListTableBody", tableBody.toUtf8());

    mainTemplate.setVariable("isActiveCarList", "active");
    mainTemplate.setVariable("title", "Список автомобилей");

	mainTemplate.setVariable("content", "<div class=\"animated fadeIn\">" + t.toUtf8() + "</div>");
	response.write(mainTemplate.toUtf8(), true);
}
