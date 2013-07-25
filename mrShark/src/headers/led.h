/*
 * led.h
 *
 *  Created on: 28.05.2013
 *      Author: hannes
 */

#ifndef LED_H_
#define LED_H_

// -------- DEFINES --------
#define LED_STAT_DDR	DDRD
#define LED_STAT_PORT	PORTD

#define LED_STAT		PD2

#define LED1_DDR	DDRD
#define LED1_PORT	PORTD

#define LED2_DDR	DDRD
#define LED2_PORT	PORTD

#define LED3_DDR	DDRC
#define LED3_PORT	PORTC

#define LED4_DDR	DDRB
#define LED4_PORT	PORTB

#define LED1		PD5
#define LED2		PD6
#define LED3		PC3
#define LED4		PB2

#define LED_N		1		// LED1
#define LED_O		2		// LED2
#define LED_S		3		// LED3
#define LED_W		4		// LED4
#define LED_STATUS	5		// LED_STATUS

#define COLOR_R_DDR	DDRD
#define COLOR_R_PORT	PORTD

#define COLOR_G_DDR	DDRB
#define COLOR_G_PORT	PORTB

#define COLOR_B_DDR	DDRB
#define COLOR_B_PORT	PORTB

#define COLOR_R		PD7
#define COLOR_G		PB0
#define COLOR_B		PB1

// -------- VARIABLES --------


// -------- FUNCTIONS --------
void led_init(void);
void led_on(uint8_t led);
void led_off(uint8_t led);
void led_all_on(void);
void led_all_off(void);
void led_set_color(uint8_t r, uint8_t g, uint8_t b);
void led_set_allcolors(void);
void led_set_nocolors(void);

#endif /* LED_H_ */
