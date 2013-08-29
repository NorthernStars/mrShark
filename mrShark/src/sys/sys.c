/*
 * sys.c
 *
 *  Created on: 28.05.2013
 *      Author: hannes
 */

#include "../headers/sys.h"

// -------- VARIABLES --------
uint8_t sys_robotID = CFG_BOT_ID;
volatile uint8_t sys_showControlTraffic = CFG_SHOW_CONTROL_TRAFFIC;

// -------- EEPROM DATA --------
uint8_t sys_ee_robotID EEMEM;

/**
 * Initiates the complete system
 */
void sys_init(void){

	// call libraries init functions
	i2c_init();
	led_init();

	led_on(LED_STATUS);

	motor_init();
	control_init();
	debug_init();

	sei();

	// send system information
	debug_send_system_info(SYS_NAME, SYS_VERSION, SYS_PUBLISHER);

	// set led color green
	led_off(LED_STATUS);

}

/**
 * Reads robot id from eeprom
 */
uint8_t sys_ee_read_robotID(void){
	uint8_t ret = eeprom_read_byte( &sys_ee_robotID );
	// check if id is available
	if( ret == EEPROM_DEF ){
		// id is not available
		return 0x00;
	}
	return ret;
}

/**
 * Sets a new robot id and writes it to eeprom
 */
void sys_ee_set_robotID(uint8_t robotID){
	sys_robotID = robotID;
	eeprom_update_byte( &sys_ee_robotID, robotID );
}
