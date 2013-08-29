/*
 * motor.c
 *
 *  Created on: 28.05.2013
 *      Author: hannes
 */

#include "../headers/sys.h"

// -------- VARIABLES --------
uint8_t motor_left_cmd = MOTOR_BRAKE;
uint8_t motor_left_speed = MOTOR_BRAKE;
uint8_t motor_right_cmd = MOTOR_BRAKE;
uint8_t motor_right_speed = MOTOR_BRAKE;

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
void motor_set_speed(uint8_t address, uint16_t speed, uint8_t direction){
	speed = (speed * 100) / 0xff;
	speed  = speed * (MOTOR_SPEED_MAX - MOTOR_SPEED_MIN);
	speed = (speed / 100) + MOTOR_SPEED_MIN;
	i2c_writeData( address, MOTOR_REG_CONTROL, (speed<<2)|direction );
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

/**
 * Returns motor direction command
 */
uint8_t motor_get_direction(uint8_t address){
	return i2c_readData(address, MOTOR_REG_CONTROL) & 0x03;
}

/**
 * Returns motor speed
 */
uint8_t motor_get_speed(uint8_t address){
	uint16_t speed = i2c_readData(address, MOTOR_REG_CONTROL) >> 2;
	speed = (speed - MOTOR_SPEED_MIN) * 100;
	speed = speed / (MOTOR_SPEED_MAX - MOTOR_SPEED_MIN);
	speed = (speed * 0xff) / 100;
	return speed;
}

/**
 * Gets fault conditions from motor driver
 */
uint8_t motor_get_fault(uint8_t address){
	return i2c_readData(address, MOTOR_REG_FAULT) & MOTOR_FAULT_MASK;
}

/**
 * Clears the fault conditions ofmotor driver
 */
void motor_clear_fault(uint8_t address){
	i2c_writeData(address, MOTOR_REG_FAULT, MOTOR_FAULT_CLEAR);
}
