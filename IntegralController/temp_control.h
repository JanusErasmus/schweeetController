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
	cLED *mHeaterLED;
	cOutput *mFreezerRelay;
	cLED *mFreezerLED;
	bool mLEDflag;
	cTempProbe *mProbe;
	uint16_t mCount;

	uint16_t mSetPoint;

	sIntegralVariables mHeaterIntegral;
	sIntegralVariables mFreezerIntegral;

	void setHeater(bool state);
	void setFreezer(bool state);


	void doIntegralHeating(float temp);
	void doIntegralCooling(float temp);

public:
	cTempControl(cHeater *heater, cLED *heaterled, cOutput *freezerRelay, cLED *freezerled, cTempProbe *probe);
	virtual ~cTempControl();

	void run();

	void start();
	void stop();

	eControlStatus status(){ return mStatus; };
	uint16_t getSetPoint(){ return mSetPoint; };
	void setSetPoint(uint16_t setPoint){ mSetPoint = setPoint; };
};

#endif /* TEMP_CONTROL_H_ */
