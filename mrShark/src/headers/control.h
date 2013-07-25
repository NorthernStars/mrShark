/*
 * control.h
 *
 *  Created on: 29.05.2013
 *      Author: hannes
 */

#ifndef CONTROL_H_
#define CONTROL_H_

// -------- DEFINES --------
#define IR_SD_DDR	DDRD
#define IR_SD_PORT	PORTD
#define IR_SD		PD4

// -------- VARIABLES --------


// -------- FUNCTIONS --------
void control_init(void);
uint8_t control_get(void);
void control_IR_shutdown(void);
void control_IR_switchon(void);

#endif /* CONTROL_H_ */
