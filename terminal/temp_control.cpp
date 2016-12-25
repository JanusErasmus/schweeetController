#include <util/delay.h>

#include <terminal.h>
#include "temp_control.h"
#include "nvm.h"

#define SAMPLE_PERIOD 10  //set to be 1 second
#define OFF_TIME 60

cTempControl::cTempControl(cOutput *relay, cLED *led, cTempProbe *probe) :
			mRelay(relay),
			mLED(led),
			mProbe(probe)

{
	mStarted = false;
	mStatus = STOPPED;
	mCount = SAMPLE_PERIOD;
	mSetPoint = eeprom_read_byte(ADDRES_SETPOINT);
}

void cTempControl::setHeater(bool state)
{
	if(state)
	{
		mRelay->set();
		mLED->green();
	}
	else
	{
		mRelay->reset();
		mLED->red();
	}
}

void cTempControl::start()
{
	mStarted = true;
	mStatus = DIFFERENTIAL;
}

void cTempControl::stop()
{
	mStarted = false;
	mStatus = STOPPED;
}

void cTempControl::doIntegralControl(float temp)
{
	if(mIntegral.onFlag)
	{
		if(mIntegral.ontime-- > 0)
			return;
		mIntegral.onFlag = false;

		mIntegral.offtime = OFF_TIME;

		setHeater(false);

	}
	else
	{
		if(mIntegral.offtime-- > 0)
			return;
		mIntegral.onFlag = true;

		//Hysteresis of 0.4C
		if((((float)mSetPoint - 0.2) >= temp) || (temp >= ((float)mSetPoint + 0.2)))
		{
			if(temp > (float)mSetPoint)
				mIntegral.setOnTime--;
			else
				mIntegral.setOnTime++;

			if(mIntegral.setOnTime < 0)
				mIntegral.setOnTime = 0;
		}

		mIntegral.ontime = mIntegral.setOnTime;

		printp("%03.1f - set %ds\n", temp, mIntegral.ontime);

		if(mIntegral.ontime)
			setHeater(true);
	}
}

void cTempControl::run()
{

	if(mCount--)
		return;
	mCount = SAMPLE_PERIOD;


	if(!mStarted)
	{
		mLED->off();
		mRelay->reset();
		return;
	}

	float temp = mProbe->getTemp();
	if(temp < (mSetPoint - 5))
	{
		mStatus = DIFFERENTIAL;
		setHeater(true);
	}
	else
	{
		mStatus = INTEGRAL;
		doIntegralControl(temp);
	}

}



cTempControl::~cTempControl()
{
}

cTempControl::sIntegralVariables::sIntegralVariables()
{
	offtime = 0;
	onFlag = true;
	ontime = 0;
	setOnTime = 0;
}

