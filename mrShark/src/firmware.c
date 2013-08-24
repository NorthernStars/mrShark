/*
 * firmware.c
 *
 *  Created on: 14.05.2013
 *      Author: hannes
 */

#include "headers/sys.h"


int main(void){

	// initiate system
	sys_init();

	led_set_allcolors();

	// main loop
	while(1){

		uint8_t motor_cmd;
		uint8_t motor_speed;

		// check for changed motor values
		if( ctrl_flag_motorL ){
			motor_cmd = control_getMotorCommand(MOTOR_ADDR_L);
			motor_speed = control_getMotorSpeed(MOTOR_ADDR_L);
			motor_set_speed(MOTOR_ADDR_L, motor_speed, motor_cmd);
		}
		if( ctrl_flag_motorR ){
			motor_cmd = control_getMotorCommand(MOTOR_ADDR_R);
			motor_speed = control_getMotorSpeed(MOTOR_ADDR_R);
			motor_set_speed(MOTOR_ADDR_R, motor_speed, motor_cmd);
		}
	};

}
