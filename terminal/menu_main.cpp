#include <terminal.h>

#include "menu_main.h"
#include "menu_stanby.h"
#include "menu_select_probe.h"
#include "menu_controller_status.h"

cMenu *statusController(cMenuManager *manager)
{
	return new cMenuControllerStatus(manager);
}

cMenu *startController(cMenuManager *manager)
{
	cTempControl *control = manager->getController();
	if(control)
	{
		control->start();
	}
	return new cMenuControllerStatus(manager);
}

cMenu *stopController(cMenuManager *manager)
{
	cTempControl *control = manager->getController();
	if(control)
	{
		control->stop();
	}
	return new cMenuControllerStatus(manager);
}

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
		{"1. Status", statusController},
		{"2. Start", startController},
		{"3. Stop", stopController},
		{"4. Select probe", selectProbe},
		{"5. Setup", setupController},
		{"6. Back", goBack},
		{"\0", 0}
};

cMenuMain::cMenuMain(cMenuManager * manager) : cMenuList(manager, mainMenu)
{
}

cMenuMain::~cMenuMain()
{
}

