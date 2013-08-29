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
#define SYS_VERSION		"1.0"
#define SYS_PUBLISHER	"NorthernStars"


// -------- ENEGRY CONFIGURATION --------
// Set all componets to TRUE that aren't used
#define SYS_POWER_DOWN_I2C		FALSE
#define SYS_POWER_DOWN_TIMER0	FALSE
#define SYS_POWER_DOWN_TIMER1	FALSE
#define SYS_POWER_DOWN_TIMER2	TRUE
#define SYS_POWER_DOWN_SPI		TRUE
#define SYS_POWER_DOWN_UART		FALSE
#define SYS_POWER_DOWN_ADC		TRUE


// -------- INCLUDES --------
#include <avr/io.h>
#include <stdlib.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>

#include "config.h"
#include "../lib/i2c/i2cmaster.h"
#include "../lib/uart/uart.h"
#include "../lib/suart/suart.h"
#include "debug.h"
#include "led.h"
#include "motor.h"
#include "control.h"
#include "monitor.h"

// -------- VARIABLES --------
extern uint8_t sys_robotID;
extern volatile uint8_t sys_showControlTraffic;

// -------- EEPROM DATA --------
#define EEPROM_DEF 0xFF
extern uint8_t  sys_ee_robotID EEMEM;

// -------- FUNCTIONS --------
void sys_init(void);
void sys_power_init(void);
void sys_sleep(void);

uint8_t sys_ee_read_robotID(void);
void sys_ee_set_robotID(uint8_t robotID);


#endif /* SYS_H_ */
