#include <LPC214X.H>
#include "Serial.h"

unsigned char GsmSendMsg(unsigned char *msgStr);

void main(){
	
	Uart0_Init();
	Uart0_Puts("AT\r\n");		// Enter
	delay(100);
	Uart0_Puts("ATE0\r\n");			// Turn Echo off
	delay(100);
	//Uart0_Puts("ATD\r\n");
	delay(100);
	Uart0_Puts("ATD90144001579;\r\n");	// Dial number to call
	delay(10000);
	Uart0_Puts("ATH0\r\n");			// Disconnect call 
	delay(100);
	GsmSendMsg("GSM Interfacing Code");
	
	while(1);	
	
}

unsigned char GsmSendMsg(unsigned char *msgStr){
	Uart0_Puts("AT+CMGF=1\r\n");		// msg mode
	delay(100);
	Uart0_Puts("AT+CMGS=\"9104401579\"\r\n");
	delay(100);
	Uart0_Puts(msgStr);
	delay(100);
	Uart0_PutCh(0x1A);		// Ctrl+Z
	delay(100);
	return(1);
}