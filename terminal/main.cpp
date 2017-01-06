#include <stdio.h>
#include <float.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

#include <terminal.h>
#include <led.h>
#include <heartbeat.h>
#include <analog_sampler.h>
#include <lcd.h>

#include "temp_control.h"
#include "menu_manager.h"
#include "seven_segment.h"

void watchdogReset()
{
  __asm__ __volatile__ ( "wdr\n" );
}

cOutput backlight(PORT_PG(2));
void backLight(uint8_t argc, char **argv)
{
	if(argc > 1)
		backlight.set();
	else
		backlight.reset();
}
extern const dbg_entry backlightEntry = {backLight, "light"};

cOutput relay1(PORT_PF(0));
cOutput relay2(PORT_PF(1));
cOutput relay3(PORT_PF(2));
cOutput relay4(PORT_PF(3));
void debugOut(uint8_t argc, char **argv)
{
	cOutput *relay = 0;
	if(argc > 1)
	{
		uint8_t num = atoi(argv[1]);
		switch(num)
		{
		case 1:
			relay = &relay1;
			break;
		case 2:
			relay = &relay2;
			break;
		case 3:
			relay = &relay3;
			break;
		case 4:
			relay = &relay4;
			break;
		default:
			return;
		}

		if(argc > 2)
		{
			bool state = atoi(argv[2]);
			printp("%s - ", state?"set":"reset", num);
			if(state)
				relay->set();
			else
				relay->reset();
		}

		bool state = relay->get();
		printp("RL%d: %s\n", num, state?"ON":"OFF");
	}
	else
	{
		printp("RL1: %s\n", relay1.get()?"ON":"OFF");
		printp("RL2: %s\n", relay2.get()?"ON":"OFF");
		printp("RL3: %s\n", relay3.get()?"ON":"OFF");
		printp("RL4: %s\n", relay4.get()?"ON":"OFF");
	}
}
extern const dbg_entry outputEntry = {debugOut, "o"};


cAnalog analogIn1(4);
cAnalog analogIn2(5);
cAnalog analogIn3(6);
cAnalog analogIn4(7);

void measureTemp(uint8_t argc, char **argv)
{
	printp("Measuring temp:\n");

	double sample = analogIn1.lastSample();
	double temp = 500 * (sample/1024.0) - 273.0;
	printf(" 1: %.1f\n", temp);

	sample = analogIn2.lastSample();
	temp = 500 * (sample/1024.0) - 273.0;
	printf(" 2: %.1f\n", temp);

	sample = analogIn3.lastSample();
	temp = 5 * (sample/1024.0);
	printf(" 3: %.1f\n", temp);

	sample = analogIn4.lastSample();
	temp = 5 * (sample/1024.0);
	printf(" 4: %.1f\n", temp);
}

extern const dbg_entry mainEntry = {measureTemp, "temp"};


/* main program starts here */
int main(void)
{
	//WDTCSR = _BV(WDCE) | _BV(WDE);
	//WDTCSR = (_BV(WDP2) | _BV(WDP1) | _BV(WDP0) | _BV(WDE));

	sei();

	cOutput statusRed(0x60);
	cOutput statusGreen(0x61);
	cLED status(&statusRed, &statusGreen);

	cOutput led1red(0x20);
	cOutput led1green(0x21);
	cLED led1(&led1red, &led1green);

	cOutput led2red(0x22);
	cOutput led2green(0x23);
	cLED led2(&led2red, &led2green);

	cOutput led3red(0x24);
	cOutput led3green(0x25);
	cLED led3(&led3red, &led3green);

	cOutput led4red(0x26);
	cOutput led4green(0x27);
	cLED led4(&led4red, &led4green);

	cHeartbeat heartbeat(&status);

	cTempProbe probe1(cTempProbe::LM335, &analogIn1);
	cTempProbe probe2(cTempProbe::LM335, &analogIn2);
	cTempProbe probe3(cTempProbe::PT100, &analogIn3);
	cTempProbe probe4(cTempProbe::PT100, &analogIn4);

	cTempControl tempControl(&relay1, &led1, &probe1);

	lcd_init(LCD_DISP_ON);
	lcd_clrscr();

	cAnalog *analogList[] =
	{
			&analogIn1,
			&analogIn2,
			&analogIn3,
			&analogIn4,
			0
	};
	cAnalogSampler analogSampler(analogList);

	cTempProbe *probeList[] =
	{
			&probe1,
			&probe2,
			&probe3,
			&probe4,
			0
	};
	cMenuManager menuManager(&backlight, probeList, &tempControl);

	cSevenSegment segment;

	while(1)
	{
		watchdogReset();

		Terminal.run();
		heartbeat.run();
		menuManager.run();
		analogSampler.run();
		tempControl.run();

		_delay_ms(100);
	}

	return 0;
}

