#ifndef MENU_LIST_H_
#define MENU_LIST_H_
#include "menu.h"

class cMenuList : public cMenu
{
public:
	struct menuItems
	{
		const char *itemName;
		cMenu *(*itemFuction)(cMenuManager *manager);
	};

private:
	uint8_t mItem;
	uint8_t mRow;
	const menuItems *mItemList;

	void fillDisplay();

public:
	cMenuList(cMenuManager *manager, const menuItems *items);
	virtual ~cMenuList();

	void handleButton(cButtonListner::eButtons button);
};

#endif /* MENU_LIST_H_ */
