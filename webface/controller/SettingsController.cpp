#include "SettingsController.h"

#include "database/Database.h"
#include "database/SyncQueryHandler.h"
#include "database/CarNumberInfo.h"

#include "webface/RequestMapper.h"

#include "core/Settings.h"
#include "core/Util.h"

SettingsController::SettingsController()
{

}

void SettingsController::service(HttpRequest &request, HttpResponse &response)
{
	QString metod = request.getMethod();
	if (metod == "POST")
	{

		QString login = request.getParameter("login");

		if (login.isEmpty())
		{
			response.write(Util::makeJsonResult("error", "Не указан номер автомобиля"));
			return;
		}

		Settings::instance().setLogin(login);

		Settings::instance().save();
	}

	QByteArray language = request.getHeader("Accept-Language");
	response.setHeader("Content-Type", "text/html; charset=UTF-8");

	Template main = RequestMapper::templateCache->getTemplate("index", language);
	Template t = RequestMapper::templateCache->getTemplate(QStringLiteral("settings"), language);

	t.setVariable(QStringLiteral("login"), Settings::instance().login());

	main.setVariable("isActiveSettings", " active");
	main.setVariable("title", "Settings");
	main.setVariable("content", "<div class=\"animated fadeIn\">" + t.toUtf8() + "</div>");

	response.write(main.toUtf8(), true);
}
