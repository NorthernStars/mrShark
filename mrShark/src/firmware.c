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

	// main loop
	while(1){

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

		// process debugging module
		debug_process();

	}

}
