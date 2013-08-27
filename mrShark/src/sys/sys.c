/*
 * sys.c
 *
 *  Created on: 28.05.2013
 *      Author: hannes
 */

#include "../headers/sys.h"

// -------- VARIABLES --------
uint8_t sys_robotID = CFG_BOT_ID;
volatile uint8_t sys_showControlTraffic = CFG_SHOW_CONTROL_TRAFFIC;

/**
 * Initiates the complete system
 */
void sys_init(void){

	// call libraries init functions
	i2c_init();
	led_init();
	motor_init();
	control_init();
	suart_init();

	sei();

	// send system information
	suart_puts( SYS_NAME );
	suart_puts( " " );
	suart_puts( SYS_VERSION	);
	suart_puts( "\r\n" );
	suart_puts( SYS_PUBLISHER );

}
