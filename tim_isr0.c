#include <lpc214x.h>
#define led 1<<8

__irq void T0_ISR (void)
{
	IO0PIN = ( IO0PIN ^ led );	/* Toggle P0.8 pin */ 
	T0IR = ( T0IR | (0x01) ); 	// T0IR=0x01
	VICVectAddr = 0x00;
}

void pll()                       //Fosc=12Mhz,CCLK=60Mhz,PCLK=60MHz
{
    PLL0CON=0X01;
    PLL0CFG=0X24;
    PLL0FEED=0XAA;
    PLL0FEED=0X55;
    while((PLL0STAT&(1<<10))==0);
    PLL0CON=0X03;
    PLL0FEED=0XAA;
    PLL0FEED=0X55;
    VPBDIV=0X02;		// 30Mhz
}

int main (void)
{
	IODIR0 =led;	
	
	pll();
	
	// Interrput Init
	VICIntSelect &= ~(1<<4);
	VICVectCntl0= 0x20 |4;
	VICVectAddr0= (unsigned long)T0_ISR;
	VICIntEnable= 1<<4; 

	// Timer Init
 T0TCR =0x02 ;   // reset the TC & PC, Disable the Timer
 T0CTCR=0x00;	// tiemr mode
  T0PR=29; 	// 0x1d (1us)
	//T0PR = 29999;		// 1ms

 T0MR0=10000; // for 1ms
 T0MCR=0x03;		// Interrupt Generate & Reset the TC
	 T0TCR=0x01;	// Enable TC& PC
	while(1);
}