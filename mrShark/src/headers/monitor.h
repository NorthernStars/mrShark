/*
 * monitor.h
 *
 *  Created on: 29.08.2013
 *      Author: hannes
 */

#ifndef MONITOR_H_
#define MONITOR_H_

// -------- CONFIGURATION --------
#define MONITOR_ADDR_1	0x98
#define MONITOR_ADDR_2 0x9a

#define MONITOR_REG_STATUS		0x00
#define MONITOR_REG_CONTROL		0x01
#define MONITOR_REG_TRIGGER		0x02

#define MONITOR_REG_TEMP_H		0x04
#define MONITOR_REG_TEMP_L		0x05

#define MONITOR_REG_V1_H		0x06
#define MONITOR_REG_V1_L		0x07
#define MONITOR_REG_V2_H		0x08
#define MONITOR_REG_V2_L		0x09
#define MONITOR_REG_V3_H		0x0a
#define MONITOR_REG_V3_L		0x0b
#define MONITOR_REG_V4_H		0x0c
#define MONITOR_REG_V4_L		0x0d

#define MONITOR_REG_VCC_H		0x0e
#define MONITOR_REG_VCC_L		0x0f

#define MONITOR_U1		1
#define MONITOR_U2		2
#define MONITOR_U3		3
#define MONITOR_U4		4
#define MONITOR_UVCC	5

#define MONITOR_I1		1
#define MONITOR_I2		3

#define MONITOR_1_CONFIG		0x1e	// celsius, repeated conversion, mode 2:0, v1-v2, v3-v4
#define MONITOR_2_CONFIG		0x1f	// celsius, repeated conversion, mode 2:0, v1, v2, v3, v4


// -------- FUNCTIONS --------
void monitor_init(void);

uint16_t monitor_read_temp(uint8_t address);
uint16_t monitor_read_voltage(uint8_t address, uint8_t voltage);
uint16_t monitor_read_current(uint8_t address, uint8_t current);

#endif /* MONITOR_H_ */
