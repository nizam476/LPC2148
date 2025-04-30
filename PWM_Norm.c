/*
#include<lpc214x.h>
void initPLL(void);

void pwm_init(void)
{
	PINSEL0=0x8002;	// PWM1,PWM2 configured
	
	PWMPCR=0x600;		// PWM1&2 o/p enabled
//PWMTCR=0x0A; 	  //reset TC & PC,  disable timer, Enable PWM
	PWMTCR=0x02; 	  //reset TC & PC, disable timer,
	PWMMR0=150000;	//	Period Register  
	PWMTCR=0x09;		//PWM, TC & PC Enabled
	PWMMCR=0x02;		//PWMMR0=0; if PWMMR=PWMTC 
}

int main(void)
{
	initPLL();
	pwm_init();
	while(1)
	{
		//PWMMR1= 37500;	// 25% Duty cycle
		//PWMMR2= 90000;	// 60%
		//PWMMR1 =60000;		//(40% DC val)
		//PWMMR2 =105000;	 // 70% Duty Cycle
			
		PWMMR1=45000;	  // 30% Duty cycle
		PWMMR2 =112500;	// 75%
		
		PWMLER =0x6;
	}
}

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

	VPBDIV=0x00;								// SET PCLK 15Mhz
}
*/

// Code Working (calculation 60Mhz)

#include<lpc214x.h>
void initPLL(void);
void pwm_init(void);

int main(void)
{
	initPLL();
	pwm_init();
	while(1)
	{
			
		PWMMR1 = 6000;	  // 60% Duty cycle
		PWMMR2 = 2500;	 // 25%
		
		PWMLER =0x6;
	}
}

void pwm_init(void)
{
	PINSEL0=0x8002;	// PWM1,PWM2 configured
	
	PWMPCR=0x600;		// PWM1&2 o/p enabled
//PWMTCR=0x0A; 	  //reset TC & PC,  disable timer, Enable PWM
	PWMTCR=0x02; 	  //reset TC & PC, disable timer,
	
	PWMPR = 60-1; 		// 1 micro-second resolution
	PWMMR0 = 10000;		 // 10ms period duration

	PWMTCR=0x09;		//PWM, TC & PC Enabled
	PWMMCR=0x02;		//PWMMR0=0; if PWMMR0=PWMTC the Reset
}

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

	VPBDIV=0x01;								// SET PCLK 60Mhz
}