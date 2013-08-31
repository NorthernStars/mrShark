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

// uncomment ONE of the following lines to reduce code size
// and to disable features
//#define CFG_CODE_LEVEL_AVG				// no rgb-leds, no motor fault functions, no monitoring, basic debugging
//#define CFG_CODE_LEVEL_MIN				// no rgb-leds, no motor fault functions, no monitoring, no debugging


// -------- CONFIGURATION --------
#define CFG_BOT_ID	0
#define CFG_SHOW_CONTROL_TRAFFIC	TRUE
#define CFG_SUART_TX						// uncomment to enable software uart tx
#define CFG_SUART_RX						// uncomment to enable software uart rx


// -------- CONFIGURATION END --------

#endif /* CONFIG_H_ */
