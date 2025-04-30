#include <LPC214X.H>
#define S1 1<<8
#define S2 1<<9

void delay(int a){
	int i,j;
	for(i=0; i<a; i++)
	for(j=0; j<a;j++);
}
int main(){
		int arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
		int i,temp;
		
		IO0DIR=0x3ff;
		// IODIR0=0X000003FF
	while(1){
		for(i=0; i<100; i++)
		{
			IO0CLR=0xff;		// INITAILLY ALL ZERO 8 PIN
			IO0CLR|= S1 | S2;	
			
			temp=i%10;			// 3 /10 =0.3 --> 0		
			IO0SET=S1;				// select 1 seg1 
			IO0CLR=S2;			// UNSELECT seg2
			IO0SET=arr[temp];	// --> 0-7
	
			delay(200);
			IO0CLR=0xff;	// IO0CLR = arr[temp]; (optional)
	
			IO0SET=S2;		// SELSECT 2 
			IO0CLR=S1;		// UNSELECT 1
			temp=i/10; 		// 3%10 = 0.3 --> 3
			IO0SET=arr[temp];
			delay(200);
		}
	}
}