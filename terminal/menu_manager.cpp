#include <stdio.h>

#include <lcd.h>

#include "button.h"
#include "menu_manager.h"
#include "menu_stanby.h"

#define BACKLIGHT_TIMEOUT 100

cMenuManager::cMenuManager(cOutput *backlight, cTempControl *tempControl) : mBacklight(backlight), mTempControl(tempControl)
{
	mLightTimeout = BACKLIGHT_TIMEOUT;
	Buttons.setListener(this);
	mCurrentMenu = new cMenuStanby(this);
	updateTemperature();
}

void cMenuManager::updateTemperature()
{
	double temp = mTempControl->getTemp();
	char text[16];
	lcd_gotoxy(0,1);
	sprintf(text,"% 3.1f%cC", temp, 223);
	lcd_puts(text);
}

void cMenuManager::run()
{
	Buttons.run();

	if(mLightTimeout--)
		return;

	mLightTimeout = BACKLIGHT_TIMEOUT;
	mBacklight->reset();

	setCurrentMenu(new cMenuStanby(this));
	updateTemperature();
}

void cMenuManager::pressed(cButtonListner::eButtons button)
{
	mLightTimeout = BACKLIGHT_TIMEOUT;
	mBacklight->set();

	if(mCurrentMenu)
		mCurrentMenu->handleButton(button);
}

void cMenuManager::setCurrentMenu(cMenu *menu)
{
	if(mCurrentMenu)
		delete mCurrentMenu;

	mCurrentMenu = menu;
}

cMenuManager::~cMenuManager()
{
}

