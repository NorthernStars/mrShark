/*
 * marker.c
 *
 *  Created on: 23.02.2015
 *      Author: H. Eilers
 */


#include "../../headers/sys.h"

#ifdef CFG_EXTERNAL_MARKER

// -------- VARIABLES --------
uint8_t markerData0 = 0x00;
uint8_t markerData1 = 0x00;
uint8_t markerData2 = 0x00;
uint8_t markerData3 = 0x00;

/**
 * Initiates marker
 */
void marker_init(){
	if( marker_is_available() ){

		sys_disable_onboard_i2c();

		// write configuration
		i2c_writeData( MARKER_ADDR, MARKER_PSC0, MARKER_VALUE_PSC0 );
		i2c_writeData( MARKER_ADDR, MARKER_PSC1, MARKER_VALUE_PSC1 );
		i2c_writeData( MARKER_ADDR, MARKER_PWM0, MARKER_VALUE_PWM0 );
		i2c_writeData( MARKER_ADDR, MARKER_PWM1, MARKER_VALUE_PWM1 );
		i2c_writeData( MARKER_ADDR, MARKER_LS0, MARKER_MODE_OFF_ALL );
		i2c_writeData( MARKER_ADDR, MARKER_LS1, MARKER_MODE_OFF_ALL );
		i2c_writeData( MARKER_ADDR, MARKER_LS2, MARKER_MODE_OFF_ALL );

		// switch all leds off
		marker_write_ls0(MARKER_MODE_OFF_ALL);
		marker_write_ls1(MARKER_MODE_OFF_ALL);
		marker_write_ls2(MARKER_MODE_OFF_ALL);
		marker_write_ls3(MARKER_MODE_OFF_ALL);

		sys_enable_onboard_i2c();

	}
}

/**
 * Writes data to register MARKER_LS0.
 */
void marker_write_ls0(uint8_t data){
	i2c_writeData( MARKER_ADDR, MARKER_LS0, data );
	markerData0 = data;
}

/**
 * Writes data to register MARKER_LS1.
 */
void marker_write_ls1(uint8_t data){
	i2c_writeData( MARKER_ADDR, MARKER_LS1, data );
	markerData1 = data;
}

/**
 * Writes data to register MARKER_LS2.
 */
void marker_write_ls2(uint8_t data){
	i2c_writeData( MARKER_ADDR, MARKER_LS2, data );
	markerData2 = data;
}

/**
 * Writes data to register MARKER_LS3.
 */
void marker_write_ls3(uint8_t data){
	i2c_writeData( MARKER_ADDR, MARKER_LS3, data );
	markerData3 = data;
}


/**
 * Sets all leds to same mode
 */
void marker_set_all(uint8_t mode){
	if( marker_is_available() ){

		sys_disable_onboard_i2c();
		uint8_t data = mode | (mode << 2) | (mode << 4) | (mode << 6);

		marker_write_ls0(data);
		marker_write_ls1(data);
		marker_write_ls2(data);
		marker_write_ls3(data);
		sys_enable_onboard_i2c();

	}
}

/**
 * Set mode of led
 */
void marker_set_led(uint8_t led, uint8_t mode){

	sys_disable_onboard_i2c();

	if( marker_is_available() ){

		// set register and led number
		uint8_t reg = MARKER_LS0;
		uint8_t data = markerData0;

		if( led > 11 ){
			reg = MARKER_LS3;
			led -= 12;
			data = markerData3;
		}
		else if( led > 7 ){
			reg = MARKER_LS2;
			led -= 8;
			data = markerData2;
		}
		else if( led > 3 ){
			reg = MARKER_LS1;
			led -= 4;
			data = markerData1;
		}

		led *= 2;

		// set new data
		data &= ~(0x03 << led);
		data |= (mode << led);

		// write data
		if( reg == MARKER_LS0 ) marker_write_ls0(data);
		else if( reg == MARKER_LS1 ) marker_write_ls1(data);
		else if( reg == MARKER_LS2 ) marker_write_ls2(data);
		else marker_write_ls3(data);

	}

	sys_enable_onboard_i2c();

}

/**
 * Sets marker to robot id
 */
void marker_set_id(uint8_t robotID){
	if( marker_is_available() ){

		sys_disable_onboard_i2c();
		uint8_t bEins = ( robotID%2 + (robotID >> 1)%2 + (robotID >> 3)%2 + (robotID >> 4)%2 ) % 2;
		uint8_t bZwei = ( robotID%2 + (robotID >> 2)%2 + (robotID >> 3)%2 ) % 2;
		uint8_t bVier = ( (robotID >> 1)%2 + (robotID >> 2)%2 + (robotID >> 3)%2 ) % 2;
		uint8_t bAcht = ( (robotID >> 4)%2 ) % 2;

		uint8_t vData0 =
				( bEins ? MARKER_MODE_OFF : MARKER_MODE_ON )
				| ( bZwei? MARKER_MODE_OFF << 2 : MARKER_MODE_ON << 2 )
				| ( robotID%2 ? MARKER_MODE_OFF << 4 : MARKER_MODE_ON << 4 )
				| ( bVier ? MARKER_MODE_OFF << 6 : MARKER_MODE_ON << 6 );
		uint8_t vData1 =
				( (robotID >> 1)%2 ? MARKER_MODE_OFF : MARKER_MODE_ON )
				| ( (robotID >> 2)%2 ? MARKER_MODE_OFF << 2 : MARKER_MODE_ON << 2 )
				| ( (robotID >> 3)%2 ? MARKER_MODE_OFF << 4 : MARKER_MODE_ON << 4 )
				| ( bAcht ? MARKER_MODE_OFF << 6 : MARKER_MODE_ON << 6 );
		uint8_t vData2 = 0x54
				| ( (robotID >> 4)%2 ? MARKER_MODE_OFF : MARKER_MODE_ON );

		// set leds
		marker_write_ls0( vData0 );
		marker_write_ls1( vData1 );
		marker_write_ls2( vData2 );
		marker_write_ls3( MARKER_MODE_OFF_ALL );

		#ifdef CFG_EXTERNAL_MARKER_POSITION_LED
		marker_set_led( MARKER_POSITION_LED, MARKER_MODE_ON );
		#endif

		sys_enable_onboard_i2c();

	}
}

/**
 * Sets all leds from 0 to stage to MARKER_MODE_ON
 * and led stage to MARKER_MODE_PWM1.
 */
void marker_set_loading(uint8_t stage){
	if( marker_is_available() ){

		uint8_t i;
		for( i=0; i < stage; i++ ){
			marker_set_led(i, MARKER_MODE_ON);
		}
		marker_set_led(stage, MARKER_MODE_PWM1);

	}
}

/**
 * returns TRUE if marker i2c device is available
 */
uint8_t marker_is_available(){
	sys_disable_onboard_i2c();

	if( !i2c_start(MARKER_ADDR) ){
		sys_enable_onboard_i2c();
		return TRUE;
	}

	sys_enable_onboard_i2c();
	return FALSE;
}

#endif
