#include <lcd.h>
#include <stdio.h>

#include "nvm.h"
#include "menu_setup_control.h"
#include "menu_stanby.h"

cMenuSetupControl::cMenuSetupControl(cMenuManager *manager) : cMenu(manager)
{
	mTemperature = eeprom_read_byte(ADDRES_SETPOINT);
	if(mTemperature == 0xFF)
		mTemperature = 0;


	lcd_clrscr();
	lcd_home();
	lcd_putp("Set temperature:");
	lcd_command(LCD_DISP_ON_CURSOR_BLINK);
	updateDisplay();
}

void cMenuSetupControl::updateDisplay()
{
	lcd_gotoxy(0,1);
	char temp[16];
	sprintf(temp, "%3d%cC", mTemperature ,223);
	lcd_puts(temp);
}

void cMenuSetupControl::handleButton(cButtonListner::eButtons button)
{
	switch(button)
	{
	case cButtonListner::MENU_LEFT:
	case cButtonListner::MENU_UP:
		mTemperature++;
		break;

	case cButtonListner::MENU_RIGHT:
	case cButtonListner::MENU_DOWN:
		mTemperature--;
		break;

	case cButtonListner::MENU_ENTER:
		eeprom_write_byte(ADDRES_SETPOINT, mTemperature);
		mManager->getController()->setSetPoint(mTemperature);
		mManager->setCurrentMenu(new cMenuStanby(mManager));
		return;
	default:
		break;
	}

	updateDisplay();
}

cMenuSetupControl::~cMenuSetupControl()
{
}

