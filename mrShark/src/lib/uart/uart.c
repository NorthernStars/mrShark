/*
 * uart.c
 *
 *  Created on: 30.05.2013
 *      Author: hannes
 */

#include "../../headers/sys.h"

/**
 * Initiates uart
 */
void uart_init(void)
{
    UBRR0H = UBRR_VAL >> 8;					// set baudrate
    UBRR0L = UBRR_VAL & 0xFF;

    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);  		// asynchron 8N1
    UCSR0B |= (1<<RXEN0) | (1<<TXEN0);      // enable rx and tx
}

/**
 * Sends a char via uart
 */
void uart_putc(unsigned char c)
{
    while (!(UCSR0A & (1<<UDRE0)));			// wait until ready to send
    UDR0 = c;
}


/**
 * Sends a string via uart
 */
void uart_puts (char *s)
{
    while (*s)
    {
        uart_putc(*s);
        s++;
    }
}

/**
 * Gets a char from uart
 */
uint8_t uart_getc(void)
{
    while (!(UCSR0A & (1<<RXC0)));   	// wait until char recieved
    return UDR0;                   		// return recieved char
}
