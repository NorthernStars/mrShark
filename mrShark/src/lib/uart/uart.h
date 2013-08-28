/*
 * uart.h
 *
 *  Created on: 30.05.2013
 *      Author: hannes
 */

#ifndef F_CPU
#define F_CPU		11059200UL
#endif

#ifndef UART_H
#define UART_H

// -------- DEFINES --------
#define UART_BAUD 115200UL      // Baudrate

// Berechnungen
#define UART_UBRR_VAL ((F_CPU+UART_BAUD*8)/(UART_BAUD*16)-1)  	// round clever
#define UART_BAUD_REAL (F_CPU/(16*(UART_UBRR_VAL+1)))    		// real baudrate
#define UART_BAUD_ERROR ((UART_BAUD_REAL*1000)/UART_BAUD) 		// error in ppm, 1000 = no error

#if ((UART_BAUD_ERROR<990) || (UART_BAUD_ERROR>1010))
  #error UART Baudrate error > 1%
#endif

// -------- FUNCTIONS --------
void uart_init(void);

void uart_putc(unsigned char c);
void uart_puts (char *s);

uint8_t uart_getc(void);

#endif // UART_H 

