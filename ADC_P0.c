/*
#include <LPC214X.H>
#define rs (1<<8)
#define en 1<<9

void delay(int time){
	int i,j;
	for(i=0;i<time;i++){
		for(j=0;j<500;j++);
	}
}

void lcd_cmd(int cmd){
	IO0PIN =cmd;
	//	IO0SET |= cmd;
	IO0CLR |= rs;  //0 for sending command
	IO0SET |= en;
	delay(20);
	IO0CLR |= en;
//	IO0CLR |= cmd;
}

void lcd_data(int data){
	IO0PIN =data;
//	IO0SET |= data;
	IO0SET |= rs;  //1 for sending data
	IO0SET |= en;
	delay(20);
	IO0CLR |= en;
//	IO0CLR |= data;
}

void lcd_init(){
	lcd_cmd(0x0f); //switching on lcd
	//lcd_cmd(0x0C);	//Display on, cursor off
	//lcd_cmd(0x0E);	//Display on, cursor blink
	lcd_cmd(0x38); //for 8 bit mode 5x7 matrix
	lcd_cmd(0x01); //clearing screen
	lcd_cmd(0x06);	
	lcd_cmd(0x80); //first row first col
}

void lcd_string(char *str){
	while(*str!='\0'){
		lcd_data(*str++);
	}
}

void adc_init(){
	unsigned int temp,result;
	unsigned char a,b,c,d;
	//while(!((AD0GDR >> 31) & 1));
		while(!(AD0GDR & 1<<31));	   //waiting A/D conversion
	
	result = AD0GDR;
	result = (( result>>6) & 0x3ff);
	
	temp =result;
		
	a = (temp%10);
	temp = temp/10;
		
	b=(temp%10);
	temp = temp/10;
	
	c=(temp%10);
	temp = temp/10;
	
	d=(temp%10);
	
	
	lcd_data(d+48);
	lcd_data(c+48);
	lcd_data(b+48);
	lcd_data(a+48);
		
	
	delay(500);
}

int main(){	
	IO0DIR = 0x000003ff;
		PINSEL1 = 0x01000000;

	lcd_init();
	lcd_string("ADC values: ");

	while(1){
			AD0CR = 0x01200202;
	
		lcd_cmd(0xc0); 
		adc_init();
	}	
}
*/

#include<lpc214x.h>
#define rs 1<<8
#define en 1<<9

void msg(char *st);
void lcd_init();
void cmd(unsigned char cm);
void data(unsigned char dt);
void delay(int a);
void display();
void initPLL(void);

int main(){
		IO0DIR=0x3FF;//| 1<<8 | 1<<9;
			PINSEL1 = 0x01000000;
	
	initPLL();
			lcd_init();
	// ADC Init
	//	AD0CR=0x01200202;

	msg("ADC VAlue:");
	while(1){
	 			AD0CR=0x01200302;
	while(!(AD0GDR & 1<<31));	   //waiting A/D conversion
	display();
	delay(10);
	}
}

void lcd_init(){
	cmd(0x38);
	cmd(0x0e);
	cmd(0x01);
	cmd(0x80);
}
void cmd(unsigned char cm){
	IO0PIN=cm;
	IO0CLR=rs;
	IO0SET=en;
	delay(100);
	IO0CLR=en;
}

void data(unsigned char dt){
	IO0PIN=dt;
	IO0SET=rs;
	IO0SET=en;
	delay(100);
	IO0CLR=en;
}

void msg(char *st){
	while(*st!='\0'){
		data(*st++);
	}
}

void delay(int a){
	int i,j;
	for(i=0; i<a; i++);
	for(j=0; j<132; j++);
}

void display()
{
  unsigned char a,b,c,d;	
   unsigned int val;
   	val=AD0GDR;
	val=(val>>6)&0x3FF;
	//IOPIN0=val<<8;	// val =1023
	
   a=val%10;
   val=val/10;
	
   b=val%10;
   val=val/10;
	
   c=val%10;
   val=val/10;
	
   d=val%10;
	
	cmd(0xC0);
   data(d+48);
   data(c+48);
   data(b+48);
   data(a+48);	
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