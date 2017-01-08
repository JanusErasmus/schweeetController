#ifndef TEMP_CONTROL_H_
#define TEMP_CONTROL_H_
#include <led.h>

#include "temp_probe.h"
#include "heater.h"

class cTempControl
{
public :
	enum eControlStatus
	{
		STOPPED,
		HEATING,
		IDLE,
		COOLING,
		FAILURE
	};

private:
	struct sIntegralVariables
	{
		bool onFlag;
		int16_t offtime;
		int16_t ontime;
		int16_t setOnTime;

		sIntegralVariables();
		void reset();
	};

	eControlStatus mStatus;

	cHeater *mHeater;
	bool mLEDflag;
	cLED *mLED;
	cTempProbe *mProbe;
	uint16_t mCount;

	uint16_t mSetPoint;

	sIntegralVariables mIntegral;

	void setHeater(bool state);


	void doIntegralControl(float temp);

public:
	cTempControl(cHeater *heater, cLED *led, cTempProbe *probe);
	virtual ~cTempControl();

	void run();

	void start();
	void stop();

	eControlStatus status(){ return mStatus; };
	uint16_t getSetPoint(){ return mSetPoint; };
	void setSetPoint(uint16_t setPoint){ mSetPoint = setPoint; };
};

#endif /* TEMP_CONTROL_H_ */
