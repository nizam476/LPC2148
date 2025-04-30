#include <lpc214x.h>
#include <stdint.h>

void initPLL(void);

void initPLL(void)
{
// To generate 60MHz from 12MHz crystal 
		PLL0CFG=0X24;									// SET PSEL=2 AND MSEL=5  
		PLL0CON=0X01;									//PLL IS ACTIVE BUT NOT YET CONNECT  
		PLL0FEED=0XAA; 								//FEED SEQUENCE
	PLL0FEED=0X55;  	
		while((PLL0STAT & 0X400)==0); 	//WAIT FOR FEED SEQUENCE TO BE INSERTED
	PLL0CON=0X03;											// PLL HAS BEEN ACTIVE AND BEING CONNECTRD 			
	PLL0FEED=0XAA;									 //FEED SEQUENCE
	PLL0FEED=0X55;				 					 //FEED SEQUENCE
	VPBDIV=0x02;										// SET PCLK 30Mhz
}

void delay_ms(uint16_t j)
{
    uint16_t x,i;
	for(i=0;i<j;i++)
	{
    for(x=0; x<6000; x++);    /* loop to generate 1 milisecond delay with Cclk = 60MHz */
	}
}

int main (void)
{
	uint32_t value=1;

	PINSEL0 |= 0x00000008; /* Configure P0.1 as PWM3 */
	initPLL();
		
// For single edge controlled PWM3
	PWMTCR = 0x02; 				/* Reset and disable counter for PWM */
	PWMPR = 0x1D;					/* Prescale value for 1usec, Pclk=30MHz*/
	PWMMR0 = 1000;				/* Time period of PWM wave, 1msec */
	PWMMR3 = value;				/* Ton of PWM wave */
	PWMMCR = 0x00000203;	/* Reset and interrupt on MR0 match, interrupt on MR3 match */
	PWMLER = 0x09;				/* Latch enable for PWM3 and PWM0 */
	PWMPCR = 0x0800;			/* Enable PWM3 and PWM0, single edge controlled PWM on PWM3 */
	PWMTCR = 0x09;				/* Enable PWM and counter */

	while (1)
	{
		while (value != 999)
		{
			PWMMR3 = value;
			PWMLER = 0x08;
			delay_ms(5);
			value++;
		}
		while (value != 1)
		{
			PWMMR3 = value;
			PWMLER = 0x08;
			delay_ms(5);
			value--;
		}	
	}
}