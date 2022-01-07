/*
 * File:   PassSysBack1.c
 * Author: shara
 *
 * Created on 11 April, 2021, 3:41 PM
 */


//#include<reg51.h>
#include "xc.h"
#include<string.h>

//Micro Define //?
//#define lcdport P2
#define D4 LATBbits.LATB12
#define D5 LATCbits.LATC15
#define D6 LATCbits.LATC14
#define D7 LATCbits.LATC13


//Pin configuaration for lcd-screen
#define RS LATCbits.LATC0 
#define RW LATDbits.LATD4 
#define EN LATDbits.LATD3

//Pin configuaration for servo-motor
#define EN LATBits.LATB8
#define EN LATBbits.LATB7

//Pin configuaration for Keypad: row
#define X_1    LATCbits.LATC1
#define X_2    LATCbits.LATC2
#define X_3    LATCbits.LATC6
#define X_4    LATCbits.LATC3


//Pin configuaration for Keypad: col
#define Y_1    PORTDbits.RD11
#define Y_2    PORTDbits.RD10
#define Y_3    PORTCbits.RC12
#define Y_4    PORTBbits.RB15
//Pin configuaration for Buzzer
#define buzzer    LATBbits.LATB2

#define m1    LATBbits.LATB8
#define m2    LATBbits.LATB7

//Globar Array Declaration for Storig Password
char uid[]="54321";
char id[5];

//Function declaration
void port_init(); //function to set the pin configuration
void lcdint(); // Function to initialize Lcd-Screen
void lcddis(char *); //Function to Display a string
void delay(int); //Delay Function
void lcdcmd(char); // Function to command Lcd
void lcddata(char); // Function to display a single character in screen
char lcdkey(); // Lcd Keyboard function
char scan_key(); //Function to take single key input
void door_open(); //Function to open door
void door_close(); //Function to close Door
void sounder(); // Function to Buzz sounder

void main(){
	port_init();
	int n;
	char key;
	
    //?
	P2=0x00; // Using Port 2 as output port
	P1=0xff; // Using Port 1  as input port
	
	lcdint(); //Intitializing LCD-Screen
	lcddis("Door is Locked");
	//lcdcmd(0xc0);
	//lcddis("Enter Passcode:");
	delay(100);
	lcdcmd(0x01);  //Clearing Display Screen
	lcdcmd(0x02);	//4bit mode for LCd-Screen
	lcddis("Enter Password:");
	lcdcmd(0xc0);	// Cursor beggining of second line
	n=0;
	while(n<5){
		key=scan_key();
		id[n]=key;
		//lcddata(key);
		delay(100);
		n++;
	}
	lcdcmd(0x01); //ClearingLCD-Screen
	lcdcmd(0x02);	// 4bit mode for LCD-Screen
	
    
    
	if(strcmp(uid,id)==0){
		lcddis("Password Matched");
		delay(200);
		door_open(); //openining door
		delay(600);
		door_close(); //closing door
		lcdcmd(0x01); //Clearing LCD-Screen
		lcdcmd(0x02);	//4bit mode for LCD-Screen
	}
	else{
		lcddis("Wrong Password");
		sounder();	//Buzzing Sounde
		delay(200);
		lcdcmd(0x01); //Clearing LCD-Screen
		lcdcmd(0x02);	//4bit mode for LCD-Screen
		lcddis("Please Try Again");
		delay(200);
		lcdcmd(0x01); //Clearing LCD-Screen
		lcdcmd(0x02);	//4bit mode for LCD-Screen
	}
}

void port_init(){
    TRISBbits.TRISB12 = 0;
    TRISCbits.TRISC15 = 0;
    TRISCbits.TRISC14 = 0;
    TRISCbits.TRISC13 = 0;
    //Pin configuaration for lcd-screen
    TRISCbits.TRISC0 = 0;//RS
    TRISDbits.TRISD4 = 0;//RW
    TRISDbits.TRISD3 = 0;//EN

    //Pin configuaration for servo-motor
    TRISBbits.TRISB8 = 0; //m1
    TRISBbits.TRISB7 = 0;//m2

    //Pin configuaration for Keypad: row
    TRISCbits.TRISC1 = 0;//X1
    TRISCbits.TRISC2 = 0;//X2
    TRISCbits.TRISC6 = 0;//X3
    TRISCbits.TRISC3 = 0;//X4


    //Pin configuaration for Keypad: col
    TRISDbits.TRISD11 = 1; //Y1
    TRISDbits.TRISD10 = 1; //Y2
    TRISCbits.TRISC12 = 1; //Y3
    TRISBbits.TRISB15 = 1; //Y4
    
    //Pin configuaration for Buzzer
    TRISBbits.TRISB2 = 0;//BUZZER
}



void Lcd_SetBit(char data_bit) //Based on the Hex value Set the Bits of the Data Lines
{
    if(data_bit& 1) 
        D4 = 1;
    else
        D4 = 0;

    if(data_bit& 2)
        D5 = 1;
    else
        D5 = 0;

    if(data_bit& 4)
        D6 = 1;
    else
        D6 = 0;

    if(data_bit& 8) 
        D7 = 1;
    else
        D7 = 0;
}

//Lcd-Screen Initialization Function

