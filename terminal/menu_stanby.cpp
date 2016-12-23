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
}

void cMenuStanby::handleButton(cButtonListner::eButtons button)
{
	cMenu *menu = new cMenuMain(mManager);
	mManager->setCurrentMenu(menu);
}

cMenuStanby::~cMenuStanby()
{
}

