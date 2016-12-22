#ifndef MENU_LIST_H_
#define MENU_LIST_H_
#include "menu.h"

class cMenuList : public cMenu
{
	uint8_t mItem;
	uint8_t mRow;

	void fillDisplay();

public:
	cMenuList(cMenuManager *manager);
	virtual ~cMenuList();

	void handleButton(cButtonListner::eButtons button);
};

#endif /* MENU_LIST_H_ */
