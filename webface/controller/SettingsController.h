#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

class SettingsController : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(SettingsController)

public:
    SettingsController();
    void service(HttpRequest& request, HttpResponse& response);

signals:

public slots:
};

#endif // SETTINGSCONTROLLER_H
