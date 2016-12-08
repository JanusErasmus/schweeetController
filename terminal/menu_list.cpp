#include <lcd.h>
#include <terminal.h>

#include "menu_list.h"

cMenuList::cMenuList(cMenuManager *manager) : cMenu(manager)
{
	lcd_clrscr();
	lcd_home();
	lcd_putp("Set temp");
}

void cMenuList::handleButton(cButtonListner::eButtons button)
{
	printp("list btn\n");
}

cMenuList::~cMenuList()
{
}

