/*
 * sys.h
 *
 *  Created on: 28.05.2013
 *      Author: hannes
 */

#ifndef F_CPU
#define F_CPU 			11059200UL
#endif

#ifndef SYS_H_
#define SYS_H_
// -------- SYS_INFO --------
#define SYS_NAME		"mrShark"
#define SYS_VERSION		"0.8"
#define SYS_PUBLISHER	"NorthernStars"


// -------- INCLUDES --------
#include <avr/io.h>
#include <stdlib.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "../lib/i2c/i2cmaster.h"
#include "../lib/uart/uart.h"
#include "config.h"
#include "led.h"
#include "motor.h"
#include "control.h"

/* 9600 baud */
#define UART_BAUD_RATE		115200UL
#define SUART_BAUD_RATE		9600UL

// -------- VARIABLES --------
extern uint8_t sys_robotID;
extern volatile uint8_t sys_showControlTraffic;

// -------- FUNCTIONS --------
void sys_init(void);


#endif /* SYS_H_ */
