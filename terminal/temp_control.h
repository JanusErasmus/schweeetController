#ifndef TEMP_CONTROL_H_
#define TEMP_CONTROL_H_
#include <output.h>
#include <led.h>
#include <analog.h>

class cTempControl
{
	cOutput *mRelay;
	cLED *mLED;
	cAnalog *mAnalog;

public:
	cTempControl(cOutput *relay, cLED *led, cAnalog *analog);
	virtual ~cTempControl();

	float temp();
};

#endif /* TEMP_CONTROL_H_ */
