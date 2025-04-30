#include <LPC214X.H>
void delay(int a);

int main()
{
	IO0DIR |= (1<<10) | (1<<11); 
	// Configure the Digital O/p
	
	while(1){
	 IOSET0 |= (1<<10) | (1<<11);
		// Turn ON 2 LEDs
		delay(100);
	 IOCLR0 |= (1<<10) | (1<<11);
		// Turn Off 2 Leds
		delay(100);
	}
}

void delay(int a)
{
	int i,j;
	for(i=0; i<a; i++)
	for(j=0; j<a; j++);
}
