#ifndef MENU_MANAGER_H_
#define MENU_MANAGER_H_
#include <output.h>

class cMenu;
#include "menu.h"
#include "button.h"
#include "temp_probe.h"
#include "temp_control.h"

class cMenuManager: public cButtonListner
{
	uint16_t mLightTimeout;
	cOutput *mBacklight;
	cMenu *mCurrentMenu;
	cTempProbe **mTempProbes;
	cTempProbe *mSegmentProbe;
	cTempControl *mController;

	void updateTemperature(double temp);

public:
	cMenuManager(cOutput *backlight, cTempProbe **temperatureProbes, cTempControl *controller);
	virtual ~cMenuManager();

	void run();

	void pressed(cButtonListner::eButtons button);

	void setCurrentMenu(cMenu *menu);

	cTempProbe **getTemperaturePorts(){ return mTempProbes; };
	void setSegmentProbeIndex(uint8_t index);

	cTempControl *getController(){ return mController; };
};

#endif /* MENU_MANAGER_H_ */
