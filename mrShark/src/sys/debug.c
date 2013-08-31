/*
 * debug.c
 *
 *  Created on: 29.08.2013
 *      Author: hannes
 */

#include "../headers/sys.h"

#ifndef CFG_CODE_LEVEL_MIN

/**
 * Initiates debugging module
 */
void debug_init(void){
	suart_init();
}

/**
 * Function to process debugging module
 * Checks for debbunging commands and things like this
 */
void debug_process(void){
#ifdef CFG_SUART_RX

	// check for recieved commands
	if( suart_rxFlag ){
		uint8_t cmd = suart_getc();

		uint16_t tmp;

		// process command
		switch(cmd){

		case 'f':
			motor_set_speed(MOTOR_ADDR_L, MOTOR_SPEED_HALF, MOTOR_FORWARD);
			motor_set_speed(MOTOR_ADDR_R, MOTOR_SPEED_HALF, MOTOR_FORWARD);
			break;

		case'b':
			motor_set_speed(MOTOR_ADDR_L, MOTOR_SPEED_HALF, MOTOR_BACKWARD);
			motor_set_speed(MOTOR_ADDR_R, MOTOR_SPEED_HALF, MOTOR_BACKWARD);
			break;

		case 'z':
			motor_set_speed(MOTOR_ADDR_L, 0x00, MOTOR_BRAKE);
			motor_set_speed(MOTOR_ADDR_R, 0x00, MOTOR_BRAKE);
			break;

		#if !defined(CFG_CODE_LEVEL_AVG)
		case 'g':
			led_set_allcolors();
			led_all_on();
			break;

		case 'h':
			led_set_nocolors();
			led_all_off();
			break;
		#endif

		case 's':
			led_on(LED_STATUS);
			break;

		case 'r':
			led_off(LED_STATUS);
			break;

		case 'c':
			motor_set_speed(MOTOR_ADDR_L, MOTOR_SPEED_HALF, MOTOR_FORWARD);
			motor_set_speed(MOTOR_ADDR_R, MOTOR_SPEED_HALF, MOTOR_BACKWARD);
			break;

		case 'a':
			motor_set_speed(MOTOR_ADDR_L, MOTOR_SPEED_HALF, MOTOR_BACKWARD);
			motor_set_speed(MOTOR_ADDR_R, MOTOR_SPEED_HALF, MOTOR_FORWARD);
			break;

		#if !defined(CFG_CODE_LEVEL_AVG)
		case 'm':
			debug_send_c( motor_get_speed(MOTOR_ADDR_L) );
			break;

		case 'n':
			debug_send_c( motor_get_speed(MOTOR_ADDR_R) );
			break;

		case 'o':
			debug_send_c( motor_get_direction(MOTOR_ADDR_L) );
			break;

		case 'p':
			debug_send_c( motor_get_direction(MOTOR_ADDR_R) );
			break;

		case 'd':
			debug_send_c( motor_get_fault(MOTOR_ADDR_L) );
			break;

		case 'e':
			debug_send_c( motor_get_fault(MOTOR_ADDR_R) );
			break;

		case 'u':
			motor_clear_fault( MOTOR_ADDR_L );
			break;

		case 'v':
			motor_clear_fault( MOTOR_ADDR_R );
			break;
		#endif

		case 'i':
			debug_send_c( sys_robotID );
			break;

		case 'j':
			debug_send_msg( SYS_PUBLISHER );
			break;

		case 'k':
			debug_send_msg( SYS_VERSION );
			break;

		case 'l':
			debug_send_msg( SYS_NAME );
			break;

		case 'M':
			debug_send_c( motor_test() );
			break;

		case 'T':
			tmp = monitor_read_temp(MONITOR_ADDR_1);
			debug_send_c_wait( tmp>>8);
			debug_send_c_wait( tmp );
			debug_send_msg("\r\n");

			tmp = monitor_read_temp(MONITOR_ADDR_2);
			debug_send_c_wait( tmp>>8);
			debug_send_c_wait( tmp );
			break;

		case 'U':
			tmp = monitor_read_voltage(MONITOR_ADDR_2, MONITOR_U1);
			debug_send_c_wait( tmp>>8 );
			debug_send_c_wait( tmp );
			break;

		case 'V':
			tmp = monitor_read_voltage(MONITOR_ADDR_2, MONITOR_U4);
			debug_send_c_wait( tmp>>8 );
			debug_send_c_wait( tmp );
			break;

		case 'W':
			tmp = monitor_read_voltage(MONITOR_ADDR_2, MONITOR_U2);
			debug_send_c_wait( tmp>>8 );
			debug_send_c_wait( tmp );
			break;

		case 'X':
			tmp = monitor_read_voltage(MONITOR_ADDR_2, MONITOR_U3);
			debug_send_c_wait( tmp>>8 );
			debug_send_c_wait( tmp );
			break;

		case 'I':
			tmp = monitor_read_current(MONITOR_ADDR_1, MONITOR_I1);
			debug_send_c_wait( tmp>>8 );
			debug_send_c_wait( tmp );
			break;

		case 'J':
			tmp = monitor_read_current(MONITOR_ADDR_1, MONITOR_I2);
			debug_send_c_wait( tmp>>8 );
			debug_send_c_wait( tmp );
			break;

		case 'A':
			tmp = monitor_read_voltage(MONITOR_ADDR_1, MONITOR_UVCC);
				debug_send_c_wait( tmp>>8 );
				debug_send_c_wait( tmp );

			tmp = monitor_read_voltage(MONITOR_ADDR_2, MONITOR_UVCC);
				debug_send_c_wait( tmp>>8 );
				debug_send_c_wait( tmp );
			break;

		case '?':
			debug_send_help();
			break;

		default:
			debug_send_c( 0xff );
			break;

		}
	}

#endif /* CFG_SUART_RX */
}


/**
 * Sends status information via software uart
 */
void debug_send_system_info(char *productName, char *productVersion, char *publisher){
#ifdef CFG_SUART_TX

	debug_send_msg( publisher );
	debug_send_msg( "\r\n" );
	debug_send_msg( productName );
	debug_send_msg( " ver. " );
	debug_send_msg( productVersion );
	debug_send_msg( "\r\nid:" );
	debug_send_c_wait( sys_robotID );
	debug_send_msg( "\r\n" );

#endif /* CFG_SUART_TX */
}


/**
 * Sends all available commands
 */
void debug_send_help(void){
	debug_send_msg( "DEBUG COMMANDS:\r\n" );
	debug_send_msg( "abcdefghijklmnoprstuvwzM?" );
}



/**
 * Sends a debug message string
 * via software uart
 */
void debug_send_msg(char *s){
	suart_puts(s);
}

/**
 * Send a byte via software uart
 * Doesn't care about running transmissions!
 */
void debug_send_c(char c){
	suart_putc(c);
}

/**
 * Send a byte via software uart
 * Wait for running transmission to finfish.
 * Can block system!
 */
void debug_send_c_wait(char c){
	suart_putc_wait(c);
}

#endif
