#include <lcd.h>
#include <stdio.h>

#include "menu_controller_status.h"
#include "menu_stanby.h"

cMenuControllerStatus::cMenuControllerStatus(cMenuManager *manager) : cMenu(manager)
{
	lcd_clrscr();
	lcd_command(LCD_DISP_ON);
	lcd_gotoxy(5,0);

	cTempControl *control = manager->getController();
	if(control)
	{
		cTempControl::eControlStatus status = control->status();
		if(status == cTempControl::STOPPED)
		{
			lcd_putp("Stopped");
		}
		else
		{
			lcd_putp("Started");
			lcd_gotoxy(3,1);
			char setPoint[16];
			sprintf(setPoint, "Set @ %d%cC", control->setPoint(), 223);
			lcd_puts(setPoint);
		}
	}
	else
	{
		lcd_putp("No controller");
	}

}

void cMenuControllerStatus::handleButton(cButtonListner::eButtons button)
{
	cMenu *menu = new cMenuStanby(mManager);
	mManager->setCurrentMenu(menu);
}

cMenuControllerStatus::~cMenuControllerStatus()
{
}

