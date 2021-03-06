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
uint8_t sys_ee_robotID EEMEM = CFG_BOT_ID;

/**
 * Initiates the complete system
 */
void sys_init(void){

	// initiate power saving
	sys_power_init();

	// read robot id
	sys_robotID = sys_ee_read_robotID();

	// call libraries and modules init functions
	i2c_init();

	// init external marker
	#ifdef CFG_EXTERNAL_MARKER
	marker_init();
	marker_set_loading(0);
	marker_set_led(MARKER_POSITION_LED, MARKER_MODE_PWM1);
	#endif

	// init leds
	led_init();
	led_on(LED_STATUS);
	#ifdef CFG_EXTERNAL_MARKER
	marker_set_loading(1);
	#endif

	// enable onboard i2c
	sys_enable_onboard_i2c();

	// initi control
	control_init();
	#ifdef CFG_EXTERNAL_MARKER
	marker_set_loading(2);
	#endif

	#if !defined(CFG_CODE_LEVEL_AVG) && !defined(CFG_CODE_LEVEL_MIN)
	monitor_init();
	animation_init();
	#endif

	#ifdef CFG_EXTERNAL_MARKER
	marker_set_loading(5);
	#endif

	#ifndef CFG_CODE_LEVEL_MIN
	debug_init();
	#endif

	#ifdef CFG_EXTERNAL_MARKER
	marker_set_loading(6);
	#endif

	// activate interrupts
	sei();

	// check for led test
	#if !defined(CFG_CODE_LEVEL_MIN)
	if( sys_robotID == 0 ){
		led_test();
	}
	#endif

	// motor init
	motor_init();
	#ifdef CFG_EXTERNAL_MARKER
	marker_set_loading(8);
	#endif

	// send system information
	#ifndef CFG_CODE_LEVEL_MIN
	debug_send_system_info(SYS_NAME, SYS_VERSION, SYS_PUBLISHER);
	#endif

	// set marker ID
	#ifdef CFG_EXTERNAL_MARKER
	marker_set_id(sys_robotID);
	#endif

	// set led color green
	led_off(LED_STATUS);

}


/**
 * Initiates power saving
 */
void sys_power_init(void){
	PRR |= (CFG_POWER_DOWN_I2C<<PRTWI)
		| (CFG_POWER_DOWN_SPI<<PRSPI)
		| (CFG_POWER_DOWN_UART<<PRUSART0)
		| (CFG_POWER_DOWN_TIMER0<<PRTIM0)
		| (CFG_POWER_DOWN_TIMER1<<PRTIM1)
		| (CFG_POWER_DOWN_TIMER2<<PRTIM2)
		| (CFG_POWER_DOWN_ADC<<PRADC);
}

/**
 * Suspends system to idel state
 */
void sys_sleep(void){
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_mode();
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

/**
 * Sets the channel/mode of onboard i2c
 */
void sys_set_onboard_i2c(uint8_t channel){
	i2c_writeDataRegOnly( SYS_I2C_ONBOARD_ADDR, channel );
}

/**
 * Reads status of onboard i2c
 */
uint8_t sys_read_onboard_i2c(void){
	i2c_start_wait( SYS_I2C_ONBOARD_ADDR + I2C_READ );
	return i2c_readNak();
}

/**
 * Enables the onboard i2c circuit
 */
void sys_enable_onboard_i2c(void){
	sys_set_onboard_i2c(SYS_I2C_ONBOARD_SEL_CH0);
}

/**
 * Disables the onboard i2c circuit
 */
void sys_disable_onboard_i2c(void){
	sys_set_onboard_i2c(SYS_I2C_ONBOARD_SEL_NONE);
}

