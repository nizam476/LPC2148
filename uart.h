#include<lpc214x.h>

void Uart0_Init(void){
	PINSEL0=0x00000005;
	U0LCR=0x83;
	U0DLM=0x00;
	U0DLL=0x97;
	U0LCR=0x03;
}

unsigned char Uart0_PutCh(unsigned char ch){
	U0THR=ch;
	while(!(U0LSR & 0x20));
	return(ch);
}

void Uart0_PutS(unsigned char *str){
	while(*str)
		Uart0_PutCh(*str++);
}