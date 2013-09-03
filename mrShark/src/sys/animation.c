/*
 * animation.c
 *
 *  Created on: 03.09.2013
 *      Author: hannes
 */

#include "../headers/sys.h"

#ifndef CFG_CODE_LEVEL_MIN
// -------- VARIABLES --------
uint8_t animation_mode = ANIMATION_MODE_NONE;

/**
 * Initiates animation module
 */
void animation_init(void){
	// Initiate timer
	TCCR2A |= (1<<WGM21);							// ctc mode
	TCCR2B |= (1<<CS20) | (1<<CS21) | (1<<CS22);	// prescaler = 1024
	OCR2A = ANIMATION_TMR_COMP;						// set compare match value
	TIMSK2 |= (1<<OCIE2A);							// enable compare match interrupt
}


/**
 * Sets an animation mode
 */
void animation_set_mode(uint8_t mode){
	animation_mode = mode;
}

/**
 * Processes animation
 */
void animation_process(void){
	if( animation_mode == ANIMATION_MODE_RED_PULSED )
		animation_red_pulsed();
	else if( animation_mode == ANIMATION_MODE_FADE )
		animation_fade();
	else if( animation_mode == ANIMATION_MODE_STROBE )
		animation_strobe();
	else if( animation_mode == ANIMATION_MODE_LADY )
		animation_lady();
}

/**
 * Compare Match Interrupt ISR for Timer2
 */
ISR(TIMER2_COMPA_vect){
	// call animation process
	animation_process();
}

/**
 * Red pulsed animation
 */
void animation_red_pulsed(void){
	static uint8_t led = 0x00;
	static uint8_t ledInc = TRUE;

	// set color
	led_all_on();
	led_set_colors(led, 0, 0, LED_N);
	led_set_colors(led, 0, 0, LED_O);
	led_set_colors(led, 0, 0, LED_S);
	led_set_colors(led, 0, 0, LED_W);

	// increase/decrease counter
	if(ledInc)
		led++;
	else
		led--;

	// set increase/decrease
	if( led == 255 )
		ledInc = FALSE;
	if( led == 0 )
		ledInc = TRUE;
}

/**
 * Fade animation
 */
void animation_fade(void){
	#define ANIM_FADE_INC	1
	static uint8_t led_r = 0xff;
	static uint8_t led_g = 0x00;
	static uint8_t led_b = 0x00;

	// fade leds
	if( led_r == 0xff ){
		if( led_b > 0 )
			led_b -= ANIM_FADE_INC;
		else if( led_g < 0xff )
			led_g += ANIM_FADE_INC;
	}

	if( led_g == 0xff ){
		if( led_r > 0 )
			led_r -= ANIM_FADE_INC;
		else if( led_b < 0xff )
			led_b += ANIM_FADE_INC;
	}

	if( led_b == 0xff ){
		if( led_g > 0 )
			led_g -= ANIM_FADE_INC;
		else if( led_r < 0xff )
			led_r += ANIM_FADE_INC;
	}

	// set color
	led_all_on();
	led_set_colors(led_r, led_g, led_b, LED_N);
	led_set_colors(led_r, led_g, led_b, LED_O);
	led_set_colors(led_r, led_g, led_b, LED_S);
	led_set_colors(led_r, led_g, led_b, LED_W);
}

/**
 * LED strobe animation
 */
void animation_strobe(void){
	static uint8_t led = 0x00;
	static uint8_t ledInc = TRUE;

	// set color
	led_all_on();
	led_set_colors(led, led, led, LED_N);
	led_set_colors(led, led, led, LED_O);
	led_set_colors(led, led, led, LED_S);
	led_set_colors(led, led, led, LED_W);

	// increase/decrease counter
	if(ledInc)
		led += 5;
	else
		led -= 5;

	// set increase/decrease
	if( led == 255 )
		ledInc = FALSE;
	if( led == 0 )
		ledInc = TRUE;
}

/**
 * Lady animation
 */
void animation_lady(void){
	static uint8_t led_color = 127;
	static uint8_t led = LED_N;
	static uint8_t ledInc = TRUE;

	// set color
	led_all_off();
	led_on(led);
	led_set_colors(led_color, 0, 255, led);

	// increase/decrease counter
	if(ledInc)
		led_color++;
	else
		led_color--;

	// set increase/decrease
	if( led_color == 255 )
		ledInc = FALSE;
	if( led_color == 127 ){
		ledInc = TRUE;
		if( led != LED_W )
			led = led * 2;
		else
			led = LED_N;
	}
}

#endif
