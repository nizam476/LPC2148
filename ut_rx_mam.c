#include <LPC214X.H>

void init_uart0(void);
void tx(unsigned char);
unsigned char getkey(void);
void print(unsigned char *);
//------------------------------
int main()
{
unsigned char ch;
//VPBDIV = 0X00;
PINSEL0 = 0X00000005;
init_uart0();
print("Press Any Key from menu........\n");
print("A)RUPALI\n");
print("B)WANKHEDE\n");

while(1)
{
ch=getkey();
 switch (ch)
 {
 case 'A':
  print("\n RUPALI");
  break;
 case 'B':
  print("\n WANKHEDE");
  break;
 
 }
}
}
//----------------------------
void init_uart0()
{
U0FCR = 0X07;
U0LCR = 0X83;
U0DLL = 0X61;
U0DLM = 0X00;
U0LCR = 0X03;
}
//------------------------------
void print(unsigned char *msg)
{
  while(*msg!='\0')
  {
    if(*msg=='\n')
   {
  tx('\r');
  }
   tx(*msg);
 msg++;
  }
}
//-------------------------------
void tx(unsigned char value)
{
while(!(U0LSR & 0x20));
U0THR =  value;
}
//------------------------------
unsigned char getkey (void) 
{                    /* Read character from Serial Port   */
  while (!(U0LSR & 0x01));              /* wait until character ready        */
  return (U0RBR);
}
