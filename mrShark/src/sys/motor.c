/*
 * motor.c
 *
 *  Created on: 28.05.2013
 *      Author: hannes
 */

#include "../headers/sys.h"

/**
 * Initiates motors
 */
void motor_init(void){

	// test if motor drivers are available
	motor_test();
}

/**
 * Runs motor test sequence
 */
void motor_test(void){
	motor_set_speed(MOTOR_ADDR_L, MOTOR_SPEED_HALF, MOTOR_FORWARD);
	motor_set_speed(MOTOR_ADDR_R, MOTOR_SPEED_HALF, MOTOR_BACKWARD);
	_delay_ms(1000);

	motor_set_speed(MOTOR_ADDR_R, MOTOR_SPEED_HALF, MOTOR_FORWARD);
	motor_set_speed(MOTOR_ADDR_L, MOTOR_SPEED_HALF, MOTOR_BACKWARD);
	_delay_ms(1000);

	motor_all_brake();
}

/**
 * Sets the motors speed
 */
void motor_set_speed(uint8_t address, uint8_t speed, uint8_t direction){

	if(speed > 0x05 && speed <= 0x3f){
		i2c_start_wait( address + I2C_WRITE );
		i2c_write( MOTOR_REG_CONTROL );
		i2c_write( (speed<<2) | direction );
		i2c_stop();
	}
}

/**
 * Let one motor brake
 */
void motor_brake(uint8_t address){
	motor_set_speed(address, MOTOR_SPEED_MIN, MOTOR_BRAKE);
}

/**
 * Let all motors brake
 */
void motor_all_brake(void){
	motor_brake(MOTOR_ADDR_L);
	motor_brake(MOTOR_ADDR_R);
}
