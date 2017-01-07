#ifndef HEATER_H_
#define HEATER_H_
#include <output.h>

#define DISABLED_TEMPERATURE -999

class cHeater
{
	cOutput *mHeaterRelay;
	float mTemperature;

	bool checkHeating(float temp);

public:
	cHeater(cOutput *heaterRelay);
	virtual ~cHeater();

	bool on(float temperature = DISABLED_TEMPERATURE);
	bool off(float temperature = DISABLED_TEMPERATURE);
};

#endif /* HEATER_H_ */
