#include <terminal.h>
#include "menu_main.h"
#include "menu_stanby.h"


cMenu *setLED(cMenuManager *manager)
{
	printp("Set led\n");
	return 0;
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
		{"1. Set LED", setLED},
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

