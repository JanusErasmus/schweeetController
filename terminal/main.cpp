#include <stdio.h>
#include <float.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "terminal.h"
#include "led.h"
#include "heartbeat.h"
#include "input.h"
#include "analog.h"
#include "button.h"
#include "lcd.h"

void watchdogReset() {
  __asm__ __volatile__ (
    "wdr\n"
  );
}

void backLight(uint8_t argc, char **argv)
{
//	if(argc > 1)
//		LCDsetBacklight(1);
//	else
//		LCDsetBacklight(0);
}

extern const dbg_entry backlightEntry = {backLight, "light"};

void post(cLED **leds, cOutput **outputs)
{
	uint8_t k = 0;
	if(leds)
	{
		cLED *led = leds[k];
		while(led)
		{
			led->red();
			led = leds[++k];
		}
		_delay_ms(200);
		k = 0;
		led = leds[k];
		while(led)
		{
			led->green();
			led = leds[++k];
		}
		_delay_ms(200);
		k = 0;
		led = leds[k];
		while(led)
		{
			led->off();
			led = leds[++k];
		}
	}

	k = 0;
	if(outputs)
	{
		cOutput *rl = outputs[k];
		while(rl)
		{
			rl->set();
			_delay_ms(200);
			rl->reset();
			_delay_ms(200);
			rl = outputs[++k];
		}
	}
}

cAnalog in1(4);
cAnalog in2(5);
cAnalog in3(6);
cAnalog in4(7);

void measureTemp(uint8_t argc, char **argv)
{
	printp("Measuring temp:\n");

	double sample = in1.sample();
	double temp = 500 * (sample/1024.0) - 273.0;
	printf(" 1: %.1f\n", temp);

	sample = in2.sample();
	temp = 500 * (sample/1024.0) - 273.0;
	printf(" 2: %.1f\n", temp);

	sample = in3.sample();
	temp = 5 * (sample/1024.0);
	printf(" 3: %.1f\n", temp);

	sample = in4.sample();
	temp = 5 * (sample/1024.0);
	printf(" 4: %.1f\n", temp);
}

extern const dbg_entry mainEntry = {measureTemp, "temp"};


void loading()
{
	static uint8_t cnt = 0;
	static bool upDown = true;
	static uint8_t progress = 0;

//	if(cnt++ < 10)
//		return;

	cnt = 0;

	lcd_gotoxy(4,1);
	char text[16];
	sprintf(text,"%d", progress);
    lcd_puts(text);

	if(upDown)
	{
		progress += 5;
		if(progress > 100)
		{
			progress = 100;
			upDown = false;
		}
	}
	else
	{
		progress -= 5;
		if(progress <= 5)
		{
			progress = 0;
			upDown = true;
		}
	}
}


/* main program starts here */
int main(void)
{
	WDTCSR = _BV(WDCE) | _BV(WDE);
	WDTCSR = (_BV(WDP2) | _BV(WDP1) | _BV(WDP0) | _BV(WDE));

	printp("Started\n");

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

	cOutput relay1(PORT_PF(0));
	cOutput relay2(PORT_PF(1));
	cOutput relay3(PORT_PF(2));
	cOutput relay4(PORT_PF(3));

//	cLED *leds[] =
//	{
//			&led1,
//			&led2,
//			&led3,
//			&led4,
//			0
//	};
//	cOutput *outs[] =
//	{
//			&relay1,
//			&relay2,
//			&relay3,
//			&relay4,
//			0
//	};
//	post(leds, outs);

	cInput sw1(PORT_PJ(2));
	cInput sw2(PORT_PJ(3));
	cInput sw3(PORT_PJ(4));
	cInput sw4(PORT_PJ(5));
	cInput sw5(PORT_PJ(6));

	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_home();
	lcd_puts("Schweeet Control");


	cHeartbeat heartbeat(&status);

	while(1)
	{
		watchdogReset();

		loading();


		Terminal.run();
		heartbeat.run();
		Buttons.run();


		_delay_ms(100);
	}

	return 0;
}

