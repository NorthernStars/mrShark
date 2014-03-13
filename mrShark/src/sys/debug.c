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

		#if !defined(CFG_CODE_LEVEL_AVG) && !defined(CFG_CODE_LEVEL_MIN)
		uint16_t tmp;
		#endif

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

		#if !defined(CFG_CODE_LEVEL_AVG) && !defined(CFG_CODE_LEVEL_MIN)
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

		case 'R':
			animation_set_mode(ANIMATION_MODE_RED_PULSED);
			break;

		case 'S':
			animation_set_mode(ANIMATION_MODE_STROBE);
			break;

		case 'F':
			animation_set_mode(ANIMATION_MODE_FADE);
			break;

		case 'L':
			animation_set_mode(ANIMATION_MODE_LADY);
			break;

		case 'N':
			animation_set_mode(ANIMATION_MODE_NONE);
			break;
		#endif

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
	debug_send_msg( "abcdefghijklmnoprstuvwzM?\r\n" );

	#if !defined(CFG_CODE_LEVEL_AVG) && !defined(CFG_CODE_LEVEL_MIN)
	char motors[] = {"motors"};
	char motor[] = {"motor"};
	char animation[] = {"anim."};
	char voltage[] = {"volt."};

	debug_send_msg( "f: ");	debug_send_msg(motors); debug_send_msg( " fwd\r\n" );
	debug_send_msg( "b: ");	debug_send_msg(motors); debug_send_msg( " bwd\r\n" );
	debug_send_msg( "z: ");	debug_send_msg(motors); debug_send_msg( " brake\r\n" );
	debug_send_msg( "g: rgb leds on\r\n" );
	debug_send_msg( "h: rgb leds off\r\n" );
	debug_send_msg( "s: stat led on\r\n" );
	debug_send_msg( "r: stat led off\r\n" );
	debug_send_msg( "c: turn cw\r\n" );
	debug_send_msg( "a: turn ccw\r\n" );
	debug_send_msg( "m: L-");	debug_send_msg(motor); debug_send_msg( " speed\r\n" );
	debug_send_msg( "n: R-");	debug_send_msg(motor); debug_send_msg( " speed\r\n" );
	debug_send_msg( "o: L-");	debug_send_msg(motor); debug_send_msg( " cmd\r\n" );
	debug_send_msg( "p: R-");	debug_send_msg(motor); debug_send_msg( " cmd\r\n" );
	debug_send_msg( "i: bot ID\r\n" );
	debug_send_msg( "j: publisher\r\n" );
	debug_send_msg( "k: version\r\n" );
	debug_send_msg( "l: name\r\n" );
	debug_send_msg( "d: L-");	debug_send_msg(motor); debug_send_msg( " faults\r\n" );
	debug_send_msg( "e: R-");	debug_send_msg(motor); debug_send_msg( " faults\r\n" );
	debug_send_msg( "u: clear L-");	debug_send_msg(motor); debug_send_msg( " faults\r\n" );
	debug_send_msg( "v: clear R-");	debug_send_msg(motor); debug_send_msg( " faults\r\n" );
	debug_send_msg( "M: ");	debug_send_msg(motors);	debug_send_msg( " test\r\n" );
	debug_send_msg( "T: temp.\r\n" );
	debug_send_msg( "U: ");	debug_send_msg(voltage); debug_send_msg( "1\r\n" );
	debug_send_msg( "V: ");	debug_send_msg(voltage); debug_send_msg( "2\r\n" );
	debug_send_msg( "W: ");	debug_send_msg(voltage); debug_send_msg( " bat1\r\n" );
	debug_send_msg( "X: ");	debug_send_msg(voltage); debug_send_msg( " bat2\r\n" );
	debug_send_msg( "I: cur. L-");	debug_send_msg(motor); debug_send_msg( "\r\n" );
	debug_send_msg( "J: cur. R-");	debug_send_msg(motor); debug_send_msg( "\r\n" );
	debug_send_msg( "A: VCCs\r\n" );
	debug_send_msg( "R: red pulsed ");	debug_send_msg(animation); debug_send_msg( "\r\n" );
	debug_send_msg( "S: strobe ");	debug_send_msg(animation); debug_send_msg( "\r\n" );
	debug_send_msg( "L: lady ");	debug_send_msg(animation); debug_send_msg( "\r\n" );
	debug_send_msg( "F: fade ");	debug_send_msg(animation); debug_send_msg( "\r\n" );
	debug_send_msg( "N: no ");	debug_send_msg(animation); debug_send_msg( "\r\n" );
	#endif
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
