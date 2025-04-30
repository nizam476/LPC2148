#include <LPC214X.H>
void initPLL(void);
void Send_string(char *str);

void initPLL(void)
{
// To generate 60MHz from 12MHz crystal 
		PLL0CFG=0X24;							// SET PSEL=2 AND MSEL=5  
		PLL0CON=0X01;							//PLL IS ACTIVE BUT NOT YET CONNECT  
		PLL0FEED=0XAA; 						//FEED SEQUENCE
	PLL0FEED=0X55;  
		while((PLL0STAT & 0X400)==0); 			//WAIT FOR FEED SEQUENCE TO BE INSERTED
	PLL0CON=0X03;											// PLL HAS BEEN ACTIVE AND BEING CONNECTED 			
	PLL0FEED=0XAA;									 //FEED SEQUENCE
	PLL0FEED=0X55;				 					//FEED SEQUENCE
	VPBDIV=0x00;								// SET PCLK AS 1/4th (15Mhz)
}

void Uart0_Init(void){
	
	PINSEL0=0x05;			// Configure the TX & RX pins
	U0LCR=0x83;				// 8 bits, no Parity 1 Stop bit, dlab=1
	U0DLL=0x61;				// 9600 B.R (15Mhz)
	U0DLM=0x00;
//	U0DLL=0x86;				// 9600 B.R (60Mhz)
//	U0DLM=0x01;
	U0LCR=0x03;				// DLAB=0
}

int main(){
  initPLL();
	Uart0_Init();
	
	while(1){
		U0THR='S';
		while(!U0LSR & (0X20));	// Waiting for transmission

	}
}


//	Send_string("Techno\r\n");	// Enter (newline )
//	Send_string("Scripts\r\n");




void Send_string(char *str)
{
	while(*str!='\0')
	{//    \0 != '\0'
		U0THR=*str;		// T
	 while(!(U0LSR & 0x20));	// waiting for tx
		str++;
	}
}





/*
#include <LPC214X.H>
void print(unsigned char *st);
void Tx(unsigned char ch);
void delay(int a);


void Uart0_Init(void){
	
	PINSEL0=0x05;
	U0LCR=0x83;				// 8 bits, no Parity 1 Stop bit
	U0DLL=0x61;				// 9600 B.R
	U0DLM=0x00;
	U0LCR=0x03;				// DLAB=0
}

void main(){

	Uart0_Init();
		delay(100000);
	while(1){
	
		print(" Money is ");
	//	lcd_cmd(0xc0);
				print(" Honey");

	}
}

void print(unsigned char *st){
	while(*st!='\0'){
		Tx(*st++);
	}
}
void Tx(unsigned char ch){
	U0THR=ch;
	while(!(U0LSR & 0x20));	// waiting for tx
}

void delay(int a){
	int i,j;
for(i=0; i<a; i++)
for(j=0; j<123; j++);
}
*/