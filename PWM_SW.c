#include <lpc214x.h>

//#define PLOCK 0x00000400
//#define PWMPRESCALE 60   //60 PCLK cycles to increment TC by 1 i.e 1 Micro-second 

void initPWM(void);
void initPLL(void);

int main(void)
{
  IO0DIR = 0x1; 	//This is not needed!
	PINSEL0 =0X02;			// PWM1 CONFIG
	
	initPLL();
	initPWM(); //Initialize PWM
   
    while(1)
    {
		if( !((IO0PIN) & (1<<1)) ) // Check P0.1
		{
			PWMMR1 = 2500; 				//T-ON=25% , Hence 25% Bright
			PWMLER = (1<<1); 			//Update Latch Enable bit for PWMMR1
		}
		else if( !((IO0PIN) & (1<<2)) ) // Check P0.2
		{
			PWMMR1 = 5000; //50% Bright
			PWMLER = (1<<1);
		}
		else if( !((IO0PIN) & (1<<3)) ) // Check P0.3
		{
			PWMMR1 = 7500; //75% Bright
			PWMLER = (1<<1);
		}
		else if( !((IO0PIN) & (1<<4)) ) // Check P0.4
		{
			PWMMR1 = 10000; //100% Bright
			PWMLER = (1<<1);
		}
    }
    //return 0; //normally this wont execute ever
}

void initPWM(void)
{
	/*Assuming that PLL0 has been setup with CCLK = 60Mhz and PCLK also = 60Mhz.*/
	
	PINSEL0 = (1<<1); // Select PWM1 output for Pin0.0
	PWMPCR = 0x0; 		//Select Single Edge PWM - by default its single Edged so this line can be removed
	PWMPR = 60-1; 		// 1 micro-second resolution
	PWMMR0 = 10000;		 // 10ms period duration
	PWMMR1 = 2500; 		// 2.5ms - pulse duration i.e width (Brigtness level)
	PWMMCR = (1<<1);	 // Reset PWMTC on PWMMR0 match
	PWMLER = (1<<1) | (1<<0); // update MR0 and MR1
	PWMPCR = (1<<9); 			// enable PWM output
	PWMTCR = (1<<1) ;		 //Reset PWM TC & PR

	//Now , the final moment - enable everything
	PWMTCR = (1<<0) | (1<<3); // enable counters and PWM Mode

	//PWM Generation goes active now - LED must be 25% Bright after Reset!!
	//Now you can get the PWM output at Pin P0.0!
}


void initPLL(void)
{
// To generate 60MHz from 12MHz crystal 
		PLL0CFG=0X24;							// SET PSEL=2 AND MSEL=5  
		PLL0CON=0X01;							//PLL IS ACTIVE BUT NOT YET CONNECT  
		PLL0FEED=0XAA; 						//FEED SEQUENCE
	PLL0FEED=0X55;  
		while((PLL0STAT & 0X400)==0); 			//WAIT FOR FEED SEQUENCE TO BE INSERTED
	PLL0CON=0X03;											// PLL HAS BEEN ACTIVE AND BEING CONNECTED 			
	PLL0FEED=0XAA;									 //FEED SEQUENCE
	PLL0FEED=0X55;				 					//FEED SEQUENCE
	VPBDIV=0x01;								// SET PCLK AS SAME (60Mhz)
}
















/*	
	1. Recieve Interrupt 
Connect the 2 led 
When 1 recieved led1 on, & when 0 recieved led1 off
When a recieved led2 on, & when b recieved led2 off

2.
Recieve the string from Uart terminal & Display on LCD

*/





/*
#include<lpc214x.h>

void delay(unsigned int z);        

void pll();

int main(void)
{
    IO0DIR=0xffffffff;
    pll();                  //Fosc=12Mhz,CCLK=60Mhz,PCLK=60MHz
    while(1) {
        IO0SET=0xffffffff;
        delay(1000);               //1sec delay
        IO0CLR=0xffffffff;
        delay(1000);               //1sec delay
    }
}


void pll()                  //Fosc=12Mhz,CCLK=60Mhz,PCLK=60MHz
{
    PLL0CON=0x01;
    PLL0CFG=0x24;
    PLL0FEED=0xaa;
    PLL0FEED=0x55;
    while(!(PLL0STAT&(1<<10)));
    PLL0CON=0x03;
    PLL0FEED=0xaa;
    PLL0FEED=0x55;
    VPBDIV=0x01;
}


void delay(unsigned int z)
{
    T0CTCR=0x0;                  //Select Timer Mode
    T0TCR=0x00;                 //Timer off
    T0PR=59999;                 //Prescaler value for 1ms
    T0TCR=0x02;                 //Timer reset
    T0TCR=0x01;                 //Timer ON
    while(T0TC<z);           
    T0TCR=0x00;                 //Timer OFF
    T0TC=0;                     //Clear the TC value. This is Optional.
}


#include<lpc214x.h>

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
    VPBDIV=0X01;
}

void wait()
{
    T1CTCR=0X0000;          //Timer Mode
    T1PR=59999;                 //Prescaler Value
    T1MR0=1;                 //Match Register Value
    T1MCR=0x00000004;       //TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC.
    T1TCR=0X02;                 //Reset Timer
    T1TCR=0X01;                 //Timer ON
    while(T1TC!=T1MR0);
    T1TC=0;                         //Timer OFF
}

int main(void)
{

    IO0DIR=0xffffffff;
    pll();                             //Fosc=12Mhz,CCLK=60Mhz,PCLK=60MHz

    while(1) {
        IO0SET=0xffffffff;
        wait();
        IO0CLR=0xffffffff;
        wait();
    }

}
*/