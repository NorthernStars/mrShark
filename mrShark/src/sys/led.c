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

	LED_COLOR_R_DDR |= (1<<LED_COLOR_R);
	LED_COLOR_G_DDR |= (1<<LED_COLOR_G);
	LED_COLOR_B_DDR |= (1<<LED_COLOR_B);

	// initalize led colors
	led_all_off();
	led_set_nocolors();

	// initalize timer 0
	led_init_timer();
}

/**
 * Initiates led timer
 */
void led_init_timer(void){
	TCCR0A |= (1<<WGM01);		// CTC-Mode
	TCCR0B |= (1<<CS00);		// prescaler 1
	TIMSK0 |= (1<<OCIE0A);		// eable compare match A interrupt
	OCR0A = 0x6c;				// set compare match value to 108 (0x6c) > 100 Hz PWM
	//OCR0A = 0x36;				// set compare match value to 54 (0x36) > 200 Hz PWM
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
void led_set_colors(uint8_t r, uint8_t g, uint8_t b, uint8_t led){
	if( led == LED_N ){
		led_color_N.color_r = r;
		led_color_N.color_g = g;
		led_color_N.color_b = b;
	}
	else if( led == LED_O ){
		led_color_O.color_r = r;
		led_color_O.color_g = g;
		led_color_O.color_b = b;
	}
	else if( led == LED_S ){
		led_color_S.color_r = r;
		led_color_S.color_g = g;
		led_color_S.color_b = b;
	}
	else if( led == LED_W ){
		led_color_W.color_r = r;
		led_color_W.color_g = g;
		led_color_W.color_b = b;
	}
}

/**
 * Sets the red color of a led
 */
void led_set_color_red(uint8_t r, uint8_t led){
	if( led == LED_N )
		led_color_N.color_r = r;
	else if( led == LED_O )
		led_color_O.color_r = r;
	else if( led == LED_S )
		led_color_S.color_r = r;
	else if( led == LED_W )
		led_color_W.color_r = r;
}

/**
 * Sets the green color of a led
 */
void led_set_color_green(uint8_t g, uint8_t led){
	if( led == LED_N )
		led_color_N.color_g = g;
	else if( led == LED_O )
		led_color_O.color_g = g;
	else if( led == LED_S )
		led_color_S.color_g = g;
	else if( led == LED_W )
		led_color_W.color_g = g;
}

/**
 * Sets the blue color of a led
 */
void led_set_color_blue(uint8_t b, uint8_t led){
	if( led == LED_N )
		led_color_N.color_b = b;
	else if( led == LED_O )
		led_color_O.color_b = b;
	else if( led == LED_S )
		led_color_S.color_b = b;
	else if( led == LED_W )
		led_color_W.color_b = b;
}

/**
 * Switche all colors off
 */
void led_set_allcolors(void){
	led_color_N.color_r = led_color_O.color_r = led_color_S.color_r
			= led_color_W.color_r = 0xff;
	led_color_N.color_g = led_color_O.color_g = led_color_S.color_g
				= led_color_W.color_g = 0xff;
	led_color_N.color_b = led_color_O.color_b = led_color_S.color_b
				= led_color_W.color_b = 0xff;
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
	static uint8_t pwm = 0x00;			// pwm counter
	static uint8_t led = 0;				// led counter
	struct led_color cur_led = led_color_N;	// current led

	// reset leds
	LED1_PORT &= ~(1<<LED1);
	LED2_PORT &= ~(1<<LED2);
	LED3_PORT &= ~(1<<LED3);
	LED4_PORT &= ~(1<<LED4);

	// enable led
	if( led == 0 && led_color_N.led_on ){
		LED1_PORT |= (1<<LED1);
		cur_led = led_color_N;
	}
	else if( led == 1 && led_color_O.led_on ){
		LED2_PORT |= (1<<LED2);
		cur_led = led_color_O;
	}
	else if( led == 2 && led_color_S.led_on ){
		LED3_PORT |= (1<<LED3);
		cur_led = led_color_S;
	}
	else if( led == 3 && led_color_W.led_on ){
		LED4_PORT |= (1<<LED4);
		cur_led = led_color_W;
	}

	// set color pwm
	if( cur_led.led_on ){
		if(pwm < cur_led.color_r)
			LED_COLOR_R_PORT |= (1<<LED_COLOR_R);
		else
			LED_COLOR_R_PORT &= ~(1<<LED_COLOR_R);

		if(pwm < cur_led.color_g)
			LED_COLOR_G_PORT |= (1<<LED_COLOR_G);
		else
			LED_COLOR_G_PORT &= ~(1<<LED_COLOR_G);

		if(pwm < cur_led.color_b)
			LED_COLOR_B_PORT |= (1<<LED_COLOR_B);
		else
			LED_COLOR_B_PORT &= ~(1<<LED_COLOR_B);
	}
	else{
		LED_COLOR_R_PORT &= ~(1<<LED_COLOR_R);
		LED_COLOR_G_PORT &= ~(1<<LED_COLOR_G);
		LED_COLOR_B_PORT &= ~(1<<LED_COLOR_B);
	}

	//manage led counter
	if( led > 3 )
		led = 0;
	if( !pwm )
		led++;

	// increase pwm counter
	pwm++;
}


