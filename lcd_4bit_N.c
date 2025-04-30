#include <LPC214X.H>
#define rs 1<<8
#define en 1<<9

void delay(int a){
	int i,j;
	for(i=0;i<128;i++)
		for(j=0;j<a;j++);
}

void lcd_cmd(char c){	// 0x28
	
	char temp;
	temp=c&0xf0;		//we get 1st (upper) nibble
	
	IOCLR0=rs;			// Command mode
	IOSET0=en;
	IOSET0 =IOSET0|temp;	// IOSET0=temp
	delay(10);
	IOCLR0=en;
	IOCLR0=temp;
	
	temp=c&0x0f;		// 2nd (lower) nibble 
	//IOCLR0=rs;
	IOSET0=en;
	temp=temp<<4;
	IOSET0=IOSET0|temp; //we get 2nd nibble
	delay(10);
	IOCLR0=en;
		IOCLR0=temp;
}

void lcddata(char dt){
	int temp;
	
	temp=dt&0xf0;		//we get 1st nibble
		IOSET0=rs;	// rs=1	(data mode)
		IOSET0=en;
	IOSET0=IOSET0|temp;
	delay(10);
	IOCLR0=en;
		IOCLR0=temp;
	
	temp=dt&0x0f;
	//IOSET0=rs;
	IOSET0=en;
	temp=temp<<4;
	IOSET0=IOSET0|temp;	//we get 2nd nibble
	delay(10);
	IOCLR0=en;
	IOCLR0=temp;
}

void lcd_string(char *st)
{
	while(*st!='\0'){
		lcddata(*st);
		st++;
	}
	delay(100);
}

int main(){
	IODIR0=0x3f0;	// all pin as o/p
	 
	lcd_cmd(0x02);	// 4 bit mode 
	delay(100);
	lcd_cmd(0x0f);
	delay(100);
	lcd_cmd(0x28);	// 4 bit mode 5x7 Matrix/pixel
	delay(100);
	lcd_cmd(0x01);
	delay(100);
	
				lcd_string("   TECHNOSCRIPTS    ");
	delay(100);	
		while(1);

}





/*
void lcdcom(int cm){
	int temp;
	
temp=cm&0xf0;
	
		IOCLR0=rs;
		IOSET0=en;
	IOSET0=IOSET0|temp;
	delay(10);
	IOCLR0=en;
	
		IOCLR0=temp;
	
	temp=cm&0x0f;
	
		IOCLR0=rs;
		IOSET0=en;
	temp=temp<<4;
	IOSET0=IOSET0|temp;
	delay(10);
	IOCLR0=en;
	
		IOCLR0=temp;
	

}
*/