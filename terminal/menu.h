#ifndef MENU_H_
#define MENU_H_
#include "button.h"

class cMenuManager;

#include "menu_manager.h"

class cMenu
{
protected:
	cMenuManager *mManager;

public:
	cMenu(cMenuManager *manager);
	virtual ~cMenu();

	virtual void handleButton(cButtonListner::eButtons button) = 0;
};

#endif /* MENU_H_ */
