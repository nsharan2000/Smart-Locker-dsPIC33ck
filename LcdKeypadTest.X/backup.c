/*
 * File:   backup.c
 * Author: shara
 *
 * Created on 15 April, 2021, 6:51 PM
 */


#pragma config ICS = 0b10 //ICS is set properly pgd2

// 'C' source line config statements

// FSEC
#pragma config BWRP = OFF               // Boot Segment Write-Protect bit (Boot Segment may be written)
#pragma config BSS = DISABLED           // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSEN = OFF               // Boot Segment Control bit (No Boot Segment)
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = DISABLED           // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP = OFF               // Configuration Segment Write-Protect bit (Configuration Segment may be written)
#pragma config CSS = DISABLED           // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = OFF            // Alternate Interrupt Vector Table bit (Disabled AIVT)

// FBSLIM
#pragma config BSLIM = 0x1FFF           // Boot Segment Flash Page Address Limit bits (Enter Hexadecimal value)

// FSIGN

// FOSCSEL
#pragma config FNOSC = PRI              // Oscillator Source Selection (Primary Oscillator (XT, HS, EC))
#pragma config IESO = OFF              // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC
#pragma config POSCMD = HS             // Primary Oscillator Mode Select bits (EC (External Clock) Mode)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)
#pragma config PLLKEN = OFF              // PLL Lock Status Control (PLL lock signal will be used to disable PLL clock output if lock is lost)
#pragma config XTCFG = G3               // XT Config (24-32 MHz crystals)
#pragma config XTBST = ENABLE           // XT Boost (Boost the kick-start)

// FWDT
// RWDTPS = No Setting
#pragma config RCLKSEL = LPRC           // Watchdog Timer Clock Select bits (Always use LPRC)
#pragma config WINDIS = ON              // Watchdog Timer Window Enable bit (Watchdog Timer operates in Non-Window mode)
#pragma config WDTWIN = WIN25           // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
// SWDTPS = No Setting
#pragma config FWDTEN = ON              // Watchdog Timer Enable bit (WDT enabled in hardware)

// FPOR
#pragma config BISTDIS = DISABLED       // Memory BIST Feature Disable (mBIST on reset feature disabled)

// FICD
//#pragma config ICS = PGD2               // ICD Communication Channel Select bits (Communicate on PGC2 and PGD2)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)
#pragma config NOBTSWP = DISABLED       // BOOTSWP instruction disable bit (BOOTSWP instruction is disabled)

// FDMTIVTL
#pragma config DMTIVTL = 0xFFFF         // Dead Man Timer Interval low word (Enter Hexadecimal value)

// FDMTIVTH
#pragma config DMTIVTH = 0xFFFF         // Dead Man Timer Interval high word (Enter Hexadecimal value)

// FDMTCNTL
#pragma config DMTCNTL = 0xFFFF         // Lower 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)

// FDMTCNTH
#pragma config DMTCNTH = 0xFFFF         // Upper 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)

// FDMT
#pragma config DMTDIS = OFF             // Dead Man Timer Disable bit (Dead Man Timer is Disabled and can be enabled by software)

// FDEVOPT
#pragma config ALTI2C1 = OFF            // Alternate I2C1 Pin bit (I2C1 mapped to SDA1/SCL1 pins)
#pragma config ALTI2C2 = OFF            // Alternate I2C2 Pin bit (I2C2 mapped to SDA2/SCL2 pins)
#pragma config ALTI2C3 = OFF            // Alternate I2C3 Pin bit (I2C3 mapped to SDA3/SCL3 pins)
#pragma config SMBEN = SMBUS            // SM Bus Enable (SMBus input threshold is enabled)
#pragma config SPI2PIN = PPS            // SPI2 Pin Select bit (SPI2 uses I/O remap (PPS) pins)

// FALTREG
#pragma config CTXT1 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits (Not Assigned)
#pragma config CTXT2 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits (Not Assigned)
#pragma config CTXT3 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 3 bits (Not Assigned)
#pragma config CTXT4 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 4 bits (Not Assigned)

// FBTSEQ
#pragma config BSEQ = 0xFFF             // Relative value defining which partition will be active after device Reset; the partition containing a lower boot number will be active (Enter Hexadecimal value)
#pragma config IBSEQ = 0xFFF            // The one's complement of BSEQ; must be calculated by the user and written during device programming. (Enter Hexadecimal value)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include "xc.h"
#include<string.h>
#include <libpic30.h>

#define FCY 16000000UL

//Micro Define 
//Pin configuaration for lcd-screen data pins
#define D4 LATBbits.LATB12
#define D5 LATCbits.LATC15
#define D6 LATCbits.LATC14
#define D7 LATCbits.LATC13


//Pin configuaration for lcd-screen control pins
#define RS LATCbits.LATC0 
#define RW LATDbits.LATD4 
#define EN LATDbits.LATD3

//Pin configuaration for servo-motor
#define m1 LATBbits.LATB8
#define m2 LATBbits.LATB7

