#include <lcd.h>
#include <terminal.h>
#include <avr/pgmspace.h>

#include "menu_list.h"

#define DISPLAY_ROWS 2

cMenuList::cMenuList(cMenuManager *manager, const menuItems *items) : cMenu(manager), mItemList(items)
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
		lcd_puts(mItemList[startRow++].itemName);
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
		char item = mItemList[mItem].itemName[0];
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
	{
		cMenu *menu = mItemList[mItem].itemFuction(mManager);
		if(menu)
		{
			mManager->setCurrentMenu(menu);
			return;
		}
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

