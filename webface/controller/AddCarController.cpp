#include "AddCarController.h"

#include "database/Database.h"
#include "database/SyncQueryHandler.h"
#include "database/CarNumberInfo.h"

#include "webface/RequestMapper.h"

AddCarController::AddCarController()
{

}

void AddCarController::service(HttpRequest &request, HttpResponse &response)
{
    QString metod = request.getMethod();

    if (metod == "GET")
    {
        QByteArray language = request.getHeader("Accept-Language");
        response.setHeader("Content-Type", "text/html; charset=UTF-8");

        Template t = RequestMapper::templateCache->getTemplate("modal/add-new-car", language);
        response.write(t.toUtf8(), true);
    }
    else if (metod == "POST")
    {
        parseAndSave(request, response);
    }
}

void AddCarController::parseAndSave(HttpRequest &request, HttpResponse &response)
{
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
        writeResult(response, "error", "Не указан номер автомобиля");
        return;
    }

    if (ownerSurname.isEmpty())
    {
        writeResult(response, "error", "Не указана фамилия владельца");
        return;
    }

    if (ownerName.isEmpty())
    {
        writeResult(response, "error", "Не указано имя владельца");
        return;
    }

    CarNumberInfo info;

    info.setCarNumber(carNumber.toUpper());
    info.setOwnerSurname(ownerSurname);
    info.setOwnerName(ownerName);
    info.setOwnerPatronymic(ownerPatronymic);
    info.setParkingPlace(parkingPlace);
    info.setApartmentNumber(apartmentNumber);
    info.setPhoneNumber(phone);
    info.setDescription(description);

    QString transactionId = Database::addCar(info);

    SyncQueryHandler queryHandler;
    if (!queryHandler.waitResult(transactionId))
    {
        writeResult(response, "error", "Ошибка добавления записи");
        return;
    }

    writeResult(response, "success", "");
}

void AddCarController::writeResult(HttpResponse &response, const QString &result, const QString &message)
{
    QString json = "{ \"result\":\"%1\", \"message\":\"%2\" }";
    response.write(json.arg(result, message).toUtf8());
}
