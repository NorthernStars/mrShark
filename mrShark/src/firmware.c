/*
 * firmware.c
 *
 *  Created on: 14.05.2013
 *      Author: hannes
 */
#include <util/twi.h>

#include "headers/sys.h"


int main(void){

	// initiate system
	sys_init();

	animation_set_mode(ANIMATION_MODE_FADE);

	// main loop
	while(1){

		// suspend system
		sys_sleep();

		// check for changed motor values
		if( ctrl_flag_motorL ){
			motor_set_speed(
					MOTOR_ADDR_L,
					control_getMotorSpeed(MOTOR_ADDR_L),
					control_getMotorCommand(MOTOR_ADDR_L));
		}

		if( ctrl_flag_motorR ){
			motor_set_speed(
					MOTOR_ADDR_R,
					control_getMotorSpeed(MOTOR_ADDR_R),
					control_getMotorCommand(MOTOR_ADDR_R));
		}

		// check for changed robot id
		if( ctrl_flag_id )
			sys_ee_set_robotID( control_getRobotID() );

		#ifndef CFG_CODE_LEVEL_MIN
		// process debugging module
		debug_process();
		#endif

	}

}
