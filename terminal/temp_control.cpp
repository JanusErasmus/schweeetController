#include "temp_control.h"

cTempControl::cTempControl(cOutput *relay, cLED *led, cAnalog *analog) :
			mRelay(relay),
			mLED(led),
			mAnalog(analog)

{
}

float cTempControl::temp()
{
	double sample = mAnalog->sample();
	double temp = 500 * (sample/1024.0) - 273.0;
	return temp;
}

cTempControl::~cTempControl()
{
}

