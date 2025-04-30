#include <LPC214X.H>
#include "uart.h"

void delay(int a){
	int i,j;
	for(i=0; i<a; i++)
	for(j=0; j<132; j++);
}
void main(void){
	
	Uart0_Init();
	delay(100);
	Uart0_PutS("AT\r\n");
	delay(100);
	Uart0_PutS("ATE0\r\n");
	delay(100);
	Uart0_PutS("AT+CMGF=1\r\n");
	delay(100);
	Uart0_PutS("AT+CMGS=\"90144015709\"\r\n");
	delay(100);
	Uart0_PutS("Welcome to GSM");
	delay(100);
	Uart0_PutCh(0x1A);		// ctrl +Z
	delay(100);
	while(1);
	
}
