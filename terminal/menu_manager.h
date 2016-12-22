#ifndef MENU_MANAGER_H_
#define MENU_MANAGER_H_
#include <output.h>

class cMenu;
#include "menu.h"
#include "button.h"

class cMenuManager: public cButtonListner
{
	uint16_t mLightTimeout;
	cOutput *mBacklight;
	cMenu *mCurrentMenu;

	void updateTemperature(double temp);

public:
	cMenuManager(cOutput *backlight);
	virtual ~cMenuManager();

	void run();

	void pressed(cButtonListner::eButtons button);

	void setCurrentMenu(cMenu *menu);
};

#endif /* MENU_MANAGER_H_ */
