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

		#if !defined(CFG_CODE_LEVEL_AVG)
		uint16_t tmp;
		#endif

		// process command
		switch(cmd){

		case 'f':
			motor_set_speed(MOTOR_ADDR_L, 0x50, MOTOR_FORWARD);
			motor_set_speed(MOTOR_ADDR_R, 0x40, MOTOR_FORWARD);
			break;

		case'b':
			motor_set_speed(MOTOR_ADDR_L, 0x40, MOTOR_BACKWARD);
			motor_set_speed(MOTOR_ADDR_R, 0x43, MOTOR_BACKWARD);
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
			debug_send_c( motor_get_speed(MOTOR_ADDR_L), TRUE );
			break;

		case 'n':
			debug_send_c( motor_get_speed(MOTOR_ADDR_R), TRUE );
			break;

		case 'o':
			debug_send_c( motor_get_direction(MOTOR_ADDR_L), TRUE );
			break;

		case 'p':
			debug_send_c( motor_get_direction(MOTOR_ADDR_R), TRUE );
			break;

		case 'd':
			debug_send_c( motor_get_fault(MOTOR_ADDR_L), TRUE );
			break;

		case 'e':
			debug_send_c( motor_get_fault(MOTOR_ADDR_R), TRUE );
			break;

		case 'u':
			motor_clear_fault( MOTOR_ADDR_L );
			break;

		case 'v':
			motor_clear_fault( MOTOR_ADDR_R );
			break;
		#endif

		case 'i':
			debug_send_c( sys_robotID, TRUE );
			break;

		case 'j':
			debug_send_msg( SYS_PUBLISHER, TRUE );
			break;

		case 'k':
			debug_send_msg( SYS_VERSION, TRUE );
			break;

		case 'l':
			debug_send_msg( SYS_NAME, TRUE );
			break;

		case 'M':
			debug_send_c( motor_test(), TRUE );
			break;

		#if !defined(CFG_CODE_LEVEL_AVG)
		case 'T':
			tmp = monitor_read_temp(MONITOR_ADDR_1);
			debug_send_c_wait( tmp>>8, FALSE );
			debug_send_c_wait( tmp, FALSE );

			tmp = monitor_read_temp(MONITOR_ADDR_2);
			debug_send_c_wait( tmp>>8, FALSE );
			debug_send_c_wait( tmp, TRUE );
			break;

		case 'U':
			tmp = monitor_read_voltage(MONITOR_ADDR_2, MONITOR_U1);
			debug_send_c_wait( tmp>>8, FALSE );
			debug_send_c_wait( tmp, TRUE );
			break;

		case 'V':
			tmp = monitor_read_voltage(MONITOR_ADDR_2, MONITOR_U4);
			debug_send_c_wait( tmp>>8, FALSE );
			debug_send_c_wait( tmp, TRUE );
			break;

		case 'W':
			tmp = monitor_read_voltage(MONITOR_ADDR_2, MONITOR_U2);
			debug_send_c_wait( tmp>>8, FALSE );
			debug_send_c_wait( tmp, TRUE );
			break;

		case 'X':
			tmp = monitor_read_voltage(MONITOR_ADDR_2, MONITOR_U3);
			debug_send_c_wait( tmp>>8, FALSE );
			debug_send_c_wait( tmp, TRUE );
			break;

		case 'I':
			tmp = monitor_read_current(MONITOR_ADDR_1, MONITOR_I1);
			debug_send_c_wait( tmp>>8, FALSE );
			debug_send_c_wait( tmp, TRUE );
			break;

		case 'J':
			tmp = monitor_read_current(MONITOR_ADDR_1, MONITOR_I2);
			debug_send_c_wait( tmp>>8, FALSE );
			debug_send_c_wait( tmp, TRUE );
			break;

		case 'A':
			tmp = monitor_read_voltage(MONITOR_ADDR_1, MONITOR_UVCC);
				debug_send_c_wait( tmp>>8, FALSE );
				debug_send_c_wait( tmp, FALSE );

			tmp = monitor_read_voltage(MONITOR_ADDR_2, MONITOR_UVCC);
				debug_send_c_wait( tmp>>8, FALSE );
				debug_send_c_wait( tmp, TRUE );
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
			debug_send_c( 0xff, TRUE );
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

	debug_send_msg( publisher, TRUE );
	debug_send_msg( productName, FALSE );
	debug_send_msg( " ver. ", FALSE );
	debug_send_msg( productVersion, TRUE );
	debug_send_msg( "id:", FALSE );
	debug_send_c_wait( sys_robotID, TRUE );

#endif /* CFG_SUART_TX */
}


/**
 * Sends all available commands
 */
