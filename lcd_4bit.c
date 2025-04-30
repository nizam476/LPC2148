#include<lpc214x.h>

#define RS  0x00020000              /* RS  - P1.17   1<<17   */
#define RW  0X00040000              /* R/W - P1.18   1<<18   */    
#define EN  0X00080000              /* E   - P1.19   1<<19    */
#define CLR 0X00FE0000
 
int Delay(unsigned int x){
 x=x*8000;
 while(x!=0){
  x--;
 }
 return 0;
}


void LCD_Command1(char command1){		// 28
 int Temp;
 IO1CLR = CLR;                      /* Clearing the port pins               */
 IO1SET = EN;                       /* Enable pin high                      */
 IO1CLR = RS;                       /* RS=0 for command register            */
 IO1CLR = RW;                       /* R/W=0 for write                      */
 Temp   = (command1 & 0xF0);        /* Taking the first nibble of command   */
 Temp   = Temp << 16;               /* Shift it 16 bits to left             */
 IO1SET = IO1SET | Temp;            /* Writing it to data line(P1.20-P1.23) */
 Delay(2);
 IO1CLR = EN;                       /* Enable pin low to give H-L pulse     */
 
 IO1CLR = CLR;                      /* Clearing the port pins               */
 IO1SET = EN;                       /* Enable pin high                      */
 IO1CLR = RS;                       /* RS=0 for command register            */
 IO1CLR = RW;                       /* R/W=0 for write                      */
 Temp   = (command1 & 0x0F);        /* Taking the second nibble of command  */
 Temp   = Temp << 20;               /* Shift it 20 bits to left             */
 IO1SET = IO1SET | Temp;            /* Writing it to data line              */
 Delay(2);
 IO1CLR = EN;                       /* Enable pin low to give H-L pulse     */
}

 void LCD_Data(char data)  {
 int Temp;
 IO1CLR = CLR;                      /* Clearing the port pins               */
 IO1SET = EN;                       /* Enable pin high                      */
 IO1SET = RS;                       /* RS=1 for data register               */
 IO1CLR = RW;                       /* R/W=0 for write                      */
 Temp   = (data & 0xF0);            /* Taking the first nibble of data      */
 Temp   = Temp << 16;               /* Shift it 16 bits to left             */
 IO1SET = IO1SET | Temp;            /* Writing it to data line              */
 Delay(2);
 IO1CLR = EN;                       /* Enable pin low to give H-L pulse     */
 
 IO1CLR = CLR;                      /* Clearing the port pins               */
 IO1SET = EN;                       /* Enable pin high                      */
 IO1SET = RS;                       /* RS=1 for data register               */
 IO1CLR = RW;                       /* R/W=0 for write                      */
 Temp   = (data & 0x0F);            /* Taking the second nibble of data     */
 Temp   = Temp << 20;               /* Shift it 20 bits to left             */
 IO1SET = IO1SET | Temp;            /* Writing it to data line              */
 Delay(2);
 IO1CLR = EN;                       /* Enable pin low to give H-L pulse     */
}
 
void LCD_String(unsigned char *dat){
 while(*dat!='\0')                  /* Check for termination character      */
 {
  LCD_Data(*dat);                   /* Display the character on LCD         */
  dat++;                            /* Increment the pointer                */
 }
}
 
void LCD_Init(void){
 
	Delay(15);

 LCD_Command1(0x02);								// 4 bit Mode
 LCD_Command1(0x28);								// 5x7 Matrix
 LCD_Command1(0x01);
	/* Clear display       */
 LCD_Command1(0x06);                /* Auto increment      */
 //LCD_Command1(0x0E);								//Display on Cursor ON
	LCD_Command1(0x0C);
}



int main(){
 IO1DIR  = 0x00FE0000;          /* LCD pins set as o/p  Initialize port   */
 LCD_Init();                        /* Initialize LCD                       */
 LCD_String("   Embedded   ");
 LCD_Command1(0xC0);                /* 2nd row, 1st location                */
 LCD_String("   System    ");
 while(1);
	
}





















// LCD_Command(0x30);				// 8 bit Mode
// Delay(10);    
// LCD_Command(0x30);
// Delay(5);    
// LCD_Command(0x30);

// LCD_Command(0x20);							// 4 bit Mode





//void LCD_Command(char command){ // 20
// int Temp;                           
// IO1CLR = CLR;                      /* Clearing the port pins               */
// IO1SET = EN;                       /* Enable pin high                      */
// IO1CLR = RS;                       /* RS=0 for command register            */
// IO1CLR = RW;                       /* R/W=0 for write                      */
// Temp   = (command & 0xF0) << 16;   /* Taking the first nibble of command   */
// IO1SET = IO1SET | Temp;            /* Writing it to data line              */
// Delay(2);
// IO1CLR = EN;                       /* Enable pin low to give H-L pulse     */
//}
