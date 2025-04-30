#include <LPC214X.H>
#define led 1<<15

void init_uart0(void);
unsigned char getkey (void);
void pll();

int main()
{
unsigned char ch;
	IO0DIR=led;
PINSEL0 = 0X00000005;
init_uart0();
	pll();

while(1)
{
	ch=getkey(); 
switch (ch)
 {
 case '1':
	IO0SET=led;
  break;
 case '0':
		IO0CLR=led;
		break;
 }
}
}

void init_uart0()
{
//U0FCR = 0X07;
U0LCR = 0X83;
U0DLL = 0X61;
U0DLM = 0X00;
U0LCR = 0X03;
}

unsigned char getkey (void) 
{                    			// Read character from Serial Port   
  while (!(U0LSR & 0x01));              // wait until character ready        
  return (U0RBR);
}

void pll()           
       //Fosc=12Mhz,CCLK=60Mhz,PCLK=60MHz
{
    PLL0CON=0x01;
    PLL0CFG=0x24;
    PLL0FEED=0xAA;
    PLL0FEED=0x55;
    while(!(PLL0STAT & (1<<10)));
    PLL0CON=0x03;
    PLL0FEED=0xAA;
    PLL0FEED=0x55;
    VPBDIV=0x00;
}
