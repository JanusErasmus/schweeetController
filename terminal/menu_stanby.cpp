#include <util/delay.h>

#include <lcd.h>
#include <terminal.h>

#include "menu_stanby.h"
#include "menu_main.h"

cMenuStanby::cMenuStanby(cMenuManager *manager) : cMenu(manager)
{
	lcd_clrscr();
	lcd_command(LCD_DISP_ON);
	lcd_gotoxy(5,0);
	lcd_putp("Shweeet");

	cTempControl *control = manager->getController();
	if(control)
	{
		lcd_gotoxy(0,1);
		char setPoint[16];
		cTempControl::eControlStatus status = control->status();
		switch(status)
		{
		case cTempControl::STOPPED:
			return;
		case cTempControl::DIFFERENTIAL:
			sprintf(setPoint, "Heating to %d%cC", control->getSetPoint(), 223);
			break;
		case cTempControl::INTEGRAL:
			sprintf(setPoint, "Control for %d%cC", control->getSetPoint(), 223);
			break;
		}
		lcd_puts(setPoint);
	}
}

void cMenuStanby::handleButton(cButtonListner::eButtons button)
{
	cMenu *menu = new cMenuMain(mManager);
	mManager->setCurrentMenu(menu);
}

cMenuStanby::~cMenuStanby()
{
}

