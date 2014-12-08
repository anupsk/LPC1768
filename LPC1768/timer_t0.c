#define PCONP 		(*((volatile unsigned int *)0x400FC0C4))
#define PCLKSEL0 	(*((volatile unsigned int *)0x400FC1A8))
#define MR0_T0 		(*((volatile unsigned int *)0x40004018))
#define MCR0_T0 	(*((volatile unsigned int *)0x40004014))
#define TCR_T0		(*((volatile unsigned int *)0x40004004))
#define PR_T0			(*((volatile unsigned int *)0x4000400C))
#define NVIC_ISER	(*((volatile unsigned int *)0xE000E100))
#define IR_T0			(*((volatile unsigned int *)0x40004000))
	
#define COUNT_PER_MS	0x05DC
unsigned short int flag = 0;
	
void (*cb_func)(void);

void TIMER0_IRQHandler(){
	IR_T0 = IR_T0 | (1 << 0);
	cb_func();
	flag = 1;
}

int initialize_timer0() {
	if(!(PCONP & 0x0002)){
		return -1;
	}	
	
	NVIC_ISER = 0x02; 						//Enable Timer0 interrupt bit in NVIC chip.	
	PCLKSEL0 	= PCLKSEL0	| 0x0C; //pclk = cclk/8;   cclk = 12MHz
																//Reducing frequency to lowest to reduce power consumption
																//Also, for minimum of 1ms delay, high frequency is not necessary
	PR_T0 		= 0x00;							
	MCR0_T0 	= MCR0_T0 	| 0x03; //set interrupt on counter match
	
	return 0;
}

int delay_cb(unsigned int ms_hex, void (*f)(void)){
	cb_func = f;
	if(initialize_timer0())
			return -1;
	
	MR0_T0 		= ms_hex * COUNT_PER_MS; //counter to be matched value
	TCR_T0 		= TCR_T0 		| 0x01;
	
	return 0;
}

int delay_b(unsigned int ms_hex){
	if(initialize_timer0())
			return -1;
	
	MR0_T0 		= ms_hex * COUNT_PER_MS; //counter to be matched value
	TCR_T0 		= TCR_T0 		| 0x01;
	while(0 == flag){}
	flag = 0;
	return 0;
}


