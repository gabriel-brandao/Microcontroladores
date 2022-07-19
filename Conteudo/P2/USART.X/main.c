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
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
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
#include <stdlib.h>
#include <stdio.h> //printf
#include <string.h> //strcmp
#include "uart.h"

void main(void) {
     TRISB = 0; //Configura PORTB como saída
     PORTB = 0; //Inicia PORTB toda com nível baixo
     int numPorta=0;
     char temp[10];
     
     UART_Close(); //fecha qualquer conexao que estiver aberta
     UART_Open(9600); //abre uma conexão []bits/s
     UART_Write("Start!\r\n");
     
     while (1) {
          UART_Read(temp); //lê do terminal
          UART_Write(temp); //escreve no terminal
          
          if (strncmp(temp,"ON",2) == 0){ //compara apenas os 2 primeiros caracteres das duas strings, se iguais retorna 0
              UART_Write("Num porta");
              UART_Read(temp);
              UART_Write(temp);
              
              numPorta = atoi(temp); //converte cadeia de char para int
              
              switch(numPorta){
                  case 0:
                      PORTBbits.RB0 = 1;
                      UART_Write("LED0 ON\r\n");
                      break;
                  case 1:
                      PORTBbits.RB1 = 1;
                      UART_Write("LED1 ON\r\n");
                      break;
                  case 2:
                      PORTBbits.RB2 = 1;
                      UART_Write("LED2 ON\r\n");
                      break;
                  case 3:
                      PORTBbits.RB3 = 1;
                      UART_Write("LED3 ON\r\n");
                      break;
                  case 4:
                      PORTBbits.RB4 = 1;
                      UART_Write("LED4 ON\r\n");
                      break;
                  case 5:
                      PORTBbits.RB5 = 1;
                      UART_Write("LED5 ON\r\n");
                      break;
                  case 6:
                      PORTBbits.RB6 = 1;
                      UART_Write("LED6 ON\r\n");
                      break;
                  case 7:
                      PORTBbits.RB7 = 1;
                      UART_Write("LED7 ON\r\n");
                      break;
                  default:
                      UART_Write("Invalido\r\n");
              }
          }
          if (strncmp(temp,"OFF",3) == 0) {
              UART_Write("Num porta");
              UART_Read(temp);
              UART_Write(temp);
              
              numPorta = atoi(temp);
              
              switch(numPorta){
                  case 0:
                      PORTBbits.RB0 = 0;
                      UART_Write("LED0 OFF\r\n");
                      break;
                  case 1:
                      PORTBbits.RB1 = 0;
                      UART_Write("LED1 OFF\r\n");
                      break;
                  case 2:
                      PORTBbits.RB2 = 0;
                      UART_Write("LED2 OFF\r\n");
                      break;
                  case 3:
                      PORTBbits.RB3 = 0;
                      UART_Write("LED3 OFF\r\n");
                      break;
                  case 4:
                      PORTBbits.RB4 = 0;
                      UART_Write("LED4 OFF\r\n");
                      break;
                  case 5:
                      PORTBbits.RB5 = 0;
                      UART_Write("LED5 OFF\r\n");
                      break;
                  case 6:
                      PORTBbits.RB6 = 0;
                      UART_Write("LED6 OFF\r\n");
                      break;
                  case 7:
                      PORTBbits.RB7 = 0;
                      UART_Write("LED7 OFF\r\n");
                      break;
                  default:
                      UART_Write("Invalido\r\n");
              }
          }
          if (strncmp(temp,"Out",3) == 0) {
               UART_Write("Program Out\r\n");
               PORTBbits.RB1 = 0;
               break;
          }
     }
     UART_Write("Finish!\r\n");
}