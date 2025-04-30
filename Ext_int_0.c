#include<lpc214x.h>
void extint0_isr(void) __irq ;
unsigned char int_flag=0,flag=0;

int main()
{
	IO1DIR=0x02000000;
	IO1SET=0x02000000;
	PINSEL1=0x00000001;			// P0.16
		
	EXTMODE=0x01;				// falling edge
	EXTPOLAR=0X00;
	VICVectAddr0=(unsigned long)extint0_isr;
	VICVectCntl0=0X20 | 14;
	VICIntEnable |=0X00004000;
	while(1)
	{
		if(int_flag==0X01)
		{
			if(flag==0X00)
			{
				IO1CLR=0x02000000;
				flag=1;
			}
			else if(flag==0X01)
			{
				IO1SET=0x02000000;
				flag=0;
			}
			int_flag=0X00;
		}
	}
}

void extint0_isr(void)__irq
{
	EXTINT|=0x01;
	int_flag=0X01;
	VICVectAddr=0;
}
