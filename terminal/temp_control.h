#ifndef TEMP_CONTROL_H_
#define TEMP_CONTROL_H_
#include <output.h>
#include <led.h>
#include "temp_probe.h"

class cTempControl
{
public :
	enum eControlStatus
	{
		STOPPED,
		DIFFERENTIAL,
		INTEGRAL
	};

private:
	struct sIntegralVariables
	{
		bool onFlag;
		int16_t offtime;
		int16_t ontime;
		int16_t setOnTime;

		sIntegralVariables();
	};

	eControlStatus mStatus;

	bool mStarted;
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

	void start();
	void stop();

	eControlStatus status(){ return mStatus; };
	uint16_t setPoint(){ return mSetPoint; };
};

#endif /* TEMP_CONTROL_H_ */
