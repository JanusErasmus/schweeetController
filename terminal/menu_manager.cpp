#include <stdio.h>

#include <lcd.h>

#include "button.h"
#include "seven_segment.h"
#include "menu_manager.h"
#include "menu_stanby.h"

#define BACKLIGHT_TIMEOUT 100

cMenuManager::cMenuManager(cOutput *backlight, cTempProbe **temperatureProbes) : mBacklight(backlight), mTempProbes(temperatureProbes)
{
	mSegmentProbe = mTempProbes[0];
	mLightTimeout = BACKLIGHT_TIMEOUT;
	Buttons.setListener(this);
	mCurrentMenu = new cMenuStanby(this);

	if(mSegmentProbe)
	{
		double temp = mSegmentProbe->getTemp();
		SevenSegment.setNumber(temp);
	}
}

void cMenuManager::updateTemperature(double temp)
{
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


	if(mSegmentProbe)
	{
		double temp = mSegmentProbe->getTemp();
		SevenSegment.setNumber(temp);
	}

	setCurrentMenu(new cMenuStanby(this));
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

void cMenuManager::setSegmentProbeIndex(uint8_t index)
{
	if(mTempProbes[index])
	{
		mSegmentProbe = mTempProbes[index];
		double temp = mSegmentProbe->getTemp();
		SevenSegment.setNumber(temp);
	}
}

cMenuManager::~cMenuManager()
{
}

