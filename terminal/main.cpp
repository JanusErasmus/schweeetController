#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "terminal.h"
#include "led.h"
#include "heartbeat.h"
#include "input.h"

void watchdogReset() {
  __asm__ __volatile__ (
    "wdr\n"
  );
}

void tryDebug(uint8_t argc, char **argv)
{
	printp("Mains Debug %d\n", argc);
}

extern const dbg_entry mainEntry = {tryDebug, "debug"};

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

	cInput sw1(PORT_PJ(2));
	cInput sw2(PORT_PJ(3));
	cInput sw3(PORT_PJ(4));
	cInput sw4(PORT_PJ(5));
	cInput sw5(PORT_PJ(6));

	cHeartbeat heartbeat(&status);

	while(1)
	{
		watchdogReset();


		Terminal.run();

		heartbeat.run();

		_delay_ms(100);
	}

	return 0;
}
