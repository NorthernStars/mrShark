/*
 * monitor.c
 *
 *  Created on: 29.08.2013
 *      Author: hannes
 */

#include "../headers/sys.h"

/**
 * Initiates monitoring module
 */
void monitor_init(void){
	// set configuration
	i2c_writeData(MONITOR_ADDR_1, MONITOR_REG_CONTROL, MONITOR_1_CONFIG);
	i2c_writeData(MONITOR_ADDR_2, MONITOR_REG_CONTROL, MONITOR_2_CONFIG);

	// trigger measurement
	i2c_writeData(MONITOR_ADDR_1, MONITOR_REG_TRIGGER, 0xff);
	i2c_writeData(MONITOR_ADDR_2, MONITOR_REG_TRIGGER, 0xff);
}

/**
 * Reads sensors internal temperature
 * Returns 13bit two complement number with 0.0625°C LSB
 * TEMP = monitor_read_temp() * 0,0625°C
 */
uint16_t monitor_read_temp(uint8_t address){
	uint16_t temp = (i2c_readData(address, MONITOR_REG_TEMP_H) & 0x1f) << 8; // get msb
	temp = temp | i2c_readData(address, MONITOR_REG_TEMP_L);
	return temp;
}

/**
 * Reads voltage from sensor
 * Returns 14bit two complement number with 305.18µV LSB
 * U = monitor_read_voltage() * 305.18µV
 */
uint16_t monitor_read_voltage(uint8_t address, uint8_t voltage){
	uint16_t u = 0x00;
	uint8_t regH = MONITOR_REG_V1_H;
	uint8_t regL = MONITOR_REG_V1_L;

	if( voltage == MONITOR_U2 ){
		regH = MONITOR_REG_V2_H;
		regL = MONITOR_REG_V2_L;
	}
	else if( voltage == MONITOR_U3 ){
		regH = MONITOR_REG_V3_H;
		regL = MONITOR_REG_V3_L;
	}
	else if( voltage == MONITOR_U4 ){
		regH = MONITOR_REG_V4_H;
		regL = MONITOR_REG_V4_L;
	}
	else if( voltage == MONITOR_UVCC ){
		regH = MONITOR_REG_VCC_H;
		regL = MONITOR_REG_VCC_L;
	}

	u = (i2c_readData(address, regH) & 0x7f) << 8;
	u = u | i2c_readData(address, regL);

	return u;
}

/**
 * Readscurrent from sensor
 * Returns 14bit two complement number with 19.42µV/Risense LSB
 * I = monitor_read_current() * (19.42µV/Risense)
 */
uint16_t monitor_read_current(uint8_t address, uint8_t current){
	return monitor_read_voltage(address, current);
}
