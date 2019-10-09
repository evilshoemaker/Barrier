#include "ChangePasswordController.h"

#include "core/Util.h"
#include "core/Settings.h"

ChangePasswordController::ChangePasswordController()
{

}

void ChangePasswordController::service(HttpRequest &request, HttpResponse &response)
{
    QString type = request.getParameter("type");
	QString oldPassword = request.getParameter("oldPassword");
	QString password = request.getParameter("password");
	QString repeatPassword = request.getParameter("repeatPassword");

    if (type != "admin" && type != "operator")
    {
        response.write("{\"result\":\"error\", \"message\":\"Ошибка запроса\"}");
        return;
    }

    QString realPassword = type == "admin"
            ? Settings::instance().adminPassword()
            : Settings::instance().operatorPassword();

    if (oldPassword.isEmpty() || Util::sha1(oldPassword) != realPassword)
	{
		response.write("{\"result\":\"error\", \"message\":\"Не верный пароль\"}");
		return;
	}

	if (password != repeatPassword)
	{
		response.write("{\"result\":\"error\", \"message\":\"Пароли не совпадают\"}");
		return;
	}

    if (type == "admin")
    {
        Settings::instance().setAdminPassword(Util::sha1(password));
    }
    else
    {
        Settings::instance().setOperatorPassword(Util::sha1(password));
    }

	response.write("{\"result\":\"success\"}");
}
