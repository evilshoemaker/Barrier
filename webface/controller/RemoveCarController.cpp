#include "RemoveCarController.h"

#include "core/Util.h"

#include "database/Database.h"
#include "database/DatabaseLogger.h"
#include "database/SyncQueryHandler.h"
#include "database/CarNumberInfo.h"
#include "database/CarNumberInfoMapper.h"

RemoveCarController::RemoveCarController()
{

}

void RemoveCarController::service(HttpRequest &request, HttpResponse &response)
{
	QString metod = request.getMethod();
	if (metod == "POST")
	{
		parseAndRemove(request, response);
		return;
	}

	response.write(Util::makeJsonResult("error", tr("Не верный запрос")));
}

void RemoveCarController::parseAndRemove(HttpRequest &request, HttpResponse &response)
{
	bool isSuccessTransform = false;
	qlonglong carInfoId = request.getParameter("id").toLongLong(&isSuccessTransform);

	if (!isSuccessTransform)
	{
		response.write(Util::makeJsonResult("error", tr("Отсуствует или не верный обязательный параметр")));
		return;
	}

	CarNumberInfoMapper mapper;
	CarNumberInfo *carInfo = mapper.getById(carInfoId, this);

	DatabaseLogger::removeCar(carInfo);

	QString transactionId = Database::removeCar(carInfoId);

	SyncQueryHandler queryHandler;
	if (!queryHandler.waitResult(transactionId))
	{
		response.write(Util::makeJsonResult("error", tr("Ошибка удаления записи")));
		return;
	}

	response.write(Util::makeJsonResult("success"));
}
