#ifndef MENU_MANAGER_H_
#define MENU_MANAGER_H_
#include <output.h>


class cMenu;
#include "menu.h"
#include "button.h"
#include "temp_control.h"

class cMenuManager: public cButtonListner
{
	uint16_t mLightTimeout;
	cOutput *mBacklight;
	cMenu *mCurrentMenu;
	cTempControl *mTempControl;

	void updateTemperature();

public:
	cMenuManager(cOutput *backlight, cTempControl *tempControl);
	virtual ~cMenuManager();

	void run();

	void pressed(cButtonListner::eButtons button);

	void setCurrentMenu(cMenu *menu);
};

#endif /* MENU_MANAGER_H_ */
