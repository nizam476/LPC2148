#include<lpc214x.h>
#define IN1  1<<0
#define IN2  1<<1
#define EN1  1<<2
#define EN2  1<<3
#define IN3  1<<4
#define IN4  1<<5

#define sw1  1<<16
#define sw2  1<<17
#define sw3  1<<18
#define sw4  1<<19

void delay()
{
	int i,j;
	for(i=0;i<255;i++)
	for(j=0;j<255;j++);
}
int main()
{
	IO0DIR|=IN1|IN2| IN3 | IN4 | EN1 | EN2;								// OUTPUT
	IO1DIR= 0<<16| 0<<17 | 0<<18 | 0<<19;									// 4 Switches	
	//IO1DIR =0x00000000;
	
	while(1)
	{
	if((IO1PIN & sw1)==0)
	{
		IO0SET=EN1;
		IO0SET=EN2;
		IO0SET=IN1;					// All CLk wise
		IO0CLR=IN2;
		IO0SET=IN3;
		IO0CLR=IN4;
	}
	else if((IO1PIN & sw2)==0){
		IO0SET=EN1;
		IO0SET=EN2;
		IO0CLR=IN1;
		IO0SET=IN2;						// ALL Anti clk
		IO0CLR=IN3;
		IO0SET=IN4;
	}
	else if((IO1PIN & sw3)==0){
				IO0SET=EN1;
		IO0CLR=EN2;
		IO0SET=IN1;							// 2 clk wise
		IO0CLR=IN2;
//		IO0CLR=IN3;						// 2 STOP
//		IO0CLR=IN4;
	}
		else if((IO1PIN & sw4)==0){
		IO0SET=EN1;
		IO0CLR=EN2;
		IO0CLR=IN1;						// 2 Anti clk witse
		IO0SET=IN2;
//		IO0CLR=IN3;							// 2 STOP
//		IO0CLR=IN4;
	}
	else{
		IO0CLR=IN1;
		IO0CLR=IN2;
		IO0CLR=IN3;
		IO0CLR=IN4;
	}
 }
}
