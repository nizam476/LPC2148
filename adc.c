#include<lpc214x.h>
#define rs 1<<0  
#define en 1<<1 

void lcd_cmd(char);
void lcd_dat(unsigned char);
void delay(int);
void display(void);
void initPLL(void);

int main()
{	
	unsigned char i;
	char cmd[8]={0x38,0x0e,0x01,0x06,0x80};
	char name[12]="ADC Values";

	PINSEL1=0x01000000;	// configure adc pin of AD0.1
	IODIR0=0x000FFFF;
	//PINSEL2=0;
	initPLL();
		
	for(i=0;i<6;i++)
	 {
	 	lcd_cmd(cmd[i]);
		delay(5);
	 }
	 for(i=0;i<12;i++)
	{
	 	lcd_dat(name[i]);
		delay(100);
	}
while(1)
{
		AD0CR=0X01200302;	   //AD0.1, start conversion
	//AD0CR=0x01200202;
	 
	while(!(AD0GDR & 1<<31));	   //waiting A/D conversion
	display();
	delay(10);
//	lcd_cmd(0x01);
 }
}

void lcd_cmd(char cmd)
{
	IOPIN0=cmd<<8;
	//IO0SET=cmd<<8
	IOCLR0=rs;	// 1<<0
	IOSET0=en; // 1<<1
	delay(10);
	IOCLR0=en;
	//IOCLR=cmd<<8
}

void lcd_dat(unsigned char dat)
{
	IOPIN0=dat<<8;
	IOSET0=rs;
	IOSET0=en;
	delay(10);
	IOCLR0=en;
}

void delay(int x)
{
	int i,j;
	for(i=0;i<100;i++)
	for(j=0;j<x;j++);
}

void display()
{
  unsigned char a,b,c,d;	
   unsigned int val;
	
   	val=AD0GDR;
	val=(val>>6)&0x3FF;
	//IOPIN0=val<<8;	// val =1023
	
  a = val /1000;		// 1
  b = val /100 %10;	// 0
  c = val /10 %10;	// 2
  d = val %10;			// 3
	
	lcd_cmd(0x8C);
   lcd_dat(a+48);
   lcd_dat(b+48);
   lcd_dat(c+48);
   lcd_dat(d+48);	
}

void initPLL(void)
{
// To generate 60MHz from 12MHz crystal 
	PLL0CFG=0X24;							// SET PSEL=2 AND MSEL=5  
	PLL0CON=0X01;							//PLL IS ACTIVE BUT NOT YET CONNECT  
	PLL0FEED=0XAA; 					//FEED SEQUENCE
	PLL0FEED=0X55;  
		while((PLL0STAT & 0X400)==0); 	//WAIT FOR FEED SEQUENCE TO BE INSERTED
	PLL0CON=0X03;											// PLL HAS BEEN ACTIVE AND BEING CONNECTRD 			
	PLL0FEED=0XAA;									 //FEED SEQUENCE
	PLL0FEED=0X55;				 					//FEED SEQUENCE
	
	VPBDIV=0x00;								// SET PCLK 15Mhz
}
