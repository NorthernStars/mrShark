/*
 * led.c
 *
 *  Created on: 28.05.2013
 *      Author: hannes
 */

#include "../headers/sys.h"

volatile struct led_color led_color_N;
volatile struct led_color led_color_O;
volatile struct led_color led_color_S;
volatile struct led_color led_color_W;

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

	// initate led color structures
	led_color_N.led_number = LED_N;
	led_color_O.led_number = LED_O;
	led_color_S.led_number = LED_S;
	led_color_W.led_number = LED_W;

	// initalize led colors
	led_all_off();
	led_set_nocolors();

	// initalize timer
	led_init_timer();
}

/**
 * Initiates led timer
 */
void led_init_timer(void){
	TCCR0A |= (1<<WGM01);		// CTC-Mode
	TCCR0B |= (1<<CS01);		// prescaler 8
	TIMSK0 |= (1<<OCIE0A);		// eable compare match A interrupt
	OCR0A = 0x00;				// set compare match value
}

/**
 * Switches one led on
 * Use defined LEDx for setting led number
 */
void led_on(uint8_t led){
	if( led == LED_N )
		led_color_N.led_on = 0xff;
	else if( led == LED_O )
		led_color_O.led_on = 0xff;
	else if( led == LED_S )
		led_color_S.led_on = 0xff;
	else if( led == LED_W )
		led_color_W.led_on = 0xff;
	else if( led == LED_STATUS )
		LED_STAT_PORT |= (1<<LED_STAT);
}

/**
 * Switches one led off
 * Use defined LEDx for setting led number
 */
void led_off(uint8_t led){
	if( led == LED_N )
		led_color_N.led_on = 0x00;
	else if( led == LED_O )
		led_color_O.led_on = 0x00;
	else if( led == LED_S )
		led_color_S.led_on = 0x00;
	else if( led == LED_W )
		led_color_W.led_on = 0x00;
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
	led_color_N.color_r = led_color_O.color_r = led_color_S.color_r
			= led_color_W.color_r = 0x00;
	led_color_N.color_g = led_color_O.color_g = led_color_S.color_g
				= led_color_W.color_g = 0x01;
	led_color_N.color_b = led_color_O.color_b = led_color_S.color_b
				= led_color_W.color_b = 0x00;
}

/**
 * Switche all colors off
 */
void led_set_nocolors(void){
	led_color_N.color_r = led_color_N.color_g = led_color_N.color_b = 0x00;
	led_color_O.color_r = led_color_O.color_g = led_color_O.color_b = 0x00;
	led_color_S.color_r = led_color_S.color_g = led_color_S.color_b = 0x00;
	led_color_W.color_r = led_color_W.color_g = led_color_W.color_b = 0x00;
}

/**
 * Timer0 Compare Match Interrupt
 */
ISR( TIMER0_COMPA_vect ){
	static uint8_t pwm = 0x00;						// counting color value

	if(pwm < 0x80)
		COLOR_G_PORT |= (1<<COLOR_G);
	else
		COLOR_G_PORT &= ~(1<<COLOR_G);

	pwm++;
}


