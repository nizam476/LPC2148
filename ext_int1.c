#include <lpc214x.h>
//#define led 1<<25
void DelayMs(unsigned int count)
{
 unsigned int i,j; 
 for(i=0;i<count;i++)
  for(j=0;j<1000;j++);
}

void ExtInt_Serve1(void)__irq
{
	
 IO1SET = 0xffffffff;				// ALL LEDs/ PINs ON
 DelayMs(4000);
 IO1CLR = 0xffffffff;				//ALL LEDs/ PINs OFF
 DelayMs(4000);
	
	 // IOPIN1 = (IO1PIN ^ (0x00800000));	// Toggle the single led
 EXTINT |=2;
 VICVectAddr=0;		// End of Interrupt execution
}

void ExtInt_Init1()
{
	 PINSEL0 |= 0x20000000;  // Enable EINT1 on P0.14
	 VICIntEnable |= (1<<15); // Enable INT1 to contribute for fiq/irq
	VICIntSelect &=~(1<<15);	// select the irq mode
 VICVectCntl0 = 0x20 | 15;  // 15 is index of  EINT1  
 VICVectAddr0 = (unsigned long) ExtInt_Serve1;

	//EXTINT=0x02;		// EXTINT |=1<<1
 EXTMODE |= 2;      // Edge sensitive mode on EINT1
 EXTPOLAR = 0;      // Falling edge sensitive 
	//EXTPOLAR &=~(1<<1); optioanl
}

int main(void)
{
 IO1DIR = 0xffffffff;	// o/p
//	IO1DIR | =led;
 ExtInt_Init1(); //Initialize Interrupt
	
	IO1SET = 0xffffffff;
 while(1)
 {
 }
}       