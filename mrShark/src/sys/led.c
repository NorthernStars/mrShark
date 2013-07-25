/*
 * led.c
 *
 *  Created on: 28.05.2013
 *      Author: hannes
 */

#include "../headers/sys.h"

/**
 * Initiates leds
 */
void led_init(void){

	// enable output ios
	LED1_DDR |= (1<<LED1);
	LED2_DDR |= (1<<LED2);
	LED3_DDR |= (1<<LED3);
	LED4_DDR |= (1<<LED4);

	LED_STAT_DDR |= (1<<LED_STAT);

	COLOR_R_DDR |= (1<<COLOR_R);
	COLOR_G_DDR |= (1<<COLOR_G);
	COLOR_B_DDR |= (1<<COLOR_B);

}

/**
 * Switches one led on
 * Use defined LEDx for setting led number
 */
void led_on(uint8_t led){
	if( led == LED_N )
		LED1_PORT |= (1<<LED1);
	else if( led == LED_O )
		LED2_PORT |= (1<<LED2);
	else if( led == LED_S )
		LED3_PORT |= (1<<LED3);
	else if( led == LED_W )
		LED4_PORT |= (1<<LED4);
	else if( led == LED_STATUS )
		LED_STAT_PORT |= (1<<LED_STAT);
}

/**
 * Switches one led off
 * Use defined LEDx for setting led number
 */
void led_off(uint8_t led){
	if( led == LED_N )
		LED1_PORT &= ~(1<<LED1);
	else if( led == LED_O )
		LED2_PORT &= ~(1<<LED2);
	else if( led == LED_S )
		LED3_PORT &= ~(1<<LED3);
	else if( led == LED_W )
		LED4_PORT &= ~(1<<LED4);
	else if( led == LED_STATUS )
		LED_STAT_PORT &= ~(1<<LED_STAT);
}

/**
 * Switches all leds on
 */
void led_all_on(void){
	led_on(LED_N);
	led_on(LED_O);
	led_on(LED_S);
	led_on(LED_W);
}

/**
 * Switches all leds off
 */
void led_all_off(void){
	led_off(LED_N);
	led_off(LED_O);
	led_off(LED_S);
	led_off(LED_W);
}

/**
 * Sets a rgb color
 */
void led_set_color(uint8_t r, uint8_t g, uint8_t b){

}

/**
 * Switche all colors off
 */
void led_set_allcolors(void){
	COLOR_R_PORT |= (1<<COLOR_R);
	COLOR_G_PORT |= (1<<COLOR_G);
	COLOR_B_PORT |= (1<<COLOR_B);
}

/**
 * Switche all colors off
 */
void led_set_nocolors(void){
	COLOR_R_PORT &= ~(1<<COLOR_R);
	COLOR_G_PORT &= ~(1<<COLOR_G);
	COLOR_B_PORT &= ~(1<<COLOR_B);
}


