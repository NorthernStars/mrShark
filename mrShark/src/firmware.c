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

	led_on(LED_STATUS);
	led_set_allcolors();

	uart_send_system_info(SYS_NAME, SYS_VERSION, SYS_PUBLISHER);

	// main loop
	uint8_t c = 0x00;
	uint8_t led_status = 0x00;
	uint8_t speed = MOTOR_SPEED_HALF;
	/**
	 * COMMANDS
	 * All commands are NOT case sensitive
	 * x: all leds on
	 * o: all leds off
	 * f: forward
	 * r: backward
	 * b: brake
	 * m: set max speed (send direction after this)
	 * h: set half speed (send direction after this)
	 * i: set min speed (send direction after this)
	 */
	while(1){

		if(led_status){
			led_off(LED_STATUS);
			led_status = 0x00;
		}
		else{
			led_on(LED_STATUS);
			led_status = 0xff;
		}

		c = control_get();

		if(c){
			led_all_off();
			led_on(LED_STATUS);
		}

		// process command
		if( c == 'F' || c == 'f' ){
			motor_set_speed(MOTOR_ADDR_L, speed, MOTOR_FORWARD);
			motor_set_speed(MOTOR_ADDR_R, speed, MOTOR_FORWARD);
			uart_puts(":fwd");
			led_on(LED_N);
		}
		else if( c == 'R' || c == 'r' ){
			motor_set_speed(MOTOR_ADDR_L, speed, MOTOR_REVERSE);
			motor_set_speed(MOTOR_ADDR_R, speed, MOTOR_REVERSE);
			uart_puts(":bwd");
			led_on(LED_O);
		}
		else if( c == 'B' || c == 'b' ){
			motor_brake(MOTOR_ADDR_L);
			motor_brake(MOTOR_ADDR_R);
			uart_puts(":brake");
			led_on(LED_S);
		}
		else if( c == 'X' || c == 'x' ){
			uart_puts(":led_all_on");
			led_all_on();
		}
		else if( c == 'O' || c == 'o' ){
					uart_puts(":led_all_off");
					led_all_off();
				}
		else if( c == 'H' || c == 'h' ){
			speed = MOTOR_SPEED_HALF;
			uart_puts(":half_speed");
			led_on(LED_W);
		}
		else if( c == 'M' || c == 'm' ){
			speed = MOTOR_SPEED_MAX;
			uart_puts(":max_speed");
			led_on(LED_W);
		}
		else if( c == 'I' || c == 'i' ){
			speed = MOTOR_SPEED_MIN;
			uart_puts(":min_speed");
			led_on(LED_W);
		}

	}

}
