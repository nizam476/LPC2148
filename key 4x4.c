#include<lpc214x.h>
#define rs (1<<8)
#define en (1<<9)

//#define c1 1<<16

void delay(int);
void lcd_cmd(char);
void lcd_dat(char);
char keypad(void);
void lcd_init(void);

char c;					//GLOBAL VAR
int main()
{
	//PINSEL0=PINSEL2=0;
	IO0DIR=0x000003ff;		// lcd data pins o/p
	IO1DIR=0x00f00000;		// row --> o/p(1) & col--> i/p(0)
	
		lcd_init();
	while(1){
		c=keypad();
		lcd_dat(c);	// LCD_DATA('8')
		delay(10);
	}
}

void lcd_init()
{
	lcd_cmd(0x38);
	delay(5);
	lcd_cmd(0x0e);
	delay(5);
	lcd_cmd(0x01);
	delay(5);
	lcd_cmd(0x06);
	delay(5);
	lcd_cmd(0x80);
	delay(5);
}
void lcd_cmd(char cmd)
{
	IO0PIN=cmd;
	IO0CLR=rs;
	IO0SET=en;
	delay(1);
	IO0CLR=en;
}

void lcd_dat(char dat)
{
	IO0PIN=dat;
	IO0SET=rs;
	IO0SET=en;
	delay(1);
	IO0CLR=en;
}

void delay(int x)
{
	int i,j;
	for(i=0;i<1000;i++)
	for(j=0;j<x;j++);
}

char keypad()// function is return type (char , int, float) void --> Not return type
{
	while(1){
	IO1CLR |=(1<<20);										// r1=0
	IO1SET |=(1<<21)|(1<<22)|(1<<23);		//r2=r3=r4=1
		
	if(!(IOPIN1&(1<<16)))				// C1=1
	{//  if(!(0)) --> if(1)
		while(!(IOPIN1&(1<<16)));			//c1 still continuses pressed or not
		return '7';
	}
	if(!(IOPIN1&(1<<17)))		// 1 &1 =1  ! =0		// if 17 
	{
		while(!(IOPIN1&(1<<17)));	
		return '8';
	}
	if(!(IOPIN1&(1<<18)))
	{
		while(!(IOPIN1&(1<<18)));
		return '9';
	}
  if(!(IOPIN1&(1<<19)))
	{
		while(!(IOPIN1&(1<<19)));
		return '/';
	}

	IOCLR1=(1<<21);									// r2=0
	IOSET1=(1<<20)|(1<<22)|(1<<23);	// r1=r3=r4=1
	if(!(IOPIN1&(1<<16)))
	{
		while(!(IOPIN1&(1<<16)));
		return '4';
	}
	if(!(IOPIN1&(1<<17)))
	{
		while(!(IOPIN1&(1<<17)));
		return '5';
	}
	if(!(IOPIN1&(1<<18)))
	{
		while(!(IOPIN1&(1<<18)));
		return '6';
	}
	if(!(IOPIN1&(1<<19)))
	{
		while(!(IOPIN1&(1<<19)));
		return '*';
	}
	
	IOCLR1=(1<<22);									 // r3=0
	IOSET1=(1<<20)|(1<<21)|(1<<23); // r1=r2=r4=1
	if(!(IOPIN1&(1<<16)))
	{
		while(!(IOPIN1&(1<<16)));
		return '1';
	}
	if(!(IOPIN1&(1<<17)))
	{
		while(!(IOPIN1&(1<<17)));
		return '2';
	}
	if(!(IOPIN1&(1<<18)))
	{
		while(!(IOPIN1&(1<<18)));
		return '3';
	}
if(!(IOPIN1&(1<<19)))
	{
		while(!(IOPIN1&(1<<19)));
		return '-';
	}
	IOCLR1=(1<<23);				// r4=0
	IOSET1=(1<<22)|(1<<20)|(1<<21);
	if(!(IOPIN1&(1<<16)))
	{
		while(!(IOPIN1&(1<<16)));
		lcd_cmd(0x01);
	}
	if(!(IOPIN1&(1<<17)))
	{
		while(!(IOPIN1&(1<<17)));
		return '0';
	}
	if(!(IOPIN1&(1<<18)))
	{
		while(!(IOPIN1&(1<<18)));
		return '=';
	}
  if(!(IOPIN1&(1<<19)))
	{
		while(!(IOPIN1&(1<<19)));
		return '+';
	}
 }
}
