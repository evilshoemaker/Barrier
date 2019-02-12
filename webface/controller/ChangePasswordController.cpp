#include "ChangePasswordController.h"

#include "core/Util.h"
#include "core/Settings.h"

ChangePasswordController::ChangePasswordController()
{

}

void ChangePasswordController::service(HttpRequest &request, HttpResponse &response)
{
	QString oldPassword = request.getParameter("oldPassword");
	QString password = request.getParameter("password");
	QString repeatPassword = request.getParameter("repeatPassword");

	if (oldPassword.isEmpty() || Util::sha1(oldPassword) != Settings::instance().password())
	{
		response.write("{\"result\":\"error\", \"message\":\"Не верный пароль\"}");
		return;
	}

	if (password != repeatPassword)
	{
		response.write("{\"result\":\"error\", \"message\":\"Пароли не совпадают\"}");
		return;
	}

	Settings::instance().setPassword(Util::sha1(password));
	response.write("{\"result\":\"success\"}");
}
