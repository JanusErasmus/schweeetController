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
		uint8_t setPoint = control->getSetPoint();
		char statusString[32];
		cTempControl::eControlStatus status = control->status();
		switch(status)
		{
		case cTempControl::HEATING:
			sprintf(statusString, "Heating to %d%cC", setPoint, 223);
			break;
		case cTempControl::IDLE:
			sprintf(statusString, "Control for %d%cC", setPoint, 223);
			break;
		case cTempControl::FAILURE:
			sprintf(statusString, "Heater failure");
			break;
		default:
			return;
		}
		lcd_puts(statusString);
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

