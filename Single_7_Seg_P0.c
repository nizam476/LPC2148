/*
#include <LPC214X.H>

void delay(int a){
	int i,j;
	for(i=0; i<a; i++)
	for(j=0; j<1231; j++);
}

void main(){
	int i;
	int arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
	IO0DIR=0xff;
		while(1)
		{
			for(i=0; i<10; i++)
			{
				IO0SET=arr[i]<<8;
				delay(1000);
				IO0CLR=arr[i]<<8;
			}			
		}
}

*/
/*
// Using IOPIN REGISTER
#include <LPC214X.H>

void delay(int a){
	int i,j;
	for(i=0; i<a; i++)
	for(j=0; j<1231; j++);
}
void main(){
	int i;
	int arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
	IO0DIR=0xff;
		while(1){
			for(i=0; i<10; i++){
				IO0PIN=arr[i];
				delay(100);

			}
			
		}
}
*/


#include <LPC214X.H>

void delay(int a){
	int i,j;
	for(i=0; i<a; i++)
	for(j=0; j<1231;j++);
}
int main(){
	int i;
//	int arr[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
	//unsigned int arr[]={0xf3,0x12,0x163,0x133,0x192,0x1b1,0x1f1,0x13,0x1f3,0x1b3};
	
		int arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
	IO0DIR=0x000000ff;
		// IODIR0 = 0xff;	--> 0-7 pins as o/p
		while(1){
			for(i=0; i<10; i++){
				IO0SET=arr[i];
				delay(100);
				IO0CLR=arr[i];
			}
		}
}
