#include <lcd.h>
#include <terminal.h>
#include <avr/pgmspace.h>

#include "menu_list.h"
#include "menu_stanby.h"

#define DISPLAY_ROWS 2

static const char menuList[][16] PROGMEM =
{
		{"1. Set LED"},
		{"2. Setup"},
		{"3. Start"},
		{"4. Stop"},
		{"5. Back"},
		{"\0"}
};

cMenuList::cMenuList(cMenuManager *manager) : cMenu(manager)
{
	mItem = 0;
	mRow = 0;
	fillDisplay();

	lcd_command(LCD_DISP_ON_CURSOR_BLINK);
}

void  cMenuList::fillDisplay()
{
	lcd_clrscr();

	uint8_t startRow = 0;


	if(mItem >= DISPLAY_ROWS)
	{
		startRow = mItem - DISPLAY_ROWS + 1;
	}

	for(uint8_t k = 0; k < DISPLAY_ROWS; k++)
	{
		lcd_gotoxy(0,k);
		lcd_puts_p(menuList[startRow++]);
	}

	lcd_gotoxy(0,mRow);

}

void cMenuList::handleButton(cButtonListner::eButtons button)
{
	switch(button)
	{
	case cButtonListner::MENU_DOWN:
	{
		if(++mRow > DISPLAY_ROWS)
			mRow = DISPLAY_ROWS;

		mItem++;
		char item = pgm_read_byte(menuList[mItem]);
		if(item == '\0')
			mItem--;
	}
		break;
	case cButtonListner::MENU_UP:
		if(mRow > 0)
			mRow--;

		if(mItem)
			mItem--;

		break;
	case cButtonListner::MENU_ENTER:
		switch(mItem)
		{
		case 0:
			printp("Set led\n");
			break;
		case 1:
			printp("Setup\n");
			break;
		case 2:
			printp("Start\n");
			break;
		case 3:
			printp("Stop\n");
			break;
		case 4:
		default:
			mManager->setCurrentMenu(new cMenuStanby(mManager));
			return;
		}
		break;
	default:
		break;
	}

	fillDisplay();
}

cMenuList::~cMenuList()
{
}

