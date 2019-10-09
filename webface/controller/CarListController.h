#ifndef CARLISTCONTROLLER_H
#define CARLISTCONTROLLER_H

#include "AdminAccesController.h"

class CarListController : public AdminAccesController
{
	Q_OBJECT
	Q_DISABLE_COPY(CarListController)

public:
	CarListController();
	void service(HttpRequest& request, HttpResponse& response);

};

#endif // CARLISTCONTROLLER_H
