#ifndef MENU_STANBY_H_
#define MENU_STANBY_H_

#include "menu.h"

class cMenuStanby : public cMenu
{
public:
	cMenuStanby(cMenuManager *manager);
	virtual ~cMenuStanby();

	void handleButton(cButtonListner::eButtons button);
};

#endif /* MENU_STANBY_H_ */
