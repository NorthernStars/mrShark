/*
 * suart.h
 *
 *  Created on: 25.08.2013
 *      Author: Hannes Eilers
 */


#ifndef SUART_H
#define SUART_H
#endif

#ifdef SUART_H

// -------- DEFINES --------
#define SUART_BAUD 		600UL      	// Baudrate

#define SUART_RX_DDR	DDRC
#define SUART_RX_PIN	PINC
#define SUART_RX		PC0

#define SUART_TX_DDR	DDRC
#define SUART_TX_PORT	PORTC
#define SUART_TX		PC1

#define SUART_THRESHOLD		20			// Threshold for rx level in %
#define SUART_OVERSAMPLING	16			// oversampling factor
#define SUART_BUFF_SIZE		30			// size of suart fifo buffer


// Calculation
#define SUART_COMP_VAL 	(F_CPU / (SUART_OVERSAMPLING * SUART_BAUD)) 				// compare match value rounded
#define SUART_BAUD_REAL ((F_CPU * 100) / (SUART_OVERSAMPLING * SUART_COMP_VAL))		// real baudrate * 100
#define SUART_BAUD_ERR 	(SUART_BAUD / 100)											// 1% of baudrate

#if ( (SUART_BAUD_REAL + SUART_BAUD_ERR) < SUART_BAUD_REAL || (SUART_BAUD_REAL -  SUART_BAUD_ERR) > SUART_BAUD_REAL)
  #error Software UART Baudrate error > 1%
#endif

#define SUART_TH	((SUART_OVERSAMPLING * (100-SUART_THRESHOLD)) / 100)

// -------- STATES --------
#define SUART_STATE_IDLE	0
#define SUART_STATE_START	1
#define SUART_STATE_DATA	2
#define SUART_STATE_STOP	3

// -------- VARIABLES --------
#ifdef CFG_SUART_RX
extern uint8_t rxDataBuffer[];
extern fifo_t rxData;
#endif

#ifdef CFG_SUART_TX
extern uint8_t txDataBuffer[];
extern fifo_t txData;
#endif


// -------- FUNCTIONS --------
void suart_init(void);

#ifdef CFG_SUART_RX
uint8_t suart_getc(void);
uint8_t suart_read(void);
#endif

#ifdef CFG_SUART_TX
void suart_putc(char data);
void suart_puts(char *s);
#endif

#endif /* SUART_H */
