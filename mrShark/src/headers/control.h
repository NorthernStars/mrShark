/*
 * control.h
 *
 *  Created on: 29.05.2013
 *      Author: hannes
 */

#ifndef CONTROL_H_
#define CONTROL_H_

// -------- DEFINES --------
#define IR_SD_DDR	DDRD
#define IR_SD_PORT	PORTD
#define IR_SD		PD4

#define BOT_NONE	0xff

// -------- COMMANDS --------
#define CMD_V2_RESERVED			0x00

#define CMD_V2_LEFT_FWD			0x41
#define CMD_V2_LEFT_BWD			0x42
#define CMD_V2_RIGHT_FWD		0x44
#define CMD_V2_RIGHT_BWD		0x47
#define CMD_V2_STOP				0x48
#define CMD_V2_SET_ID			0x4b
#define CMD_V2_LEDS_ON			0x4d
#define CMD_V2_LEDS_OFF			0x4e
#define CMD_V2_PROTOCOL_VERSION	0x50
#define CMD_V2_LED_STAT_ON		0x55
#define CMD_V2_LED_STAT_OFF		0x56
#define CMD_V2_ROBOT_ID			0x5a

#define CMD_V2_LED1_RED			0x63
#define CMD_V2_LED1_GREEN		0x65
#define CMD_V2_LED1_BLUE		0x66

#define CMD_V2_LED2_RED			0x69
#define CMD_V2_LED2_GREEN		0x6a
#define CMD_V2_LED2_BLUE		0x6c

#define CMD_V2_LED3_RED			0x6f
#define CMD_V2_LED3_GREEN		0x71
#define CMD_V2_LED3_BLUE		0x72

#define CMD_V2_LED4_RED			0x74
#define CMD_V2_LED4_GREEN		0x77
#define CMD_V2_LED4_BLUE		0x78

#define CMD_V2_LED_ON			0x7b
#define CMD_V2_LED_OFF			0x7d

#define CMD_V2_SECTION_SEP		0x2b
#define CMD_V2_SEPERATOR		0x2e

#define CMD_V2_TRANS_END		0x59

// -------- COMMANDS --------
#define CTRL_STATE_INIT_READY	0x01
#define CTRL_STATE_REC_BOT_ID	0x02
#define CTRL_STATE_REC_VALUE	0x03

// -------- VARIABLES --------
extern volatile uint8_t ctrl_cmd_motorL;
extern volatile uint8_t ctrl_val_motorL;
extern volatile uint8_t ctrl_flag_motorL;
extern volatile uint8_t ctrl_cmd_motorR;
extern volatile uint8_t ctrl_val_motorR;
extern volatile uint8_t ctrl_flag_motorR;

extern volatile uint8_t ctrl_cmd_id;
extern volatile uint8_t ctrl_flag_id;

// -------- FUNCTIONS --------
void control_init(void);

uint8_t control_getMotorCommand(uint8_t motor);
uint8_t control_getMotorSpeed(uint8_t motor);

void control_send_system_info(char *productName, char *productVersion, char *publisher);
void control_IR_shutdown(void);
void control_IR_switchon(void);

uint8_t control_getCmd(void);

#endif /* CONTROL_H_ */
