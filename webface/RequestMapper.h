#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include "httprequesthandler.h"
#include "httpsessionstore.h"
#include "templatecache.h"
#include "staticfilecontroller.h"

class RequestMapper : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(RequestMapper)

public:
    static HttpSessionStore *sessionStore;
    static TemplateCache *templateCache;
    static StaticFileController *staticFileController;

    RequestMapper(QObject* parent = nullptr);
    ~RequestMapper();

    void service(HttpRequest& request, HttpResponse& response);

private:
    bool isAdminAccess(HttpRequest &request, HttpResponse &response);
};

#endif // REQUESTMAPPER_H
