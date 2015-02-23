/*
 * marker.h
 *
 *  Created on: 23.02.2015
 *      Author: H. Eilers
 */

#ifndef LIB_MARKER_H
#define LIB_MARKER_H

// -------- GENRAL CONFIGURATION --------
#define MARKER_MODE_ON		0x00	// 0x00 = LOW (on), 0x02 = PWM0, 0x03 = PWM1
#define MARKER_MODE_OFF		0x01	// 0x01 = high impedance (off)
#define MARKER_MODE_OFF_ALL	0x55	// all leds in one register off
#define MARKER_MODE_PWM0	0x02	// led blink at pwm0
#define MARKER_MODE_PWM1	0x03	// led blink at pwm1

#define MARKER_VALUE_PSC0	44		// external marker prescaler blink rate = (PSC + 1)/44 [s]
#define MARKER_VALUE_PWM0	128		// external marker pwm duty cycle = (256 - PWM)/256
#define MARKER_VALUE_PSC1	21		// external marker prescaler blink rate = (PSC + 1)/44 [s]
#define MARKER_VALUE_PWM1	128		// external marker pwm duty cycle = (256 - PWM)/256

// -------- I2C CONFIGURATION --------
#define MARKER_ADDR	0xC0
#define MARKER_PSC0	0x02
#define MARKER_PSC1	0x04
#define MARKER_PWM0	0x03
#define MARKER_PWM1	0x05
#define MARKER_LS0	0x06
#define MARKER_LS1	0x07
#define MARKER_LS2	0x08
#define MARKER_LS3	0x09
#define MARKER_AI	0x10		// auto increment

// -------- FUNCTIONS --------
void marker_init();

void marker_write_ls0(uint8_t data);
void marker_write_ls1(uint8_t data);
void marker_write_ls2(uint8_t data);
void marker_write_ls3(uint8_t data);

void marker_set_all(uint8_t mode);
void marker_set_id(uint8_t robotID);
void marker_set_led(uint8_t led, uint8_t mode);
void marker_set_loading(uint8_t stage);

uint8_t marker_is_available();

// -------- VARIABLES --------
extern uint8_t markerData0;
extern uint8_t markerData1;
extern uint8_t markerData2;
extern uint8_t markerData3;

#endif /* LIB_MARKER_H */
