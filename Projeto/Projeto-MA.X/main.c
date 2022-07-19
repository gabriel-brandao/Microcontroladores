// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator (HS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = ON        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

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

#define _XTAL_FREQ 4000000
#include <xc.h>
#include "lcd.h"
#include <stdio.h>

#define HEATER PORTCbits.RC5 //esquentar
#define COOLER PORTCbits.RC2 //esfriar 

int temperaturaMax = 50;
int intervaloOffColer = 5;

void __interrupt(high_priority) isr_inter(void){

    if(INTCONbits.INT0IE && INTCONbits.INT0IF){ //se for interrupção INT0
        temperaturaMax--;
        INTCONbits.INT0IF=0;
    }
    
    if(INTCON3bits.INT1IE && INTCON3bits.INT1IF){ 
        temperaturaMax++;
        INTCON3bits.INT1IF = 0;
    }
}


void main(void) {
    double temperaturaAtual;
    
    RCONbits.IPEN = 1; //habilita prioridade
    INTCONbits.GIEH = 1; //ativa alta prioridade
    INTCONbits.GIEL = 0; //desativa baixa prioridade
    
    //Configura a interrupção INT0
    INTCONbits.INT0IE = 1;//Habilita INT0
    INTCONbits.INT0IF = 0;//Limpa a flag de INT0
    INTCON2bits.INTEDG0 = 1;//Borda de subida
    
    //Configura a interrupção INT1
    INTCON3bits.INT1E = 1; //Habilita INT1
    INTCON3bits.INT1F = 0; //Limpa a flag de INT1
    INTCON2bits.INTEDG1 = 1; //Borda de subida
    INTCON3bits.INT1IP = 1; //Ativa alta prioridade
    
    TRISC=0;
    
    ADCON0 = 0b00001001;//Habilita conversão A/D em modo ocioso, seleciona canal AN2, 
    ADCON1 = 0b00001100;//Configura AN2 como analógico, Vref+ = VDD e Vref- = VSS
	ADCON2 = 0b10001100;//Fosc/4, Taq=2Tad, justificado a direita
   
    PIC_init();
    config_lcd();
    
    while(1){
        HEATER = 1;
        
        if (temperaturaAtual >= temperaturaMax)
                COOLER = 1;
         else
            if (temperaturaAtual < (temperaturaMax - intervaloOffColer))
                COOLER = 0;
            
        ADCON0bits.GODONE = 1; //inicia a conversão AD
            while(ADCON0bits.GODONE == 1){
                temperaturaAtual = ((ADRESH << 8) | ADRESL);
                temperaturaAtual = (1000*temperaturaAtual)/2048;//Calculo do sensor de temperatura com mais sensibilidade
                limpa_tela();
                escrever_lcd("Temp.Now:");
                escrever_temperatura(temperaturaAtual, 2);
                cursor_lcd_pos(0x90); //endereçamento para terceira linha (LCD 16X4)
                escrever_lcd("Max: ");
                escrever_temperatura(temperaturaMax, 2);
                
                __delay_ms(300);   
            }

        ClrWdt();
    }
    return;
}