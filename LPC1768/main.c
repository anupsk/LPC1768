/*
	Blink 4 Leds on LPC1768 as a 4-bit counter.
	Blinking interval of 1 second.
	Using hardware timer for 1 second interval.
*/

#include "timer_t0.h"
#include "leds_board.h"

#define ONE_SECOND_DELAY_MS_HEX					0x03E8 	//1000ms(decimal) = 0x03E8(hex)
#define BLINK_INTERVAL_MS_HEX						ONE_SECOND_DELAY_MS_HEX
#define COUNT_MAX												15

static unsigned short int counter;
static unsigned short int state;

void error(void){
	while(1);
}	

void isr(void){
	state = 	 	((counter & 0x08) << 4 |
							(counter & 0x04) << 3 |
							(counter & 0x02) << 3 |
							(counter & 0x01) << 2);
	leds_state(state);
	counter++;
	if(COUNT_MAX == counter)
			counter = 0;		//Restart counter from 0
}

int main(void){
	if(delay_cb(BLINK_INTERVAL_MS_HEX, isr))
			error();
	
	while(1);
}