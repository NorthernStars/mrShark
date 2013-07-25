/*
 * control.c
 *
 *  Created on: 29.05.2013
 *      Author: hannes
 */

#include "../headers/sys.h"

/**
 * Initiates motors
 */
void control_init(void){

	// set shutdown io as output
	// and switches ir communication on
	//IR_SD_DDR |= (1<<IR_SD);
	//control_IR_shutdown();

	// initiate uart
	uart_init();

}

/**
 * Gets recieved char from uart
 */
uint8_t control_get(void){
	return uart_getc();
}


/**
 * Shuts IR communictaion down
 */
void control_IR_shutdown(void){
	IR_SD_PORT |= (1<<IR_SD);
}

/**
 * Switches IR communication on
 */
void control_IR_switchon(void){
	IR_SD_PORT &= ~(1<<IR_SD);
}
