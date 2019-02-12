#include "EditCarController.h"

#include "database/Database.h"
#include "database/SyncQueryHandler.h"
#include "database/CarNumberInfo.h"

#include "core/Util.h"

EditCarController::EditCarController()
{

}

void EditCarController::service(HttpRequest &request, HttpResponse &response)
{
	QByteArray metod = request.getMethod();
	if (metod == "GET")
	{
		bool isSuccessTransform = false;
		qlonglong carInfoId = request.getParameter("id").toLongLong(&isSuccessTransform);

		if (!isSuccessTransform)
		{
			response.write(Util::makeJsonResult("error", tr("Отсуствует или не верный обязательный параметр")));
			return;
		}

		QByteArray language = request.getHeader("Accept-Language");
		response.setHeader("Content-Type", "text/html; charset=UTF-8");

		Template t = RequestMapper::templateCache->getTemplate("modal/edit-car", language);

		QString error;
		if (!fillTemplateFromDb(t, carInfoId, error))
		{
			response.write(Util::makeJsonResult("error", error));
			return;
		}

		response.write(t.toUtf8(), true);
	}
	else if (metod == "POST")
	{
		parseAndSave(request, response);
	}
}

bool EditCarController::fillTemplateFromDb(Template &t, qlonglong id, QString &error)
{
	QString transactionId = Database::requestCar(id);
	SyncQueryHandler queryHandler;
	if (!queryHandler.waitResult(transactionId))
	{
		error = tr("Не удалось получить выбранную запись. Ошибка БД");
		return false;
	}

	QList<QSqlRecord> records = queryHandler.records();
	if (records.isEmpty())
	{
		error = tr("Не удалось получить выбранную запись. Отсутствует запись");
		return false;
	}

	QSqlRecord record = records.first();

	t.setVariable("id", record.value("id").toString());
	t.setVariable("carNumber", record.value("car_number").toString());
	t.setVariable("ownerSurname", record.value("surname").toString());
	t.setVariable("ownerName", record.value("name").toString());
	t.setVariable("ownerPatronymic", record.value("patronymic").toString());
	t.setVariable("parkingPlace", record.value("parking_place").toString());
	t.setVariable("apartmentNumber", record.value("apartment_number").toString());
	t.setVariable("phone", record.value("phone_number").toString());
	t.setVariable("description", record.value("description").toString());

	return true;
}

void EditCarController::parseAndSave(HttpRequest &request, HttpResponse &response)
{
	bool isSuccessTransform = false;
	qlonglong carInfoId = request.getParameter("id").toLongLong(&isSuccessTransform);

	if (!isSuccessTransform)
	{
		response.write(Util::makeJsonResult("error", tr("Отсуствует или не верный обязательный параметр")));
		return;
	}

	QString carNumber = request.getParameter("car_number");
	QString ownerSurname = request.getParameter("owner_surname");
	QString ownerName = request.getParameter("owner_name");
	QString ownerPatronymic = request.getParameter("owner_patronymic");
	QString parkingPlace = request.getParameter("parking_place");
	QString apartmentNumber = request.getParameter("apartment_number");
	QString phone = request.getParameter("phone");
	QString description = request.getParameter("description");

	if (carNumber.isEmpty())
	{
		response.write(Util::makeJsonResult("error", "Не указан номер автомобиля"));
		return;
	}

	if (ownerSurname.isEmpty())
	{
		response.write(Util::makeJsonResult("error", "Не указана фамилия владельца"));
		return;
	}

	if (ownerName.isEmpty())
	{
		response.write(Util::makeJsonResult("error", "Не указано имя владельца"));
		return;
	}

	CarNumberInfo info;

	info.setId(carInfoId);
	info.setCarNumber(carNumber.toUpper());
	info.setOwnerSurname(ownerSurname);
	info.setOwnerName(ownerName);
	info.setOwnerPatronymic(ownerPatronymic);
	info.setParkingPlace(parkingPlace);
	info.setApartmentNumber(apartmentNumber);
	info.setPhoneNumber(phone);
	info.setDescription(description);

	QString transactionId = Database::updateCar(info);

	SyncQueryHandler queryHandler;
	if (!queryHandler.waitResult(transactionId))
	{
		response.write(Util::makeJsonResult("error", "Ошибка обновления записи"));
		return;
	}

	response.write(Util::makeJsonResult("success", ""));
}
