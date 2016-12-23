#ifndef TEMP_CONTROL_H_
#define TEMP_CONTROL_H_
#include <output.h>
#include <led.h>
#include "temp_probe.h"

class cTempControl
{
	struct sIntegralVariables
	{
		bool onFlag;
		int16_t offtime;
		int16_t ontime;
		int16_t setOnTime;

		sIntegralVariables();
	};

	bool mEnabled;
	cOutput *mRelay;
	cLED *mLED;
	cTempProbe *mProbe;
	uint16_t mCount;

	uint16_t mSetPoint;

	sIntegralVariables mIntegral;

	void setHeater(bool state);


	void doIntegralControl(float temp);

public:
	cTempControl(cOutput *relay, cLED *led, cTempProbe *probe);
	virtual ~cTempControl();

	void run();

	void enable();
	void disable();
};

#endif /* TEMP_CONTROL_H_ */
