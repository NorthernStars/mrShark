/*
 * sys.c
 *
 *  Created on: 28.05.2013
 *      Author: hannes
 */

#include "../headers/sys.h"

/**
 * Initiates the complete system
 */
void sys_init(void){

	// call libraries init functions
	i2c_init();
	led_init();
	motor_init();
	control_init();

	sei();

}
