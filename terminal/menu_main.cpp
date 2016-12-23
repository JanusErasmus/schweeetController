#include <terminal.h>

#include "menu_main.h"
#include "menu_stanby.h"
#include "menu_select_probe.h"


cMenu *selectProbe(cMenuManager *manager)
{
	return new cMenuSelectProbe(manager);
}

cMenu *setupController(cMenuManager *manager)
{
	printp("Setup\n");
	return 0;
}

cMenu *goBack(cMenuManager *manager)
{
	return new cMenuStanby(manager);
}


const cMenuList::menuItems mainMenu[] =
{
		{"1. Select probe", selectProbe},
		{"2. Setup", setupController},
		{"3. Back", goBack},
		{"\0", 0}
};

cMenuMain::cMenuMain(cMenuManager * manager) : cMenuList(manager, mainMenu)
{
}

cMenuMain::~cMenuMain()
{
}

