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

	led_on(LED_STATUS);

	motor_init();
	control_init();
	debug_init();

	sei();

	// send system information
	debug_send_system_info(SYS_NAME, SYS_VERSION, SYS_PUBLISHER);

	// set led color green
	led_off(LED_STATUS);

}
