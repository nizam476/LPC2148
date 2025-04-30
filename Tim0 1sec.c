#include <LPC214X.H>
#define led 1<<0

void t0_delay(){

	
T0CTCR=0x00;	 //timer mode
	T0MR0=15000000;
	T0MCR=0X04;	
	T0TCR=0x01; //enable TC& PC
	
while(T0TC != T0MR0);	// waiting for desired delay
	// 0 < 1us
	T0TC=0;					// Clear flag bit 

 //T0TCR=0x00;	// stop the timer
}

void initPLL(void)
{
// To generate 60MHz from 12MHz crystal 
	PLL0CFG=0X24;							// SET PSEL=2 AND MSEL=5  
	PLL0CON=0X01;							//PLL IS ACTIVE BUT NOT YET CONNECT  
	PLL0FEED=0XAA; 					//FEED SEQUENCE
PLL0FEED=0X55;  
	while((PLL0STAT & 0X400)==0); 			//WAIT FOR FEED SEQUENCE TO BE INSERTED
PLL0CON=0X03;											// PLL HAS BEEN ACTIVE AND BEING CONNECTRD 			
PLL0FEED=0XAA;									 //FEED SEQUENCE
PLL0FEED=0X55;				 					//FEED SEQUENCE
VPBDIV=0x00;								// SET PCLK SAME AS FCCLK
}

int main(){
	IO0DIR= led;	// 1<<0
	initPLL();
	while(1)
	{
	IO0SET=led;
		t0_delay();		// 1000us  delay generate 1ms
		IO0CLR=led;
		t0_delay();	// 10us
	}
}