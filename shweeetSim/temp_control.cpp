
#include "temp_control.h"
#include "nvm.h"

#define SAMPLE_PERIOD 10  //set to be 1 second
#define HEATER_OFF_TIME 60

#define FREEZER_OFF_TIME 600
#define FREEZER_MIN_TIME 300
#define FREEZER_INC_TIME 60

cTempControl::cTempControl(cHeater *heater, cLED *heaterled, cOutput *freezerRelay, cLED *freezerled, cTempProbe *probe) :
			mHeater(heater),
			mHeaterLED(heaterled),
			mFreezerRelay(freezerRelay),
			mFreezerLED(freezerled),
			mProbe(probe)

{
	mLEDflag = false;
	mStatus = STOPPED;
	mCount = 3;
	mSetPoint = eeprom_read_byte(ADDRES_SETPOINT);

    mFreezerParam.onFlag = false;

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
		mHeater->on();
        mFreezerRelay->reset();
        qDebug() << "Freezer OFF";
		mStatus = HEATING;
	}
	else
	{
		mHeater->off();

		if(mStatus != COOLING)
			mStatus = IDLE;
	}

	if(!mHeater->OK())
	{
		mStatus = FAILURE;
	}
}

void cTempControl::setFreezer(bool state)
{
	if(state)
	{
		mFreezerRelay->set();
        qDebug() << "Freezer ON";
        mHeater->reset();
        mHeater->off();
		mStatus = COOLING;
	}
	else
	{
		mFreezerRelay->reset();
        qDebug() << "Freezer OFF";

		if(mStatus != HEATING)
			mStatus = IDLE;
	}
}

void cTempControl::start()
{
	eeprom_write_byte(ADDRES_CONTROLLING, true);
	mStatus = IDLE;
	setHeater(false);
	setFreezer(false);
}

void cTempControl::stop()
{
	eeprom_write_byte(ADDRES_CONTROLLING, false);
	mHeater->reset();
	mStatus = STOPPED;

    mHeaterParam.reset();
    mFreezerParam.reset();
}

void cTempControl::doIntegralHeating(float temp)
{
    if(mHeaterParam.onFlag)
	{
        if(mHeaterParam.ontime-- > 0)
			return;
        mHeaterParam.onFlag = false;

        mHeaterParam.offtime = HEATER_OFF_TIME;

		setHeater(false);
	}
	else
	{
        if(mHeaterParam.offtime-- > 0)
			return;
        mHeaterParam.onFlag = true;

		//Hysteresis of 0.4C
		if((((float)mSetPoint - 0.2) >= temp) || (temp >= ((float)mSetPoint + 0.2)))
		{
			if(temp > (float)mSetPoint)
                mHeaterParam.setOnTime--;
			else
                mHeaterParam.setOnTime++;

            if(mHeaterParam.setOnTime < 0)
                mHeaterParam.setOnTime = 0;
		}

        mHeaterParam.ontime = mHeaterParam.setOnTime;

        printp("Heater %03.1f - set %ds", temp, mHeaterParam.ontime);

        if(mHeaterParam.ontime)
		{
			setHeater(true);
		}
	}
}

void cTempControl::doIntegralCooling(float temp)
{
    if(mFreezerParam.onFlag)
	{
        if(mFreezerParam.ontime-- > 0)
			return;
        mFreezerParam.onFlag = false;

        mFreezerParam.offtime = FREEZER_OFF_TIME;

		setFreezer(false);
	}
	else
	{
        if(mFreezerParam.offtime-- > 0)
			return;
        mFreezerParam.onFlag = true;

		//Hysteresis of 2C
		if((((float)mSetPoint - 1) <= temp) || (temp <= ((float)mSetPoint + 1)))
		{
			if(temp < (float)mSetPoint)
            {	mFreezerParam.setOnTime -= 60;

            if(mFreezerParam.setOnTime < FREEZER_MIN_TIME)
                mFreezerParam.setOnTime = 0;
            }
			else
			{
				//start with minimim of 10m on
                if(mFreezerParam.setOnTime == 0)
                    mFreezerParam.setOnTime = FREEZER_MIN_TIME;

                mFreezerParam.setOnTime += FREEZER_INC_TIME;
			}

            if(mFreezerParam.setOnTime < 0)
                mFreezerParam.setOnTime = 0;
		}

        mFreezerParam.ontime = mFreezerParam.setOnTime;

        printp("Freezer %03.1f - set %ds", temp, mFreezerParam.ontime);

        if(mFreezerParam.ontime)
		{
			setFreezer(true);
		}
	}
}

void cTempControl::run()
{
	switch(mStatus)
	{
	case STOPPED:
	{
		mHeaterLED->off();
	}
	return;
	case HEATING:
	{
		if(mLEDflag)
		{
			mLEDflag = false;
			mHeaterLED->off();
		}
		else
		{
			mLEDflag = true;
			mHeaterLED->green();
		}
	}
	break;
	case IDLE:
	{
		mHeaterLED->green();
		mFreezerLED->green();
	}
	break;
	case COOLING:
		if(mLEDflag)
		{
			mLEDflag = false;
			mFreezerLED->off();
		}
		else
		{
			mLEDflag = true;
			mFreezerLED->green();
		}
		break;
	case FAILURE:
	{
		if(mLEDflag)
		{
			mLEDflag = false;
			mHeaterLED->off();
		}
		else
		{
			mLEDflag = true;
			mHeaterLED->red();
		}
	}
	break;
	}

	if(mCount--)
		return;
	mCount = SAMPLE_PERIOD;

    mDifferential = false;

	float temp = mProbe->getTemp();
	if(temp < ((float)mSetPoint - 5.0))
	{
		setHeater(true);
        mDifferential = true;
	}

	if(temp > ((float)mSetPoint + 3.0))
	{
		setFreezer(true);
        mDifferential = true;
	}

    if(mDifferential)
		return;


	//do NOT cool while we are still heating
    if(mHeaterParam.setOnTime <= 0)
		doIntegralCooling(temp);

	//do NOT heat while we are still cooling
    if(mFreezerParam.setOnTime <= 0)
		doIntegralHeating(temp);


}



cTempControl::~cTempControl()
{
}



