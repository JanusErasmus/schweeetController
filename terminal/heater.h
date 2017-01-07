#ifndef HEATER_H_
#define HEATER_H_
#include <output.h>

#define DISABLED_TEMPERATURE -999

class cHeater
{
	cOutput *mHeaterRelay;
	float mTemperature;

public:
	cHeater(cOutput *heaterRelay);
	virtual ~cHeater();

	bool on(float temperature = DISABLED_TEMPERATURE);
	void off();
};

#endif /* HEATER_H_ */
