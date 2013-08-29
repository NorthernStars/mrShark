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

	// set led colors to red
	led_set_color_red( 255, LED_N|LED_O|LED_S|LED_W );
	led_on( LED_N|LED_O|LED_S|LED_W );

	// send system information
	control_send_system_info(SYS_NAME, SYS_VERSION, SYS_PUBLISHER);

	// set led color green
	led_set_nocolors();
	led_all_off();
	led_set_color_green( 255, LED_N|LED_O|LED_S|LED_W );
	led_on( LED_N|LED_O|LED_S|LED_W );


}
