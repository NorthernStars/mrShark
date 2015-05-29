/*
 * animation.h
 *
 *  Created on: 03.09.2013
 *      Author: hannes
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

// -------- CONFIGURATION --------
#define ANIMATION_PRESCALER		1024		// Timer prescaler
#define ANIMATION_TMR_FREQ		100			// Timer frequency
#define ANIMATION_TMR_COMP		108			// F_CPU / (ANIMATION_PRESCALER * ANIMATION_TMR_FREQ)

// -------- DEFINES --------
#define ANIMATION_MODE_NONE				0
#define ANIMATION_MODE_FADE				1
#define ANIMATION_MODE_STROBE			2
#define ANIMATION_MODE_RED_PULSED		3
#define ANIMATION_MODE_LADY				4
#define ANIMATION_MODE_RAINBOW			5

// -------- VARIABLES --------
extern volatile uint8_t animation_mode;

// -------- FUNCTIONS --------
void animation_init(void);
void animation_set_mode(uint8_t mode);
void animation_process(void);

void animation_red_pulsed(void);
void animation_fade(void);
void animation_strobe(void);
void animation_lady(void);
void animation_rainbow(void);

#endif /* ANIMATION_H_ */
