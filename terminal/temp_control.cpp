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
	mLEDflag = false;
	mStatus = STOPPED;
	mCount = SAMPLE_PERIOD;
	mSetPoint = eeprom_read_byte(ADDRES_SETPOINT);


	bool started = eeprom_read_byte(ADDRES_CONTROLLING);
	if(started)
	{
		mStatus = IDLE;
	}
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
		mLED->off();
	}
}

void cTempControl::start()
{
	eeprom_write_byte(ADDRES_CONTROLLING, true);
	mStatus = IDLE;
	setHeater(false);
}

void cTempControl::stop()
{
	eeprom_write_byte(ADDRES_CONTROLLING, false);
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

		mStatus = IDLE;
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
		{
			mStatus = HEATING;
			setHeater(true);
		}
	}
}

void cTempControl::run()
{
	switch(mStatus)
	{
	case STOPPED:
	{
		mLED->off();
		mRelay->reset();
	}
	return;
	case HEATING:
	{
		if(mLEDflag)
		{
			mLEDflag = false;
			mLED->off();
		}
		else
		{
			mLEDflag = true;
			mLED->green();
		}
	}
	break;
	case IDLE:
	{
		mLED->green();
		mRelay->reset();
	}
	break;
	case COOLING:
		break;
	}

	if(mCount--)
		return;
	mCount = SAMPLE_PERIOD;

	float temp = mProbe->getTemp();
	if(temp < ((float)mSetPoint - 5.0))
	{
		mStatus = HEATING;
		setHeater(true);
	}
	else
	{
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

