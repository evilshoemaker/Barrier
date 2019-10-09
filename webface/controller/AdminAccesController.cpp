#include "AdminAccesController.h"

#include "webface/RequestMapper.h"

AdminAccesController::AdminAccesController()
{

}

bool AdminAccesController::isAdminAccess(HttpRequest &request, HttpResponse &response)
{
    HttpSession session = RequestMapper::sessionStore->getSession(request, response, true);

    return session.contains("type") && (session.get("type") == "all");
}
