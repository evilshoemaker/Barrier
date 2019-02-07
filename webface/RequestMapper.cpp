#include "RequestMapper.h"

#include "controller/LoginController.h"
#include "controller/SettingsController.h"
#include "controller/IndexController.h"
#include "controller/SystemInfoController.h"
#include "controller/MeasurementsController.h"
#include "controller/EventsSubscribeController.h"
#include "controller/SensorChartController.h"
#include "controller/CommandsController.h"
#include "controller/CcCommandsController.h"
#include "controller/ScCommandsController.h"
#include "controller/CalibrationCommandsController.h"
#include "controller/SensorTaringController.h"
#include "controller/CloudConnectTreeController.h"
#include "controller/CloudConnectInfoController.h"
#include "controller/SensorConnectInfoController.h"
#include "controller/RssiInfoTreeController.h"
#include "controller/RssiController.h"
#include "controller/ChangePasswordController.h"

#include "controller/energy/EnergyResourcesController.h"
#include "controller/energy/EnergyResourcesTreeController.h"
#include "controller/energy/EnergyResourcesTreeDataController.h"
#include "controller/energy/EnergyResourcesBalanceSettings.h"

#include "controller/energy/EnergyResourcesSchemController.h"
#include "controller/energy/EnergyRecourcesSchemDataController.h"

#include "controller/chart/CustomChartController.h"
#include "controller/chart/AddSensorToChartController.h"
#include "controller/chart/SensorCustomChartController.h"
#include "controller/chart/CustomChartSettingsController.h"


HttpSessionStore *RequestMapper::sessionStore = nullptr;
TemplateCache *RequestMapper::templateCache = nullptr;
StaticFileController *RequestMapper::staticFileController = nullptr;

RequestMapper::RequestMapper(QObject* parent)
    :HttpRequestHandler(parent)
{

}

RequestMapper::~RequestMapper()
{

}

void RequestMapper::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray path = request.getPath();

    if (path.startsWith("/css") || path.startsWith("/fonts")
            || path.startsWith("/js") || path.startsWith("/img")
            || path.startsWith("/amcharts") || path.startsWith("/chart"))
    {
        staticFileController->service(request, response);
        return;
    }


    QByteArray sessionId = sessionStore->getSessionId(request, response);
    if (sessionId.isEmpty() && path != "/login")
    {
        //qDebug("RequestMapper: redirect to login page");
        response.redirect("/login");
        return;
    }

    if (path == "/")
    {
		response.redirect("/measurements");
		return;
    }
    else if (path == "/login")
    {
        LoginController().service(request, response);
    }
    else if (path == "/logout")
    {
        HttpSession session = sessionStore->getSession(request, response);
        sessionStore->removeSession(session);

        response.redirect("/");
    }
    else if (path == "/settings")
    {
        SettingsController().service(request, response);
    }
    else if (path == "/settings/change-password")
    {
        ChangePasswordController().service(request, response);
    }
    else if (path == "/info")
    {
        SystemInfoController().service(request, response);
    }
    else if (path == "/measurements")
    {
        MeasurementsController().service(request, response);
    }
	else if (path == "/measurements/chart")
	{
		CustomChartController().service(request, response);
	}
	else if (path == "/commands")
	{
		CommandsController().service(request, response);
	}
	else if (path == "/commands/cc")
	{
		CcCommandsController().service(request, response);
	}
	else if (path == "/commands/sc")
	{
		ScCommandsController().service(request, response);
	}
	else if (path == "/commands/calibration")
	{
		CalibrationCommandsController().service(request, response);
	}
    else if (path == "/events/subscribe")
    {
        EventsSubscribeController().service(request, response);
    }
	else if (path == "/sensors/tree")
	{
		CloudConnectTreeController().service(request, response);
	}
    else if (path.startsWith("/sensors/chart"))
    {
        SensorChartController().service(request, response);
    }
	else if (path == "/sensors/custom_chart/add_sensor")
	{
		AddSensorToChartController().service(request, response);
	}
	else if (path.startsWith("/sensors/custom-chart/data"))
	{
		SensorCustomChartController().service(request, response);
	}
    else if (path.startsWith("/sensors/custom-chart/settings"))
    {
        CustomChartSettingsController().service(request, response);
    }
    else if (path == "/sensors/cloudConnectInfo")
    {
        CloudConnectInfoController().service(request, response);
    }
    else if (path == "/sensors/sensorConnectInfo")
    {
        SensorConnectInfoController().service(request, response);
    }
    else if (path == "/sensors/sensorTaring")
    {
        SensorTaringController().service(request, response);
    }
	else if (path == "/network")
	{
		RssiController().service(request, response);
	}
	else if (path == "/network/tree")
	{
		RssiInfoTreeController().service(request, response);
	}

	else if (path == "/energy")
	{
		EnergyResourcesController().service(request, response);
	}
	else if (path == "/energy/tree")
	{
		EnergyResourcesTreeController().service(request, response);
	}
    else if (path == "/energy/tree/data")
	{
		EnergyResourcesTreeDataController().service(request, response);
	}
    else if (path.startsWith("/energy/balance-settings"))
	{
		EnergyResourcesBalanceSettings().service(request, response);
    }
    else if (path == "/energy/schem/settings")
    {
        EnergyResourcesSchemController().service(request, response);
    }
	else if (path == "/energy/schem/list")
	{
		EnergyRecourcesSchemDataController().service(request, response);
	}

    else
    {
        response.setStatus(404, "Page not found");
    }
}
