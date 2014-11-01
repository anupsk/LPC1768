#define FIO1MASK2 (*((volatile unsigned char *)0x2009C032))
#define FIO1DIR2 (*((volatile unsigned char *)0x2009C022))
#define FIO1SET2 (*((volatile unsigned char *)0x2009C03A))
#define FIO1CLR2 (*((volatile unsigned char *)0x2009C03E))

#define COUNT_MAX 16

void approx_delay(){
	int i = 0;
	for(;i<30000000;)
		i++;
}

int main() {
	/*Mask: Access only 4 bits related to
		4 LEDs. Block other bits.
		Bit value 0 = allow
		Bit value 1 = block*/
	FIO1MASK2 = 0x4B;
	
	/*Set 4 bits related to 4 LEDS as output
	  pins.
		Bit value 0 = input
		Bit value 1 = output*/
	FIO1DIR2 = 0xB4;

	unsigned short int counter = 0;
	unsigned short int temp;
	while(1){
		approx_delay();
		temp = counter;
		//Reorder bits to match LED port pins
		temp = 	 ((counter & 0x08) << 4 |
						 (counter & 0x04) << 3 |
						 (counter & 0x02) << 3 |
						 (counter & 0x01) << 2);
		
		//Set pins high for LEDs to switch on
		FIO1SET2 = FIO1SET2 | temp;
		
		//Ser pins high for LEDs to turn off
		FIO1CLR2 = FIO1CLR2 | ~temp;
		
		counter++;
		if(COUNT_MAX == counter)
			counter = 0;
	}
}