void Lcd_Clear(){
	lcdcmd(0x38);	//  lcd initialize matrix 8bit
	delay(2);
	lcdcmd(0x01);	// Clearing Lcd-Screen
	delay(2);
	lcdcmd(0x80);	// lcd screen row-0 col-0
	delay(2);
	lcdcmd(0x0e);	//Display cursor blinking
	delay(2);
}
//setting cursor function-new
void Lcd_Set_Cursor(char a, char b)
{
    char temp,z,y;
    if(a== 1)
    {
      temp = 0x80 + b - 1; //80H is used to move the curser
        z = temp>>4; //Lower 8-bits
        y = temp & 0x0F; //Upper 8-bits
        Lcd_Cmd(z); //Set Row
        Lcd_Cmd(y); //Set Column
    }
    else if(a== 2)
    {
        temp = 0xC0 + b - 1;
        z = temp>>4; //Lower 8-bits
        y = temp & 0x0F; //Upper 8-bits
        Lcd_Cmd(z); //Set Row
        Lcd_Cmd(y); //Set Column
    }
}

//start lcd
void Lcd_Start()
{
  Lcd_SetBit(0x00);
  for(int i=1065244; i<=0; i--)  NOP();  
  Lcd_Cmd(0x03);
    __delay_ms(5);
  Lcd_Cmd(0x03);
    __delay_ms(11);
  Lcd_Cmd(0x03); 
  Lcd_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  Lcd_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  Lcd_Cmd(0x08); //Select Row 1
  Lcd_Cmd(0x00); //Clear Row 1 Display
  Lcd_Cmd(0x0C); //Select Row 2
  Lcd_Cmd(0x00); //Clear Row 2 Display
  Lcd_Cmd(0x06);
}


//Delay Function
void delay(int x)
{
	int i,j;
	for(i=0;i<x;i++)
	for(j=0;j<1275;j++);
}
//Lcd-Command Function
void Lcd_Cmd(char a)
{
    RS = 0;           
    Lcd_SetBit(a); //Incoming Hex value
    EN  = 1;         
        __delay_ms(4);
        EN  = 0;         
}
//Lcd-Display String Function
void Lcd_Print_String(char *a)
{
    int i;
    for(i=0;a[i]!='\0';i++)
       Lcd_Print_Char(a[i]);  //Split the string using pointers and call the Char function 
}

//Lcd-Data Function to Send Char to Lcd Data port
void Lcd_Print_Char(char data)  //Send 8-bits through 4-bit mode
{
   char Lower_Nibble,Upper_Nibble;
   Lower_Nibble = data&0x0F;
   Upper_Nibble = data&0xF0;
   RS = 1;             // => RS = 1
   Lcd_SetBit(Upper_Nibble>>4);             //Send upper half by shifting by 4
   EN = 1;
   for(int i=2130483; i<=0; i--)  NOP(); 
   EN = 0;
   Lcd_SetBit(Lower_Nibble); //Send Lower half
   EN = 1;
   for(int i=2130483; i<=0; i--)  NOP();
   EN = 0;
}

// Buzzer Function
void sounder(){
	int i;
	for(i=0;i<5;i++){
		buzzer=1; //buzzer on
		delay(100);
		buzzer=0; //buzzer off
        buzzer=1; //buzzer on
		delay(100);
		buzzer=0; //buzzer off
        buzzer=1; //buzzer on
		delay(100);
		buzzer=0; //buzzer off
        buzzer=1; //buzzer on
		delay(100);
		buzzer=0; //buzzer off
	}
}
//Function to Open Door
void door_open(){
	lcdcmd(0x01); //Clearing LCD-Screen
	lcdcmd(0x02); //4bit mode for LCD-Screen
	lcddis("Opening Door...");
	m1=1; //Motor on
	m2=0; //motor off
}
//Function to Close Door
void door_close(){
	lcdcmd(0x01); 
	lcdcmd(0x02);
	lcddis("Closing Door...");
	m1=0;
	m2=0;
	delay(20);
	//m1=1;
	//m2=0;
	m1=0;
	m2=1;
	delay(500);
	m1=0;
	m2=0;
}
//Dunction to scan single Key and return it to main Function
char keypad_scanner(void)  
{          
            X_1 = 0; X_2 = 1; X_3 = 1; X_4 = 1;    
            if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return '1'; 
            }
            if (Y_2 == 0) { __delay_ms(100); while (Y_2==0); return '2'; 
            }
            if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '3'; 
            }
            if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return 'A'; 
            }
            
            X_1 = 1; X_2 = 0; X_3 = 1; X_4 = 1;    
            if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return '4'; 
            }
            if (Y_2 == 0) { __delay_ms(100); while (Y_2==0); return '5'; 
            }
            if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '6'; 
            }
            if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return 'B'; 
            }
            
            X_1 = 1; X_2 = 1; X_3 = 0; X_4 = 1;    
            if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return '7'; 
            }
            if (Y_2 == 0) { __delay_s(100); while (Y_2==0); return '8'; 
            }
            if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '9'; 
            }
            if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return 'C'; 
            }
           
            X_1 = 1; X_2 = 1; X_3 = 1; X_4 = 0;    
            if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return '*'; 
            }
            if (Y_2 == 0) { __delay_ms(100); while (Y_2==0); return '0'; 
            }
            if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '#'; 
            }
            if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return 'D'; 
            }
            
    return 'n';                   
}