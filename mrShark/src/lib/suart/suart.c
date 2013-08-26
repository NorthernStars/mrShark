/*
 * suart.c
 *
 *  Created on: 25.08.2013
 *      Author: Hannes Eilers
 *
 *      Software uart library.
 *      Baudrate configured in suart.h
 *      UART-Control: 8N1
 */

#include "../../headers/sys.h"

#ifdef CFG_SUART_RX
uint8_t rxDataBuffer[SUART_BUFF_SIZE];;
fifo_t rxData;
#endif

#ifdef CFG_SUART_RX
uint8_t txDataBuffer[SUART_BUFF_SIZE];
fifo_t txData;
#endif

/**
 * Initiates software uart
 */
void suart_init(void){

	// Set IOs and fifo buffer
#ifdef CFG_SUART_RX
	SUART_RX_DDR &= ~(1<<SUART_RX);
    fifo_init (&rxData, rxDataBuffer, SUART_BUFF_SIZE);
#endif

#ifdef CFG_SUART_TX
    SUART_TX_DDR |= (1<<SUART_TX);
	fifo_init(&txData, txDataBuffer, SUART_BUFF_SIZE);
#endif

	// Enable timer
	TCCR1B |= (1<<WGM12) | (1<<CS10);	// ctc mode, no prescaler
	OCR1AH = SUART_COMP_VAL >> 8;		// set compare match value for baudrate
	OCR1AL = SUART_COMP_VAL & 0xFF;
	TIMSK1 |= (1<<OCIE1A);				// enable compare match interrupt

}

#ifdef CFG_SUART_RX
/**
 * Gets a recieved uart byte
 * Blocking call!
 */
uint8_t suart_getc(void){
	return fifo_get_wait(&rxData);
}

/**
 * Gets a recieved uart byte
 * or -1 if nothing recieved
 */
uint8_t suart_read(void){
	return fifo_get_nowait(&rxData);
}
#endif /* CFG_SUART_RX */

#ifdef CFG_SUART_TX
/**
 * Send a byte
 */
void suart_putc(uint8_t data){
	fifo_put(&txData, data);
}

/**
 * Sends a string
 */
void suart_puts(uint8_t *s){
	while(s){
		suart_putc(*s);
		s++;
	}
}
#endif /* CFG_SUART_TX */

/**
 * Timer 1 Compare Match Interrupt
 */
ISR(TIMER1_COMPA_vect){


#ifdef CFG_SUART_RX
	static uint8_t rxState = SUART_STATE_IDLE;
	static uint8_t rxSampleCounter = 0x00;
	static uint8_t rxDataCounter = 0x00;
	static uint8_t rxDataTmp = 0x00;
	static uint8_t rxLevelCounter = 0x00;

	uint8_t rx = (SUART_RX_PIN & (1<<SUART_RX)) >> SUART_RX;
	rxLevelCounter += rx;


	// START CONDITION
	if( rxState == SUART_STATE_IDLE && !rx ){
		rxState = SUART_STATE_START;
		rxLevelCounter = 0xff;
		rxSampleCounter = 0x00;
		rxDataCounter = 0x00;
		rxDataTmp = 0x00;
	}
	// START BIT
	else if( rxState == SUART_STATE_START ){
		if( rxSampleCounter ==  SUART_OVERSAMPLING - 1 ){
			if( rxLevelCounter < SUART_TH ){
				// recieved start bit
				rxState = SUART_STATE_DATA;
			}
			else
				// no start bit > reset
				rxState = SUART_STATE_IDLE;

			rxSampleCounter = 0x00;
			rxLevelCounter = 0x00;
		}
		else
			rxSampleCounter++;
	}
	// RECIEVING DATA
	else if( rxState == SUART_STATE_DATA ){
		if( rxSampleCounter == SUART_OVERSAMPLING - 1 ){
			if( rxLevelCounter < SUART_TH ){
				// add bit to data
				rxDataTmp += (1<<rxDataCounter);
			}

			rxDataCounter++;
			rxSampleCounter = 0x00;
			rxLevelCounter = 0x00;
		}
		else{
			rxSampleCounter++;
		}

		if( rxDataCounter == 7 )
			// collected all data bits
			rxState = SUART_STATE_STOP;
	}
	// STOP BIT
	else if( rxState == SUART_STATE_STOP ){
		if( rxSampleCounter ==  SUART_OVERSAMPLING - 1 ){
			if( rxLevelCounter > SUART_TH ){
				fifo_put(&rxData, rxDataTmp);
			}

			rxState = SUART_STATE_IDLE;
		}
		else
			rxSampleCounter++;
	}

#endif /* CFG_SUART_RX */

#ifdef CFG_SUART_TX
	static uint8_t txState = SUART_STATE_IDLE;
	static uint8_t txSampleCounter = 0x00;
	static uint8_t txDataCounter = 0x00;
	static uint8_t txDataTmp = 0x00;

	if( txState == SUART_STATE_IDLE && fifo_getCount(&txData) ){
		txState = SUART_STATE_START;
		txSampleCounter = 0x00;
		txDataTmp = fifo_get_nowait(&txData);
		SUART_TX_PORT &= ~(1<<SUART_TX);
	}
	else if( txState == SUART_STATE_START ){
		if( txSampleCounter < SUART_OVERSAMPLING - 1 )
			txSampleCounter++;
		else{
			txState = SUART_STATE_DATA;
			txSampleCounter = 0x00;
		}
	}
	else if( txState == SUART_STATE_DATA ){
		uint8_t bit = txDataTmp & (1<<txDataCounter);
		if( txSampleCounter < SUART_OVERSAMPLING - 1 ){
			if(bit)
				SUART_TX_PORT &= ~(1<<SUART_TX);
			else
				SUART_TX_PORT |= (1<<SUART_TX);

			txSampleCounter++;
		}
		else{
			if(txDataCounter == 7){
				txSampleCounter = 0x00;
				txState = SUART_STATE_STOP;
				SUART_TX_PORT |= (1<<SUART_TX);
			}
			else
				txDataCounter++;
		}
	}
	else if( txState == SUART_STATE_STOP ){
		if( txSampleCounter < SUART_OVERSAMPLING - 1 )
			txSampleCounter++;
		else
			txState = SUART_STATE_IDLE;
	}
	else
		SUART_TX_PORT |= (1<<SUART_TX);

#endif /* CFG_SUART_TX */

}
