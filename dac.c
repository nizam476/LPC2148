#include <LPC214X.H>

int main(){
	int i;
	PINSEL1=0x00080000;	// Aout of DAC
//	IO0DIR =0x0200000;	// o/p pin no. P0.25
	
	while(1){
		for(i=0x00; i<=0x3FF; i++)
			DACR=i<<6;
		for(i=0x3ff; i>=0x00; i--)
			DACR=i<<6;		
	}
}    