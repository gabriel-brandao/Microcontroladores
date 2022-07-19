//Fonte: https://www.microchip.com/forums/m1038695.aspx

#ifndef UART_H
#define	UART_H

#include <stdlib.h>

void UART_Open(const long int baudrate) {
     unsigned int x;
     x = (unsigned int)((_XTAL_FREQ - baudrate * 64) / (baudrate * 64)); //SPBRG for Low Baud Rate
     if (x > 255){//If High Baud Rage Required
        x = (unsigned int)((_XTAL_FREQ - baudrate * 16) / (baudrate * 16)); //SPBRG for High Baud Rate
        TXSTAbits.BRGH = 1; //Setting High Baud Rate
     }
     if (x < 256) {
          SPBRG = x; //Writing SPBRG Register
          TXSTAbits.SYNC = 0; //Setting Asynchronous Mode, ie UART
          RCSTAbits.SPEN = 1; //Enables Serial Port
          TRISCbits.RC7 = 1; //As Prescribed in Datasheet
          TRISCbits.RC6 = 0; //As Prescribed in Datasheet
          RCSTAbits.CREN = 1; //Enables Continuous Reception
          TXSTAbits.TXEN = 1; //Enables Transmission
          TXIE = 1; // Enable tx interrupts 
          RCIE = 1; // Enable rx interrupts
     }
}

void UART_Close(void) {
     RCSTAbits.SPEN = 0;
}

char UART_TX_Idle(void) {
     return (char) TXSTAbits.TRMT;
}

char UART_TX_Busy(void) {
     return (char) !TXSTAbits.TRMT;
}

char UART_RX_Ready(void) {
     return (char) RCIF;
}

void UART_Write(char info[]) {
     int i;
     for (i = 0; info[i] != '\0'; i++) {
          TXREG = info[i];
          while (UART_TX_Busy());
     }
}

void UART_Read(char info[]) {
     unsigned int i = 0;
     while (1) {
          while (!UART_RX_Ready());
          info[i] = RCREG;
          
          if (info[i] != '\r' && info[i] != '\n') 
              i++;
           else{
               info[i+1]='\0';
               break;
          }
     }
}

#endif