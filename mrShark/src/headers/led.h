/*
 * led.h
 *
 *  Created on: 28.05.2013
 *      Author: hannes
 */

#ifndef LED_H_
#define LED_H_

// -------- DEFINES --------
#define LED_STAT_DDR	DDRB
#define LED_STAT_PORT	PORTB

#define LED_STAT	PB2

#define LED1_DDR	DDRD
#define LED1_PORT	PORTD

#define LED2_DDR	DDRD
#define LED2_PORT	PORTD

#define LED3_DDR	DDRC
#define LED3_PORT	PORTC

#define LED4_DDR	DDRC
#define LED4_PORT	PORTC

#define LED1		PD6
#define LED2		PD5
#define LED3		PC3
#define LED4		PC2

#define LED_N		1		// LED1
#define LED_O		2		// LED2
#define LED_S		4		// LED3
#define LED_W		8		// LED4
#define LED_STATUS	16		// LED_STATUS

#define LED_COLOR_R_DDR		DDRD
#define LED_COLOR_R_PORT	PORTD

#define LED_COLOR_G_DDR		DDRB
#define LED_COLOR_G_PORT	PORTB

#define LED_COLOR_B_DDR		DDRB
#define LED_COLOR_B_PORT	PORTB

#define LED_COLOR_R		PD7
#define LED_COLOR_G		PB0
#define LED_COLOR_B		PB1

// -------- VARIABLES --------
struct led_color{
	uint8_t led_on;
	uint8_t color_r;
	uint8_t color_g;
	uint8_t color_b;
};
extern volatile struct led_color led_color_N;
extern volatile struct led_color led_color_O;
extern volatile struct led_color led_color_S;
extern volatile struct led_color led_color_W;

// -------- FUNCTIONS --------
void led_init(void);
void led_init_timer(void);

void led_on(uint8_t led);
void led_off(uint8_t led);

#if !defined(CFG_CODE_LEVEL_AVG) && !defined(CFG_CODE_LEVEL_MIN)
void led_all_on(void);
void led_all_off(void);

void led_set_colors(uint8_t r, uint8_t g, uint8_t b, uint8_t led);
void led_set_color_red(uint8_t r, uint8_t led);
void led_set_color_green(uint8_t g, uint8_t led);
void led_set_color_blue(uint8_t b, uint8_t led);

void led_set_allcolors(void);
void led_set_nocolors(void);
#endif

#endif /* LED_H_ */
