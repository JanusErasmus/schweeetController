#include <stdio.h>
#include <lcd.h>
#include <float.h>

#include <terminal.h>

#include "menu_select_probe.h"
#include "menu_stanby.h"

cMenuSelectProbe::cMenuSelectProbe(cMenuManager *manager) : cMenu(manager)
{
	mSelection = 0;

	lcd_clrscr();

	cTempProbe **ports = manager->getTemperaturePorts();
	if(!ports)
		return;

	uint8_t k = 0;
	cTempProbe *port = ports[k];
	char text[16];
	while(port)
	{
		sprintf(text,"%d %2.1f%cC", k + 1, port->getTemp(), 223);
		setCursor(k);
		lcd_puts(text);

		port = ports[++k];
	}
	lcd_gotoxy(0,0);
	lcd_command(LCD_DISP_ON_BLINK);
}

void cMenuSelectProbe::setCursor(uint8_t probe)
{
	uint8_t x = 0, y = 0;

	switch(probe)
	{
	case 1:
		y = 1;
		break;
	case 2:
		x = 9;
		break;
	case 3:
		y = 1;
		x = 9;
		break;
	default:
		break;
	}

	lcd_gotoxy(x,y);
}

void cMenuSelectProbe::handleButton(cButtonListner::eButtons button)
{
	switch(button)
	{
	case cButtonListner::MENU_LEFT:
	case cButtonListner::MENU_UP:
		if(mSelection)
			mSelection--;
		else
			mSelection = 3;
		break;

	case cButtonListner::MENU_RIGHT:
	case cButtonListner::MENU_DOWN:
		mSelection++;
		if(mSelection > 3)
			mSelection = 0;
		break;
	case cButtonListner::MENU_ENTER:
		mManager->setSegmentProbeIndex(mSelection);
		mManager->setCurrentMenu(new cMenuStanby(mManager));
		return;
	default:
		break;
	}

	setCursor(mSelection);
}

cMenuSelectProbe::~cMenuSelectProbe()
{
}

