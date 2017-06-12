#ifndef MENU_MAIN_H_
#define MENU_MAIN_H_
#include "menu_list.h"

class cMenuMain  : public cMenuList
{
public:
	cMenuMain(cMenuManager * manager);
	virtual ~cMenuMain();
};

#endif /* MENU_MAIN_H_ */
