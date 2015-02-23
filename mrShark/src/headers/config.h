/*
 * config.h
 *
 *  Created on: 23.08.2013
 *      Author: Hannes Eilers
 */

#ifndef CONFIG_H_
#define CONFIG_H_


// -------- DEFINES --------
#define TRUE	1
#define FALSE	0
#define true	1
#define false	0


// -------- CONFIGURATION BEGIN --------

// -------- CODE LEVEL --------
// uncomment ONE of the following lines to reduce code size
// and to disable features
//#define CFG_CODE_LEVEL_AVG				// no rgb-leds, no motor fault functions, no monitoring, basic debugging
//#define CFG_CODE_LEVEL_MIN				// no rgb-leds, no motor fault functions, no monitoring, no debugging

// -------- GENERAL CONFIGURATION --------
#define CFG_BOT_ID	13
#define CFG_SHOW_CONTROL_TRAFFIC	FALSE
#define CFG_SUART_TX						// uncomment to enable software uart tx
#define CFG_SUART_RX						// uncomment to enable software uart rx

// -------- EXTERNAL MARKER CONFIGURATION --------
#define CFG_EXTERNAL_MARKER						// uncomment to enable external marker pcb

// -------- ENEGRY CONFIGURATION --------
// Set all componets to TRUE that aren't used
#define CFG_POWER_DOWN_I2C		FALSE
#define CFG_POWER_DOWN_TIMER0	FALSE
#define CFG_POWER_DOWN_TIMER1	FALSE
#define CFG_POWER_DOWN_TIMER2	FALSE
#define CFG_POWER_DOWN_SPI		TRUE
#define CFG_POWER_DOWN_UART		FALSE
#define CFG_POWER_DOWN_ADC		TRUE

// -------- CONFIGURATION END --------

#endif /* CONFIG_H_ */
