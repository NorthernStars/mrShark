/*
 * sys.h
 *
 *  Created on: 28.05.2013
 *      Author: hannes
 */

#ifndef F_CPU
#define F_CPU			14745600UL
//#define F_CPU 			11059200UL
#endif

#ifndef SYS_H_
#define SYS_H_


// -------- SYS_INFO --------
#define SYS_NAME		"mrShark"
#define SYS_VERSION		"1.0.0b"
#define SYS_PUBLISHER	"NorthernStars"

// -------- ONBOARD I2C CONFIGURATION --------
#define SYS_I2C_ONBOARD_ACTIVE		TRUE
#define SYS_I2C_ONBOARD_ADDR		0xE0
#define SYS_I2C_ONBOARD_SEL_CH0		0x04
#define SYS_I2C_ONBOARD_SEL_CH1		0x05
#define SYS_I2C_ONBOARD_SEL_NONE	0x00

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
#include "../lib/marker/marker.h"

#include "led.h"
#include "motor.h"
#include "control.h"
#include "monitor.h"

#ifndef CFG_CODE_LEVEL_MIN
#include "debug.h"
#include "animation.h"
#endif


// -------- VARIABLES --------
extern uint8_t sys_robotID;
extern volatile uint8_t sys_showControlTraffic;

// -------- EEPROM DATA --------
#define EEPROM_DEF 0xFF
extern uint8_t  sys_ee_robotID EEMEM;

// -------- FUNCTIONS --------
void sys_init(void);
void sys_external_marker_init();
void sys_power_init(void);
void sys_sleep(void);

uint8_t sys_ee_read_robotID(void);
void sys_ee_set_robotID(uint8_t robotID);

void sys_set_onboard_i2c(uint8_t channel);
uint8_t sys_read_onboard_i2c(void);
void sys_enable_onboard_i2c(void);
void sys_disable_onboard_i2c(void);


#endif /* SYS_H_ */
