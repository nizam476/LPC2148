#include<lpc214x.h>
#include<stdio.h>

#define rs 0
#define en 1
void lcd_cmd(char);
void lcd_dat(unsigned char);
void delay(int);
void display(void);
void initPLL(void);
void lcd_string(char *str);


int main()
{	
	unsigned char i;
	char cmd[8]={0x38,0x0e,0x01,0x06,0x80};
	char name[12]="Temperature";

	PINSEL1=0x01000000;	// configure adc pin of AD0.1
	IODIR0=0x0000FFFF;
	//PINSEL2=0;
//	IODIR1=0XFFFF0000;
	
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
	IOCLR0=(1<<rs);	// 1<<0
	IOSET0=(1<<en); // 1<<1
	delay(10);
	IOCLR0=(1<<en);
	//IOCLR=cmd<<8
}

void lcd_dat(unsigned char dat)
{
	IOPIN0=dat<<8;
	IOSET0=(1<<rs);
	IOSET0=(1<<en);
	delay(10);
	IOCLR0=(1<<en);
}

void delay(int x)
{
	int i,j;
	for(i=0;i<300;i++)
	for(j=0;j<x;j++);
}

void display()
{
float temp=0.0;
char result[5];

   unsigned int val;
   	val=AD0GDR;
	val=(val>>6)&0x3FF;
	//IOPIN0=val<<8;	// val =1023
	
	temp=(((float)val/1023.0)*3.3*100);
	
		lcd_cmd(0xc0);
	sprintf(result,"%f",temp);
	
	lcd_string(result);
	
	lcd_cmd(0xdf);	// for degree cel
	lcd_dat('C');
	
}

void lcd_string(char *str)
{
	int i;
	for(i=0; str[i]!='\0'; i++)
		lcd_dat(str[i]);
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
VPBDIV=0x00;								// SET PCLK SAME AS FCCLK
}
