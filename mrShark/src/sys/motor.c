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
 * Returns 0x00 if no fault conditions occured
 * or 0xff if fault condition occured
 */
uint8_t motor_test(void){

	led_all_on();
	led_set_all_colors(0xff, 0x00, 0x00);
	_delay_ms(250);

	// clear motor faults
	led_set_all_colors(0xff, 0x50, 0x00);
	#if !defined(CFG_CODE_LEVEL_AVG) && !defined(CFG_CODE_LEVEL_MIN)
	motor_clear_fault(MOTOR_ADDR_L);
	motor_clear_fault(MOTOR_ADDR_R);
	#endif

	motor_set_speed(MOTOR_ADDR_L, MOTOR_SPEED_HALF, MOTOR_FORWARD);
	motor_set_speed(MOTOR_ADDR_R, MOTOR_SPEED_HALF, MOTOR_FORWARD);
	_delay_ms(200);

	motor_all_brake();
	_delay_ms(100);

	motor_set_speed(MOTOR_ADDR_R, MOTOR_SPEED_HALF, MOTOR_BACKWARD);
	motor_set_speed(MOTOR_ADDR_L, MOTOR_SPEED_HALF, MOTOR_BACKWARD);
	_delay_ms(200);

	motor_all_brake();

	led_set_all_colors(0x00, 0xff, 0x00);
	_delay_ms(250);
	led_all_off();

	// check if fault condition occured
	#if !defined(CFG_CODE_LEVEL_AVG) && !defined(CFG_CODE_LEVEL_MIN)
	return (motor_get_fault(MOTOR_ADDR_L) | motor_get_fault(MOTOR_ADDR_R)) & MOTOR_FAULT_MASK;
	#else
	return 0x00;
	#endif

}

/**
 * Sets the motors speed
 */
void motor_set_speed(uint8_t address, uint16_t speed, uint8_t direction){
	if( !speed ){
		motor_brake(address);
	}
	else {
		speed = (speed * 100) / 0xff;
		speed  = speed * (MOTOR_SPEED_MAX - MOTOR_SPEED_MIN);
		speed = (speed / 100) + MOTOR_SPEED_MIN;
		i2c_writeData( address, MOTOR_REG_CONTROL, (speed<<2)|direction );
	}

}

/**
 * Increases the motor value of the motor by inc
 */
void motor_increase_speed(uint8_t address, uint8_t inc){
	motor_set_speed(
					address,
					control_getMotorSpeed(address) + inc,
					control_getMotorCommand(address));
}

/**
 * Decreases the motor value of the motor by dec
 */
void motor_decrease_speed(uint8_t address, uint8_t dec){
	motor_set_speed(
					address,
					control_getMotorSpeed(address) - dec,
					control_getMotorCommand(address));
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

#if !defined(CFG_CODE_LEVEL_AVG) && !defined(CFG_CODE_LEVEL_MIN)
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
#endif
