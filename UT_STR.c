
#include <LPC214X.H>
void initPLL(void);
void Tx(unsigned char ch);

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
VPBDIV=0x00;								// SET PCLK AS 1/4th (15Mhz)
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

void Uart0_Init(void){
	
	PINSEL0=0x05;			// Configure the TX & RX pins
	U0LCR=0x83;				// 8 bits, no Parity 1 Stop bit, dlab=1
	U0DLL=0x61;				// 9600 B.R
	U0DLM=0x00;
	U0LCR=0x03;				// DLAB=0
}

int main(){
  initPLL();
	Uart0_Init();
	
	while(1){
		print("Welcome");
		print("\n\r");
	}
}
/*

#include <LPC214X.H>
void initPLL(void);
void Tx(unsigned char ch);

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
VPBDIV=0x00;								// SET PCLK AS 1/4th (15Mhz)
}

void print(unsigned char *st){
	while(*st!='\0'){
		U0THR=*st++;
			while(!(U0LSR & 0x20));	// waiting for tx	
	}
}
//void Tx(unsigned char ch){
//	U0THR=ch;
//	while(!(U0LSR & 0x20));	// waiting for tx
//}

void Uart0_Init(void){
	
	PINSEL0=0x05;			// Configure the TX & RX pins
	U0LCR=0x83;				// 8 bits, no Parity 1 Stop bit, dlab=1
	U0DLL=0x61;				// 9600 B.R
	U0DLM=0x00;
	U0LCR=0x03;				// DLAB=0
}

int main(){
  initPLL();
	Uart0_Init();
	
	while(1){
		print("uart");
		print("\n\r");
	}
}
*/