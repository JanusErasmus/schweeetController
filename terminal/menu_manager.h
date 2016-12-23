#ifndef MENU_MANAGER_H_
#define MENU_MANAGER_H_
#include <output.h>

class cMenu;
#include "menu.h"
#include "button.h"
#include "temp_probe.h"

class cMenuManager: public cButtonListner
{
	uint16_t mLightTimeout;
	cOutput *mBacklight;
	cMenu *mCurrentMenu;
	cTempProbe **mTempProbes;
	cTempProbe *mSegmentProbe;

	void updateTemperature(double temp);

public:
	cMenuManager(cOutput *backlight, cTempProbe **temperatureProbes);
	virtual ~cMenuManager();

	void run();

	void pressed(cButtonListner::eButtons button);

	void setCurrentMenu(cMenu *menu);

	cTempProbe **getTemperaturePorts(){ return mTempProbes; };
	void setSegmentProbeIndex(uint8_t index);
};

#endif /* MENU_MANAGER_H_ */
