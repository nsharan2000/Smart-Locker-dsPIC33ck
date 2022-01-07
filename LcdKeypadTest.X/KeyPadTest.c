/*
 * File:   KeyPadTest.c
 * Author: shara
 *
 * Created on 11 April, 2021, 1:49 AM
 */
// DSPIC33CK128MP506 Configuration Bit Settings

// 'C' source line config statements

//#pragma config ICS = 2

#pragma config ICS = PGD2               // ICD Communication Channel Select bits (Communicate on PGC2 and PGD2)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)
#pragma config NOBTSWP = DISABLED 

#pragma config FNOSC = PRI              // Oscillator Source Selection (Primary Oscillator (XT, HS, EC))
#pragma config IESO = OFF              // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC
#pragma config POSCMD = EC              // Primary Oscillator Mode Select bits (EC (External Clock) Mode)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)
#pragma config PLLKEN = OFF              // PLL Lock Status Control (PLL lock signal will be used to disable PLL clock output if lock is lost)
#pragma config XTCFG = G3               // XT Config (24-32 MHz crystals)
#pragma config XTBST = ENABLE           // XT Boost (Boost the kick-start)


#include <xc.h>
#include <libpic30.h>
//#include <stdio.h>
//#include <string.h>


/*
void delay(unsigned int j)
{
	unsigned int i=0;
	for(i=0;i<j;i++);
}
*/

/*
 Other Specific definition
 */





#define FCY 16000000UL //Crystal Frequency, used in delay
#define X_1    LATCbits.LATC1
#define X_2    LATCbits.LATC2
#define X_3    LATCbits.LATC6
#define X_4    LATCbits.LATC3
#define Y_1    PORTDbits.RD11
#define Y_2    PORTDbits.RD10
#define Y_3    PORTCbits.RC12
#define Y_4    PORTBbits.RB15
//#define Keypad_PORT          PORTB
//#define Keypad_PORT_Direction     TRISB   

void InitKeypad(void);
char switch_press_scan(void);
char keypad_scanner(void);
char switch_press_scan(void)                       // Get key from user
{
            char key = 'n';              // Assume no key pressed
            while(key=='n')              // Wait untill a key is pressed
            key = keypad_scanner();   // Scan the keys again and again
            return key;                  //when key pressed then return its value
}

char keypad_scanner(void)  
{          /* 
            X_1 = 0; X_2 = 1; X_3 = 1; X_4 = 1;    
            if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return '1'; }
            if (Y_2 == 0) { __delay_ms(100); while (Y_2==0); return '2'; }
            if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '3'; }
            if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return 'A'; }
            
            X_1 = 1; X_2 = 0; X_3 = 1; X_4 = 1;    
            if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return '4'; }
            if (Y_2 == 0) { __delay_ms(100); while (Y_2==0); return '5'; }
            if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '6'; }
            if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return 'B'; }
            
            X_1 = 1; X_2 = 1; X_3 = 0; X_4 = 1;    
            if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return '7'; }
            if (Y_2 == 0) { __delay_ms(100); while (Y_2==0); return '8'; }
            if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '9'; }
            if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return 'C'; }
           
            X_1 = 1; X_2 = 1; X_3 = 1; X_4 = 0;    
            if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return '*'; }
            if (Y_2 == 0) { __delay_ms(100); while (Y_2==0); return '0'; }
            if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '#'; }
            if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return 'D'; }
            */
    return 'n';                   
}

void InitKeypad(void)
{
            //Keypad_PORT                = 0x00;        // Set Keypad port pin values zero
            X_1=0;
            X_2=0;
            X_3=0;
            X_4=0;
            
            //Keypad_PORT_Direction = 0xF0;      // Last 4 pins input, First 4 pins output
            TRISCbits.TRISC1=1;
            TRISCbits.TRISC2=1;
            TRISCbits.TRISC6=1;
            TRISCbits.TRISC3=1;
            TRISDbits.TRISD11=0;
            TRISDbits.TRISD10=0;
            TRISCbits.TRISC12=0;
            TRISBbits.TRISB15=0;
            
            //OPTION_REG &= 0x7F;
}


void system_init(void);     

int main(void){    
    //system_init();
    
    int flag=0;
    char Key = 'n';
    TRISBbits.TRISB14=0;
    //LATBbits.LATB14=1;
    TRISCbits.TRISC9 = 0;
    LATCbits.LATC9 =0;
    //lcd_com(0x80);
    //lcd_puts("CircuitDigest");
    //lcd_com(0xC0);
    while(1){
        __delay_ms(100000);
        Key = switch_press_scan();
        //lcd_data(Key);
        if (Key=='2'){
            flag=1;
            LATBbits.LATB14=1;
            
        }
    }
    return (0);
}

/*
 *  System Init
 */

void system_init(void){
    //TRISD = 0x00;
    //lcd_init(); // This will initialise the lcd    
    InitKeypad();
}



