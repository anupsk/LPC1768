#define FIO1MASK2 (*((volatile unsigned char *)0x2009C032))
#define FIO1DIR2 (*((volatile unsigned char *)0x2009C022))
#define FIO1SET2 (*((volatile unsigned char *)0x2009C03A))
#define FIO1CLR2 (*((volatile unsigned char *)0x2009C03E))


void leds_state(unsigned short int state){	
	/*Mask: Access only 4 bits related to
		4 LEDs. Restrict other bits.
		Bit value 0 = allow
		Bit value 1 = block*/
	FIO1MASK2 = 0x4B;
	
	/*Set 4 bits related to 4 LEDS as output
	  pins.
		Bit value 0 = input
		Bit value 1 = output*/
	FIO1DIR2 = 0xB4;
		
	//Set pins high for LEDs to switch on
	FIO1SET2 = FIO1SET2 | state;
	
	//Ser pins high for LEDs to turn off
	FIO1CLR2 = FIO1CLR2 | ~state;
}
