#include <lpc214x.h>
#define sw1 1<<8
#define sw2 1<<9
#define sw3 1<<10

void delay_ms(unsigned int j)
{
    unsigned int x,i;
	for(i=0;i<j;i++)
	{
    for(x=0; x<6000; x++);    /* loop to generate 1 milisecond delay with Cclk = 60MHz */
	}
}

int main (void)
{
  unsigned int value;
	unsigned int i;
		unsigned int sin_wave[42]={512,591,665,742,808,873,926,968,998,1017,1023,1017,998,968,926,873,808,742,665,591,512,436,359,282,216,211,151,97,55,25,6,0,6,25,55,97,151,211,216,282,359,436 };

	i = 0;
	PINSEL1 = 0x00080000;	/* P0.25 as DAC output */
	IO0DIR = ( IO0DIR & 0xFFFFF0FF ); /* Input pins for switch. P0.8 sine, P0.9 triangular, P0.10 sawtooth, P0.11 square */
	while(1)
	{
		if(!(IO0PIN & sw1)){	// triangular
			i=0;
			while(i!=1023){
				DACR = i<<6;
				i++;
			}
			i=1023;
			while(i!=0){
				DACR=i<<6;
				i--;
			}
			
		}
		else if(!(IO0PIN & sw2)){		// sawtooth
			i=0;
			while(i!=1023){
				DACR= i<<6;
				i++;
			}
			i=0;
		
		}
		else if(!(IO0PIN & sw3)){
			i=0; 
			DACR= i<<6;
			delay_ms(100);
			i=1023;
			delay_ms(100);
			
			//while()
		}
		else{
			value=1023;
			DACR= value<<6;
		}
	}
}