//Pin configuaration for Keypad: row
#define X_1    LATCbits.LATC1
#define X_2    LATCbits.LATC2
#define X_3    LATCbits.LATC6
#define X_4    LATCbits.LATC3


//Pin configuaration for Keypad: col
#define Y_1    PORTCbits.RC12
#define Y_2    PORTBbits.RB15
#define Y_3    PORTBbits.RB14
#define Y_4    PORTBbits.RB13

//pin for lock representation
#define green  LATBbits.LATB9
#define red  LATBbits.LATB8

//Pin configuaration for Buzzer
#define buzzer LATBbits.LATB2

//Pin configuration for reset button
#define rst   PORTCbits.RC9

void change_password(void);
int n=0;
char key;
int tries =0;
char masterpass[]="123456";
char password[6];
int rp=1;

void delay1(int a)
{
   int c, d;
   
   for (c = 1; c <= a; c++)
       for (d = 1; d <= 10000; d++)
       {}     
}
//LCD Functions Developed by Circuit Digest.
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

void Lcd_Cmd(char a)
{
    RS = 0;  
    Lcd_SetBit(a); //Incoming Hex value
    EN  = 1;         
    delay1(3);
    EN  = 0;         
}

void Lcd_Clear()
{
    Lcd_Cmd(0); //Clear the LCD
    Lcd_Cmd(1); //Move the cursor to first position
}

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

void Lcd_Start()
{
  Lcd_SetBit(0x00);
  //for(int i=1065244; i<=0; i--)  NOP(); 
  //delay1(107);
  delay1(3);
  Lcd_Cmd(0x03);
  delay1(3);
  Lcd_Cmd(0x03);
  delay1(3);
  Lcd_Cmd(0x03); 
  Lcd_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  Lcd_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
  Lcd_Cmd(0x08); //Select Row 1
  Lcd_Cmd(0x00); //Clear Row 1 Display
  Lcd_Cmd(0x0C); //Select Row 2
  Lcd_Cmd(0x00); //Clear Row 2 Display
  Lcd_Cmd(0x06);
}

void Lcd_Print_Char(char data)  //Send 8-bits through 4-bit mode
{
   char Lower_Nibble,Upper_Nibble;
   Lower_Nibble = data&0x0F;
   Upper_Nibble = data&0xF0;
   RS = 1;             // => RS = 1
   Lcd_SetBit(Upper_Nibble>>4);             //Send upper half by shifting by 4
   EN = 1;
   //for(int i=2130483; i<=0; i--)  NOP(); 
   //delay1(250);
   delay1(10);
   EN = 0;
   Lcd_SetBit(Lower_Nibble); //Send Lower half
   EN = 1;
   //for(int i=2130483; i<=0; i--)  NOP();
   delay1(10);
   //delay1(250);
   EN = 0;
}

void Lcd_Print_String(char *a)
{
    int i;
    for(i=0;a[i]!='\0';i++)
       Lcd_Print_Char(a[i]);  //Split the string using pointers and call the Char function 
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
    TRISCbits.TRISC12 = 1; //Y1
    TRISBbits.TRISB15 = 1; //Y2
    TRISBbits.TRISB14 = 1; //Y3
    TRISBbits.TRISB13 = 1; //Y4
    
  
    //enable internal pull up resistors for the following read  pins
    CNPUCbits.CNPUC12 = 1; //Y1
    CNPUBbits.CNPUB15 = 1; //Y2
    CNPUBbits.CNPUB14 = 1; //Y3
    CNPUBbits.CNPUB13 = 1; //Y4
    
    CNPUCbits.CNPUC9 = 1; //BUZZER
    
    //pin CONFIG for lock representation
    TRISBbits.TRISB9 =0;
    TRISBbits.TRISB8 =0;
    
    
    //Pin configuration for Buzzer
    TRISBbits.TRISB2 = 0;//BUZZER
    
    TRISCbits.TRISC9 = 1; //reset
        
    
    RW = 0;
}

