#include<lpc214x.h>
void delay(unsigned int ms);
void initPLL(void);

void initPLL(void)
{
// To generate 60MHz from 12MHz crystal 
		PLL0CFG=0X24;							// SET PSEL=2 AND MSEL=5  
		PLL0CON=0X01;							//PLL IS ACTIVE BUT NOT YET CONNECT  
		PLL0FEED=0XAA; 					//FEED SEQUENCE
	PLL0FEED=0X55;  
		while((PLL0STAT & 0X400)==0); 	//WAIT FOR FEED SEQUENCE TO BE INSERTED
	PLL0CON=0X03;											// PLL HAS BEEN ACTIVE AND BEING CONNECTRD 			
	PLL0FEED=0XAA;									 //FEED SEQUENCE
	PLL0FEED=0X55;				 					//FEED SEQUENCE
	
VPBDIV=0x01;								// SET PCLK SAME AS FCCLK
}

void delay(unsigned int ms)
{
	T0CTCR = 0x00 ;		 				 // configure T0 as Timer
  T0PR =59999;							// 1KHz
	T0TCR = 0x02; 						//restart timer
	T0TCR = 0x01; 							//Enable/START timer 
	while(T0TC < ms); 			 //wait until timer counter reaches the desired delay
	T0TC=0;								// reset timer counter
	T0TCR = 0x00; 							//Disable/STOP timer
}

int main()
{
	IO0DIR=1<<0;
	initPLL();
	while(1)
	{
		IO0SET=1<<0;
		delay(500);	// 1000ms= ?sec
		IO0CLR=1<<0;
		delay(300);
	}	
}

//TASK: Using Timer 1 Generate the delay 1us









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