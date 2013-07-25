/*
 * uart.h
 *
 *  Created on: 30.05.2013
 *      Author: hannes
 */

#ifndef UART_H
#define UART_H

// -------- DEFINES --------
#define BAUD 115200UL      // Baudrate

// Berechnungen
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)  // round clever
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))    // real baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD) 		// error in ppm, 1000 = no error

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
  #error Baudrate error > 1%
#endif

// -------- FUNCTIONS --------
void uart_init(void);
void uart_send_system_info(char *productName, char *productVersion, char *publisher);

void uart_putc(unsigned char c);
void uart_puts (char *s);

uint8_t uart_getc(void);

#endif // UART_H 

