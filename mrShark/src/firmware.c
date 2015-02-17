/*
 * firmware.c
 *
 *  Created on: 14.05.2013
 *      Author: hannes
 */
#include <util/twi.h>

#include "headers/sys.h"


int main(void){

	uint16_t curMotorL = 0x00;
	uint16_t curMotorR = 0x00;
	uint8_t speedMotorL = 0x00;
	uint8_t speedMotorR = 0x00;

	// initiate system
	sys_init();

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
		if( ctrl_flag_id ){
			sys_ee_set_robotID( control_getRobotID() );
			sys_external_marker_init();
		}

		// read motor currents and speeds
		curMotorL = monitor_read_current(MONITOR_ADDR_1, MONITOR_I1);
		curMotorR = monitor_read_current(MONITOR_ADDR_1, MONITOR_I2);
		speedMotorL = control_getMotorSpeed(MOTOR_ADDR_L);
		speedMotorR = control_getMotorSpeed(MOTOR_ADDR_R);

		// adjust motor speed
		// tries to decrease speed of faster motor,
		// or if that fails because motor is already speed minimum
		// increases the speed of the slower motor.
		if( curMotorL > curMotorR ){

			if( speedMotorL > MOTOR_SPEED_MIN ){
				motor_decrease_speed(MOTOR_ADDR_L, 1);
			} else if( speedMotorR < MOTOR_SPEED_MAX ){
				motor_increase_speed(MOTOR_ADDR_R, 1);
			}

		} else if( curMotorR > curMotorL ){

			if( speedMotorR > MOTOR_SPEED_MIN ){
				motor_decrease_speed(MOTOR_ADDR_R, 1);
			} else if( speedMotorL < MOTOR_SPEED_MAX ){
				motor_increase_speed(MOTOR_ADDR_L, 1);
			}

		}

		#ifndef CFG_CODE_LEVEL_MIN
		// process debugging module
		debug_process();
		#endif

	}

}
