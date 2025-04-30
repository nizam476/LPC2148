#include<lpc214x.h>
#include "Serial.h"

void Uart0_Init(void){
	
	PINSEL0=0x05;
	U0LCR=0x83;				// 8 bits, no Parity 1 Stop bit
	U0DLL=0x97;				// 9600 B.R
	U0LCR=0x03;				// DLAB=0
	
}

void Uart0_PutCh(unsigned char ch){
	U0THR=ch;
	while(!(U0LSR & 0x20));
}

void Uart0_Puts(unsigned char *str){

	while(*str){
		Uart0_PutCh(*str++);
		
	}
}
 void delay(int a){
	int i,j;
	 for(i=0; i<a; i++)
	 for(j=0; j<123; j++);
 }