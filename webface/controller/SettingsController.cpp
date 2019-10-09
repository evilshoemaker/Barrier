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

        QString adminLogin = request.getParameter("adminLogin");
        QString operatorLogin = request.getParameter("operatorLogin");

        if (adminLogin.isEmpty())
		{
            response.write(Util::makeJsonResult("error", "Не указан логин администратора"));
			return;
		}

        if (operatorLogin.isEmpty())
        {
            response.write(Util::makeJsonResult("error", "Не указан логин оператора"));
            return;
        }

        Settings::instance().setAdminLogin(adminLogin);
        Settings::instance().setOperatorLogin(operatorLogin);

		Settings::instance().save();
	}

	QByteArray language = request.getHeader("Accept-Language");
	response.setHeader("Content-Type", "text/html; charset=UTF-8");

	Template main = RequestMapper::templateCache->getTemplate("index", language);
	Template t = RequestMapper::templateCache->getTemplate(QStringLiteral("settings"), language);

    t.setVariable(QStringLiteral("adminLogin"), Settings::instance().adminLogin());
    t.setVariable(QStringLiteral("operatorLogin"), Settings::instance().operatorLogin());

	main.setVariable("isActiveSettings", " active");
	main.setVariable("title", "Settings");
	main.setVariable("content", "<div class=\"animated fadeIn\">" + t.toUtf8() + "</div>");

	response.write(main.toUtf8(), true);
}
