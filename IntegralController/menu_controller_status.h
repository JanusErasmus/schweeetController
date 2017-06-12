#ifndef MENU_CONTROLLER_STATUS_H_
#define MENU_CONTROLLER_STATUS_H_
#include "menu.h"

class cMenuControllerStatus : public cMenu
{
public:
	cMenuControllerStatus(cMenuManager *manager);
	virtual ~cMenuControllerStatus();

	void handleButton(cButtonListner::eButtons button);
};

#endif /* MENU_CONTROLLER_STATUS_H_ */
