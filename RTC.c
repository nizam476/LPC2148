#include <LPC214X.H>

void lcd_string(char *st);
void lcd_init();
void cmd(unsigned char cm);
void data(unsigned char dt);
void delay(int a);

void Set_Time();
void Time();
void	initPLL();

#define rs 1<<8
#define en 1<<9

int main(){
		IO0DIR=0xFFF;//| 1<<8 | 1<<9;

		initPLL();
			lcd_init();
	
		Set_Time();
	lcd_string(" HH:MM:SS");
	while(1){

	Time();
	}
}

void Set_Time(){		// RTC INIT
	PREINT=456;
	PREFRAC=25024;
	CCR=0x02;			// clk tick counter are reset
	
	HOUR=12;			
		MIN=59;
		SEC=56;
	//CCR=0x11;		// clock enable, CTC take clk from RTC pins
		CCR=0x01;		// clk enable, clk from internal FREQ
}

void Time(){

	cmd(0xc1);			// 2ND ROW 2nd POS
	data(48+(HOUR/10));		// 2
	data(48+(HOUR%10));			// 2
	data(':');	
	data(48+(MIN/10));		// 4
	data(48+(MIN%10));			// 5
	data(':');
	data(48+(SEC/10));		// 5
	data(48+(SEC%10));		//8
//	data(':');
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
	delay(10);
	IO0CLR=en;
}

void data(unsigned char dt){
	IO0PIN=dt;
	IO0SET=rs;
	IO0SET=en;
	delay(10);
	IO0CLR=en;
}

void lcd_string(char *st){
	while(*st!='\0')
		data(*st++);
}

void delay(int a){
	int i,j;
	for(i=0; i<a; i++);
	for(j=0; j<132; j++);
}

void initPLL(void)
{
// To generate 60MHz from 12MHz crystal 
	PLL0CFG=0X24;							// SET PSEL=2 AND MSEL=5  
	PLL0CON=0X01;							//PLL IS ACTIVE BUT NOT YET CONNECT  
	PLL0FEED=0XAA; 					//FEED SEQUENCE
PLL0FEED=0X55;  
	while((PLL0STAT & 0X400)==0); 			//WAIT FOR FEED SEQUENCE TO BE INSERTED
PLL0CON=0X03;											// PLL HAS BEEN ACTIVE AND BEING CONNECTRD 			
PLL0FEED=0XAA;									 //FEED SEQUENCE
PLL0FEED=0X55;				 					//FEED SEQUENCE
VPBDIV=0x00;								// SET PCLK 1/4th = 15Mhz
}