char keypad_scanner(void)  
{           if(rst==0&&rp==1) {change_password();}
            X_1 = 0; X_2 = 1; X_3 = 1; X_4 = 1;    
            if (Y_1 == 0) { delay1(1); while (Y_1==0); return '1'; 
            }
            if (Y_2 == 0) { delay1(1); while (Y_2==0); return '2'; 
            }
            if (Y_3 == 0) { delay1(1); while (Y_3==0); return '3'; 
            }
            if (Y_4 == 0) { delay1(1); while (Y_4==0); return 'A'; 
            }
            
            X_1 = 1; X_2 = 0; X_3 = 1; X_4 = 1;    
            if (Y_1 == 0) { delay1(1); while (Y_1==0); return '4'; 
            }
            if (Y_2 == 0) { delay1(1); while (Y_2==0); return '5'; 
            }
            if (Y_3 == 0) { delay1(1); while (Y_3==0); return '6'; 
            }
            if (Y_4 == 0) { delay1(1); while (Y_4==0); return 'B'; 
            }
            
            X_1 = 1; X_2 = 1; X_3 = 0; X_4 = 1;    
            if (Y_1 == 0) { delay1(1); while (Y_1==0); return '7'; 
            }
            if (Y_2 == 0) { delay1(1); while (Y_2==0); return '8'; 
            }
            if (Y_3 == 0) { delay1(1); while (Y_3==0); return '9'; 
            }
            if (Y_4 == 0) { delay1(1); while (Y_4==0); return 'C'; 
            }
           
            X_1 = 1; X_2 = 1; X_3 = 1; X_4 = 0;    
            if (Y_1 == 0) { delay1(1); while (Y_1==0); return '*'; 
            }
            if (Y_2 == 0) { delay1(1); while (Y_2==0); return '0'; 
            }
            if (Y_3 == 0) { delay1(1); while (Y_3==0); return '#'; 
            }
            if (Y_4 == 0) { delay1(1); while (Y_4==0); return 'D'; 
            }
            
    return 'n';                   
}




// Buzzer Function
void sounder(){
	int i;
	for(i=0;i<4;i++){
		buzzer=1; //buzzer on
		delay1(35);
		buzzer=0; //buzzer off
        delay1(35);
	}
}
//Function to Open Door
void door_open(){
    green=1;
    red=0;
	Lcd_Clear();
	Lcd_Print_String("Opening Door...");
	m1=1; //Motor on
	m2=0; //motor off
    
}
//Function to Close Door
void door_close(){
	green=0;
    red=1;
	Lcd_Print_String("Closing Door...");
	m1=0;
	m2=0;
	delay1(2);
	//m1=1;
	//m2=0;
	m1=0;
	m2=1;
	delay1(5);
	m1=0;
	m2=0;
}

char switch_press_scan(void)                       // Get key from user
{
            char key = 'n';              // Assume no key pressed
            while(key=='n')              // Wait until a key is pressed
            key = keypad_scanner();   // Scan the keys again and again
            return key;                  //when key pressed then return its value
}



void change_password(void)
{
    Lcd_Clear();
    delay1(5);
    Lcd_Set_Cursor(1,1);
    Lcd_Print_String("reset new");
    Lcd_Set_Cursor(2,1);
    Lcd_Print_String("password!");
    delay1(100);
    
    Lcd_Clear();
    delay1(5);
    Lcd_Set_Cursor(1,1);
    Lcd_Print_String("New Password:");
    Lcd_Set_Cursor(2,1);
    n=0;
    rp=0;
    //__delay_ms(1000);
    
    while(n<6){
        key=switch_press_scan();
        masterpass[n]=key;
        Lcd_Print_Char(key);
        delay1(2);
        n++;
    } 
    masterpass[6]='\0';
    rp=1;
    Lcd_Clear();
    Lcd_Print_String("password reset");
    Lcd_Set_Cursor(2,1);
    Lcd_Print_String("done!!");
    delay1(300);
    Lcd_Clear();
    n=0;
}

int main(void)
{
    //unsigned int a;
    

    
    port_init();
    Lcd_Start();
    Lcd_Print_String("WELCOME");
    delay1(20);
    
    while(1)
    {   green=0;
        red=1;
        Lcd_Clear();
        delay1(5);
        Lcd_Set_Cursor(1,1);
        Lcd_Print_String("Enter Password:");
        Lcd_Set_Cursor(2,1);
        delay1(3);
        n=0;
        //__delay_ms(1000);
        while(n<6){
            key=switch_press_scan();
            password[n]=key;
            Lcd_Print_Char(key);
            delay1(2);
            n++;
        }
        password[6]='\0';
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Print_String("...");
        delay1(6);
        Lcd_Clear();
        delay1(30);
        

        if(strcmp(password,masterpass)==0){
            Lcd_Clear();
            delay1(6);
            Lcd_Print_String("Password Matched");
            delay1(20);
            Lcd_Clear();
            door_open(); //opening door
            delay1(100);
            Lcd_Clear();
            door_close(); //closing door
            tries=0;
            Lcd_Clear();   
        }
        else{
            Lcd_Clear();
            Lcd_Print_String("Wrong Password");
            sounder();	//Buzzing Sounds
            delay1(8);
            tries+=1;
            if (tries>=2){
                Lcd_Clear();
                Lcd_Print_String("Too many tries!");
                while(rst==1){
                sounder();	//Buzzing Sounds
                }
                Lcd_Clear();
                Lcd_Print_String("System Reset");
                Lcd_Set_Cursor(2,1);
                Lcd_Print_String("Done!!!");
                delay1(6);
                Lcd_Clear();
                tries=0;
            }
            else{
                Lcd_Clear(); //Clearing LCD-Screen
                Lcd_Print_String("Please Try Again");
                delay1(6);
                Lcd_Clear();
            }
        }



    }
    return 0;
}

