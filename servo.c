#include <avr/io.h>
#include "servo.h"

void servo_init(void) {
	//xmegaA, pp160. In frequency generation mode, freq = clk/(2N(CCA+1)), N = prescaler
	//also pp160, freq = clk/(N(PER+1))
	// /1024 = 1953.125
	TCC0.CTRLA |= TC_CLKSEL_DIV64_gc /*TC_CLKSEL_DIV256*/;
	TCC0.CTRLB |= TC0_CCAEN_bm | TC_WGMODE_DSBOTH_gc ;
	TCC0.PER = 312;

	//dirset is required
	PORTC.DIRSET = PIN0_bm;
	PORTC.OUTCLR = PIN0_bm;
}

void servo_set_angle(uint8_t angle) {
	const uint8_t cca_min = 10;
	const uint8_t cca_max = 38;

	//map [0,180] -> [cca_min, cca_max]
	TCC0.CCA = cca_min + ((float)(cca_max-cca_min))/180 * angle;
}
