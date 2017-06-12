#ifndef HEATER_H_
#define HEATER_H_
#include <output.h>

#include "temp_probe.h"

class cHeater
{
	cTempProbe *mProbe;
	cOutput *mHeaterRelay;
	float mTemperature;

	int16_t mSampleCount;
	bool mOK;

public:
	cHeater(cOutput *heaterRelay, cTempProbe *probe);
	virtual ~cHeater();

	void run();
	void on();
	void off();
	void reset();

	bool OK(){ return mOK; };
};

#endif /* HEATER_H_ */
