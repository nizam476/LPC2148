/*
#include<lpc214x.h>
void msg(char *st);
void lcd_init();
void cmd(unsigned char cm);
void data(unsigned char dt);
void delay(int a);

#define rs 1<<8
#define en 1<<9

void main(){
		IO0DIR=0xFFF;//| 1<<8 | 1<<9;
			lcd_init();
	while(1){

		msg("WELCOME");
		cmd(0xC0);
		msg("TechnoScripts");
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
*/

// P0 using SET & CLR REGISTER
#include<lpc214x.h>
void lcd_string(char *st);
void lcd_init();
void lcd_cmd(unsigned char cm);
void lcd_data(unsigned char dt);
void delay(int a);

#define rs 1<<8
#define en 1<<9

int main(){
		IO0DIR=0x3FF;//| 1<<8 | 1<<9;7
	// IO0DIR=0x000003ff
			lcd_init();
	lcd_string("WELCOME");
	
	while(1){
		delay(100);
		lcd_cmd(0xC0);
		lcd_string("In Arm 7 ");
		delay(200);
	//	cmd(1);
	}
}

void lcd_init(){
	lcd_cmd(0x38);
	lcd_cmd(0x0e);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
}

void lcd_cmd(unsigned char cm){
	IO0SET=cm;		// 38
	IO0CLR=rs;		// rs=0
	IO0SET=en;		// en=1
	delay(100);
	IO0CLR=en;		// en=0
	IO0CLR=cm;		// 38
}

void lcd_data(unsigned char dt){
	IO0SET=dt;
	IO0SET=rs;			// rs=1
	IO0SET=en;			// en=1
	delay(100);
	IO0CLR=en;		// en=0
	IO0CLR=dt;
}

void lcd_string(char *st){	// st= "WELCOME\0"
	while(*st!='\0'){
		lcd_data(*st++);
	}
}

void delay(int a){
	int i,j;
	for(i=0; i<a; i++);
	for(j=0; j<132; j++);
}
