/*
 * File:   HEXTEST.c
 * Author: shara
 *
 * Created on 14 April, 2021, 9:57 PM
 */

//#pragma config ICS = 0b10 //ICS is set properly pgd2
//
//// 'C' source line config statements
//
//// FSEC
//#pragma config BWRP = OFF               // Boot Segment Write-Protect bit (Boot Segment may be written)
//#pragma config BSS = DISABLED           // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
//#pragma config BSEN = OFF               // Boot Segment Control bit (No Boot Segment)
//#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
//#pragma config GSS = DISABLED           // General Segment Code-Protect Level bits (No Protection (other than GWRP))
//#pragma config CWRP = OFF               // Configuration Segment Write-Protect bit (Configuration Segment may be written)
//#pragma config CSS = DISABLED           // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
//#pragma config AIVTDIS = OFF            // Alternate Interrupt Vector Table bit (Disabled AIVT)
//
//// FBSLIM
//#pragma config BSLIM = 0x1FFF           // Boot Segment Flash Page Address Limit bits (Enter Hexadecimal value)
//
//// FSIGN
//
//// FOSCSEL
//#pragma config FNOSC = PRI              // Oscillator Source Selection (Primary Oscillator (XT, HS, EC))
//#pragma config IESO = OFF              // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)
//
//// FOSC
//#pragma config POSCMD = HS             // Primary Oscillator Mode Select bits (EC (External Clock) Mode)
//#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
//#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)
//#pragma config PLLKEN = OFF              // PLL Lock Status Control (PLL lock signal will be used to disable PLL clock output if lock is lost)
//#pragma config XTCFG = G3               // XT Config (24-32 MHz crystals)
//#pragma config XTBST = ENABLE           // XT Boost (Boost the kick-start)
//
//// FWDT
//// RWDTPS = No Setting
//#pragma config RCLKSEL = LPRC           // Watchdog Timer Clock Select bits (Always use LPRC)
//#pragma config WINDIS = ON              // Watchdog Timer Window Enable bit (Watchdog Timer operates in Non-Window mode)
//#pragma config WDTWIN = WIN25           // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
//// SWDTPS = No Setting
//#pragma config FWDTEN = ON              // Watchdog Timer Enable bit (WDT enabled in hardware)
//
//// FPOR
//#pragma config BISTDIS = DISABLED       // Memory BIST Feature Disable (mBIST on reset feature disabled)
//
//// FICD
////#pragma config ICS = PGD2               // ICD Communication Channel Select bits (Communicate on PGC2 and PGD2)
//#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)
//#pragma config NOBTSWP = DISABLED       // BOOTSWP instruction disable bit (BOOTSWP instruction is disabled)
//
//// FDMTIVTL
//#pragma config DMTIVTL = 0xFFFF         // Dead Man Timer Interval low word (Enter Hexadecimal value)
//
//// FDMTIVTH
//#pragma config DMTIVTH = 0xFFFF         // Dead Man Timer Interval high word (Enter Hexadecimal value)
//
//// FDMTCNTL
//#pragma config DMTCNTL = 0xFFFF         // Lower 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)
//
//// FDMTCNTH
//#pragma config DMTCNTH = 0xFFFF         // Upper 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)
//
//// FDMT
//#pragma config DMTDIS = OFF             // Dead Man Timer Disable bit (Dead Man Timer is Disabled and can be enabled by software)
//
//// FDEVOPT
//#pragma config ALTI2C1 = OFF            // Alternate I2C1 Pin bit (I2C1 mapped to SDA1/SCL1 pins)
//#pragma config ALTI2C2 = OFF            // Alternate I2C2 Pin bit (I2C2 mapped to SDA2/SCL2 pins)
//#pragma config ALTI2C3 = OFF            // Alternate I2C3 Pin bit (I2C3 mapped to SDA3/SCL3 pins)
//#pragma config SMBEN = SMBUS            // SM Bus Enable (SMBus input threshold is enabled)
//#pragma config SPI2PIN = PPS            // SPI2 Pin Select bit (SPI2 uses I/O remap (PPS) pins)
//
//// FALTREG
//#pragma config CTXT1 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits (Not Assigned)
//#pragma config CTXT2 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits (Not Assigned)
//#pragma config CTXT3 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 3 bits (Not Assigned)
//#pragma config CTXT4 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 4 bits (Not Assigned)
//
//// FBTSEQ
//#pragma config BSEQ = 0xFFF             // Relative value defining which partition will be active after device Reset; the partition containing a lower boot number will be active (Enter Hexadecimal value)
//#pragma config IBSEQ = 0xFFF            // The one's complement of BSEQ; must be calculated by the user and written during device programming. (Enter Hexadecimal value)
//
//// #pragma config statements should precede project file includes.
//// Use project enums instead of #define for ON and OFF.


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

//Pin configuaration for Buzzer
#define buzzer LATBbits.LATB2

//Pin configuration for reset button
#define rst   PORTBbits.RB9

//Pin configuaration for debugging
#define dbg1 LATCbits.LATC9
#define dbg2 LATCbits.LATC8


void delay1(int a)
{
   int c, d;
   
   for (c = 1; c <= a; c++)
       for (d = 1; d <= 10000; d++)
       {}     
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
    
  
    //enable internal pull up resistors for the following read 
    CNPUCbits.CNPUC12 = 1; //Y1
    CNPUBbits.CNPUB15 = 1; //Y2
    CNPUBbits.CNPUB14 = 1; //Y3
    CNPUBbits.CNPUB13 = 1; //Y4
    
    
    //Pin configuaration for Buzzer
    TRISBbits.TRISB2 = 0;//BUZZER
    
    TRISBbits.TRISB9 = 1; //reset
    
    //Pin configuaration for debugging
    TRISCbits.TRISC9 =0;
    TRISCbits.TRISC8 =0;
    RW = 0;
}

int main()
{ 
    port_init();
    while(1)
    {
       X_1 = 0; X_2 = 1; X_3 = 0; X_4 = 1; 
       if(Y_2 == 1){
           dbg1 =1;
           delay1(1000);
           dbg1 =0;
           
       }
       if(Y_2 == 0){
           dbg2 =1;
           delay1(1000);
           dbg2 =0;
       }
        }
        

    return 0;
}