void debug_send_help(void){
	debug_send_msg( "DEBUG COMMANDS:", TRUE );
	debug_send_msg( "abcdefghijklmnoprstuvwzM?", TRUE );

	#if !defined(CFG_CODE_LEVEL_AVG)
	char motors[] = {"motors"};
	char motor[] = {"motor"};
	char animation[] = {"anim."};
	char voltage[] = {"volt."};

	debug_send_msg( "f: ", FALSE);	debug_send_msg(motors, FALSE); debug_send_msg( " fwd", TRUE );
	debug_send_msg( "b: ", FALSE);	debug_send_msg(motors, FALSE); debug_send_msg( " bwd", TRUE );
	debug_send_msg( "z: ", FALSE);	debug_send_msg(motors, FALSE); debug_send_msg( " brake", TRUE );
	debug_send_msg( "g: rgb leds on", TRUE );
	debug_send_msg( "h: rgb leds off", TRUE );
	debug_send_msg( "s: stat led on", TRUE );
	debug_send_msg( "r: stat led off", TRUE );
	debug_send_msg( "c: turn cw", TRUE );
	debug_send_msg( "a: turn ccw", TRUE );
	debug_send_msg( "m: L-", FALSE);	debug_send_msg(motor, FALSE); debug_send_msg( " speed", TRUE );
	debug_send_msg( "n: R-", FALSE);	debug_send_msg(motor, FALSE); debug_send_msg( " speed", TRUE );
	debug_send_msg( "o: L-", FALSE);	debug_send_msg(motor, FALSE); debug_send_msg( " cmd", TRUE );
	debug_send_msg( "p: R-", FALSE);	debug_send_msg(motor, FALSE); debug_send_msg( " cmd", TRUE );
	debug_send_msg( "i: bot ID", TRUE );
	debug_send_msg( "j: publisher", TRUE );
	debug_send_msg( "k: version", TRUE );
	debug_send_msg( "l: name", TRUE );
	debug_send_msg( "d: L-", FALSE);	debug_send_msg(motor, FALSE); debug_send_msg( " faults", TRUE );
	debug_send_msg( "e: R-", FALSE);	debug_send_msg(motor, FALSE); debug_send_msg( " faults", TRUE );
	debug_send_msg( "u: clear L-", FALSE);	debug_send_msg(motor, FALSE); debug_send_msg( " faults", TRUE );
	debug_send_msg( "v: clear R-", FALSE);	debug_send_msg(motor, FALSE); debug_send_msg( " faults", TRUE );
	debug_send_msg( "M: ", FALSE);	debug_send_msg(motors, FALSE);	debug_send_msg( " test", TRUE );
	debug_send_msg( "T: temp.", TRUE );
	debug_send_msg( "U: ", FALSE);	debug_send_msg(voltage, FALSE); debug_send_msg( "1", TRUE );
	debug_send_msg( "V: ", FALSE);	debug_send_msg(voltage, FALSE); debug_send_msg( "2", TRUE );
	debug_send_msg( "W: ", FALSE);	debug_send_msg(voltage, FALSE); debug_send_msg( " bat1", TRUE );
	debug_send_msg( "X: ", FALSE);	debug_send_msg(voltage, FALSE); debug_send_msg( " bat2", TRUE );
	debug_send_msg( "I: cur. L-", FALSE);	debug_send_msg(motor, TRUE);
	debug_send_msg( "J: cur. R-", FALSE);	debug_send_msg(motor, TRUE);
	debug_send_msg( "A: VCCs", TRUE );
	debug_send_msg( "R: red pulsed ", FALSE);	debug_send_msg(animation, TRUE);
	debug_send_msg( "S: strobe ", FALSE);	debug_send_msg(animation, TRUE);
	debug_send_msg( "L: lady ", FALSE);	debug_send_msg(animation, TRUE);
	debug_send_msg( "F: fade ", FALSE);	debug_send_msg(animation, TRUE);
	debug_send_msg( "N: no ", FALSE);	debug_send_msg(animation, TRUE);
	#endif
}



/**
 * Sends a debug message string
 * via software uart
 */
void debug_send_msg(char *s, uint8_t endLine){
	suart_puts(s);
	if( endLine ){
		suart_puts("\n");
	}
}

/**
 * Send a byte via software uart
 * Doesn't care about running transmissions!
 */
void debug_send_c(char c, uint8_t endLine){
	suart_putc(c);
	if( endLine ){
		suart_puts("\n");
	}
}

/**
 * Send a byte via software uart
 * Wait for running transmission to finfish.
 * Can block system!
 */
void debug_send_c_wait(char c, uint8_t endLine){
	suart_putc_wait(c);
	if( endLine ){
		suart_puts("\n");
	}
}

#endif
