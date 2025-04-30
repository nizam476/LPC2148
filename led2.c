#include <LPC214X.H>
#define IN1 1<<0
#define IN2 1<<1
#define EN1 1<<2

void delay(int a);

int main(){

		IO0DIR=0x000000ff;
	while(1){
		IO0SET=EN1;
		IO0SET=IN1;
		IO0CLR=IN2;
		
	
	}
}

void delay(int a){
	int i,j;
	for(i=0; i<a; i++)
	for(j=0; j<a; j++);
}
