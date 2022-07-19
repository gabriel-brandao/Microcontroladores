
// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = INTOSC_HS // Oscillator Selection bits (Internal oscillator, HS oscillator used by USB (INTHS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF         // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 256      // Watchdog Timer Postscale Select bits (1:256)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "lcdi2c.h"

#include <pic18f4550.h>
#include <stdio.h>

int esq, dir;
int minutos;
int segundos;

void escreve_LCD (int numero){
    
    if(numero < 10){
        LCD_Write_Convert_String(0);
        dir = numero % 10;
        LCD_Write_Convert_String(dir);
    }
        
    else{
        esq = numero / 10;
        dir = numero % 10;
        
        LCD_Write_Convert_String(esq);
        LCD_Write_Convert_String(dir);
    }

}

void main(void) {
    minutos = 0;
    segundos = 0;
    
    I2C_Master_Init();
    LCD_Init(0x4E);
    LCD_Set_Cursor(1,1);
    
    
    
    
    
    
     //LCD_Write_Convert_String(6);
     
     //LCD_Write_Convert_String(segundos);
    
   /* RCONbits.IPEN = 1; //ativando as prioridades de interrupção
    INTCONbits.GIEH = 1; //ativando as interrupções de alta prioridades
    INTCONbits.GIEL = 0; //desativando as interrupções de baixa prioridades
    INTCONbits.TMR0IF = 0; //limpar flag da interrupção TMR0
    INTCONbits.TMR0IE = 1; //habilita a interrupção TMR0
    INTCON2bits.TMR0IP = 1; //TMR0 como alta prioridade
    
    
    
    
    T0CON = 0b10000011; //configura TIMER0com preescaler 1:16 e 16 bits clock interno
    
    //configurar portas de saída
    TRISB = 0x00; //configura se é entrada ou saída
    PORTB = 0x00; //valor de inicialização 
    
    TRISD = 0x00; //configura se é entrada ou saída
    PORTD = 0x00; //valor de inicialização 
    
    WRITETIMER0(3036); //configura TIMER0 com preescaler 1:16 e 16 bits clock interno
    
    while(1){        
        ClrWdt();
    }*/
    while(1){
        segundos++;

        if(segundos >= 60){
            segundos = 0;
            minutos++;
        }
        LCD_Clear();
        LCD_Set_Cursor(1,1);
        
        escreve_LCD(minutos);
        LCD_Write_String(":");
        escreve_LCD(segundos);
        __delay_ms(200);
    }
    
    return;
}

int minutos = 0;
int segundos = 0;
/*
void __interrupt(high_priority) isr_inter(void){
    
    if(INTCONbits.TMR0IF == 1 && INTCONbits.TMR0IE == 1){ //se for interrupção de timer...
        segundos++;
        
        if(segundos >= 60){
            segundos = 0;
            minutos++;
        }
        

        LCD_Clear();
        //LCD_Write_Int(minutos);
        LCD_Write_Char(':');
        //LCD_Write_Int(segundos);
        
        
        INTCONbits.TMR0IF = 0;
    }
}*/