#ifndef MENU_SETUP_CONTROL_H_
#define MENU_SETUP_CONTROL_H_
#include "menu.h"

class cMenuSetupControl : public cMenu
{
	uint8_t mTemperature;

	void updateDisplay();

public:
	cMenuSetupControl(cMenuManager *manager);
	virtual ~cMenuSetupControl();

	void handleButton(cButtonListner::eButtons button);
};

#endif /* MENU_SETUP_CONTROL_H_ */
