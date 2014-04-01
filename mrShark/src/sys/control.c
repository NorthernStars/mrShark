/*
 * control.c
 *
 *  Created on: 29.05.2013
 *      Author: hannes
 */

#include "../headers/sys.h"

// -------- VARIABLES --------
volatile uint8_t ctrl_cmd_motorL = CMD_V2_STOP;
volatile uint8_t ctrl_val_motorL = 0x00;
volatile uint8_t ctrl_flag_motorL = FALSE;
volatile uint8_t ctrl_cmd_motorR = CMD_V2_STOP;
volatile uint8_t ctrl_val_motorR = 0x00;
volatile uint8_t ctrl_flag_motorR = FALSE;

volatile uint8_t ctrl_val_id = 0x00;
volatile uint8_t ctrl_flag_id = FALSE;

volatile uint8_t ctrl_state = CMD_V2_RESERVED;
volatile uint8_t ctrl_protocol_version = 0;
volatile uint8_t ctrl_cur_bot_id = BOT_NONE;


/**
 * Initiates motors
 */
void control_init(void){

	// set shutdown io as output
	IR_SD_DDR |= (1<<IR_SD);

	// initiate uart
	uart_init();

	// enable uart interrupt
	UCSR0B |= (1<<RXCIE0);

}

/**
 * Returns direction command of a motor and resets flag
 */
uint8_t control_getMotorCommand(uint8_t motor){
	uint8_t cmd;

	// get command
	if( motor == MOTOR_ADDR_L ){
		ctrl_flag_motorL = FALSE;
		cmd = ctrl_cmd_motorL;
	}
	else{
		ctrl_flag_motorR = FALSE;
		cmd = ctrl_cmd_motorR;
	}

	// translate command to motor command
	if( cmd == CMD_V2_STOP )
		return MOTOR_BRAKE;
	else if( cmd == CMD_V2_LEFT_FWD || cmd == CMD_V2_RIGHT_FWD )
		return MOTOR_FORWARD;
	else
		return MOTOR_BACKWARD;
}

/**
 * Returns speed value of a motor and resets flag
 */
uint8_t control_getMotorSpeed(uint8_t motor){
	if(motor == MOTOR_ADDR_L){
		ctrl_flag_motorL = FALSE;
		return ctrl_val_motorL;
	}
	else{
		ctrl_flag_motorR = FALSE;
		return  ctrl_val_motorR;
	}
}

/**
 * Returns the robot id to set and resets flag
 */
uint8_t control_getRobotID(){
	ctrl_flag_id = FALSE;
	return ctrl_val_id;
}

/**
 * Gets recieved cmd from uart
 */
uint8_t control_getCmd(void){
	return uart_getc();
}

/**
 * Shuts IR communictaion down
 */
void control_IR_shutdown(void){
	IR_SD_PORT |= (1<<IR_SD);
}

/**
 * Switches IR communication on
 */
void control_IR_switchon(void){
	IR_SD_PORT &= ~(1<<IR_SD);
}

/**
 * Interrupt service routine for recieving ir command
 */
ISR(USART_RX_vect){

	uint8_t cmd = UDR0;

	// command control state machine for protocol version 2
	if( ctrl_state == CMD_V2_RESERVED && cmd == CMD_V2_PROTOCOL_VERSION ){
		// transimissison started
		ctrl_state = CMD_V2_PROTOCOL_VERSION;
		ctrl_protocol_version = 0;
		ctrl_cur_bot_id = BOT_NONE;
	}
	else if( ctrl_state == CMD_V2_PROTOCOL_VERSION ){
		// getting protocol version
		ctrl_protocol_version = cmd;
		ctrl_state = CTRL_STATE_INIT_READY;
	}
	else if( ctrl_state != CMD_V2_RESERVED && ctrl_protocol_version == 2 ){
		// getting something for protocol version 2
		switch(ctrl_state){

		case CTRL_STATE_INIT_READY:
			if( cmd == CMD_V2_SECTION_SEP ){
				// first section in transmission started
				ctrl_state = CMD_V2_SECTION_SEP;
				ctrl_cur_bot_id = BOT_NONE;
			}
			else
				ctrl_state = CMD_V2_RESERVED;
			break;

		default:

			if( ctrl_state == CMD_V2_SECTION_SEP || ctrl_state == CMD_V2_SEPERATOR ){
				// recieved command after seperator
				ctrl_state = cmd;
			}
			else if( ctrl_state == CMD_V2_ROBOT_ID ){
				// recvied robot id value
				ctrl_cur_bot_id = cmd;
				ctrl_state = CTRL_STATE_REC_BOT_ID;
			}
			else if( ctrl_state == CTRL_STATE_REC_BOT_ID && (cmd == CMD_V2_SEPERATOR || cmd == CMD_V2_SECTION_SEP) )
				// recieved command after seperator
				ctrl_state = cmd;
			else if( ctrl_state == CTRL_STATE_REC_VALUE && (cmd == CMD_V2_SEPERATOR || cmd == CMD_V2_SECTION_SEP) )
				// recieved seperator after value
				ctrl_state = cmd;
			else if( ctrl_cur_bot_id != BOT_NONE ){
				// got a value after command (with set bot id)

				// check if command is for this bot or transmission ends
				if( ctrl_cur_bot_id == sys_robotID || ctrl_state == CMD_V2_TRANS_END ){
					#if CFG_SHOW_CONTROL_TRAFFIC
					if( sys_showControlTraffic )
						led_on(LED_STATUS);
					#endif

					// process command
					uint8_t err = 0x00;
					switch(ctrl_state){

					case CMD_V2_LEFT_FWD:
						ctrl_cmd_motorL = CMD_V2_LEFT_FWD;
						ctrl_val_motorL = cmd;
						ctrl_flag_motorL = TRUE;
						break;

					case CMD_V2_LEFT_BWD:
						ctrl_cmd_motorL = CMD_V2_LEFT_BWD;
						ctrl_val_motorL = cmd;
						ctrl_flag_motorL = TRUE;
						break;

					case CMD_V2_RIGHT_FWD:
						ctrl_cmd_motorR = CMD_V2_RIGHT_FWD;
						ctrl_val_motorR = cmd;
						ctrl_flag_motorR = TRUE;
						break;

					case CMD_V2_RIGHT_BWD:
						ctrl_cmd_motorR = CMD_V2_RIGHT_BWD;
						ctrl_val_motorR = cmd;
						ctrl_flag_motorR = TRUE;
						break;

					case CMD_V2_STOP:
						ctrl_cmd_motorL = CMD_V2_STOP;
						ctrl_cmd_motorR = CMD_V2_STOP;
						ctrl_flag_motorL = TRUE;
						ctrl_flag_motorR = TRUE;
						break;

					#if !defined(CFG_CODE_LEVEL_AVG) && !defined(CFG_CODE_LEVEL_MIN)
					case CMD_V2_LED_ANIMATION:
						animation_set_mode(cmd);
						break;

					case CMD_V2_LEDS_ON:
						led_all_on();
						break;

					case CMD_V2_LEDS_OFF:
						led_all_off();
						break;

					case CMD_V2_LED1_RED:
						led_set_color_red(cmd, LED_N);
						break;

					case CMD_V2_LED1_GREEN:
						led_set_color_green(cmd, LED_N);
						break;

					case CMD_V2_LED1_BLUE:
						led_set_color_blue(cmd, LED_N);
						break;

					case CMD_V2_LED2_RED:
						led_set_color_red(cmd, LED_O);
						break;

					case CMD_V2_LED2_GREEN:
						led_set_color_green(cmd, LED_O);
						break;

					case CMD_V2_LED2_BLUE:
						led_set_color_blue(cmd, LED_O);
						break;

					case CMD_V2_LED3_RED:
						led_set_color_red(cmd, LED_S);
						break;

					case CMD_V2_LED3_GREEN:
						led_set_color_green(cmd, LED_S);
						break;

					case CMD_V2_LED3_BLUE:
						led_set_color_blue(cmd, LED_S);
						break;

					case CMD_V2_LED4_RED:
						led_set_color_red(cmd, LED_W);
						break;

					case CMD_V2_LED4_GREEN:
						led_set_color_green(cmd, LED_W);
						break;

					case CMD_V2_LED4_BLUE:
						led_set_color_blue(cmd, LED_W);
						break;

					case CMD_V2_LED_ON:
						led_on(cmd);
						break;

					case CMD_V2_LED_OFF:
						led_off(cmd);
						break;
					#endif

					case CMD_V2_LED_STAT_ON:
						led_on(LED_STATUS);
						sys_showControlTraffic = FALSE;
						break;

					case CMD_V2_LED_STAT_OFF:
						led_off(LED_STATUS);
						sys_showControlTraffic = CFG_SHOW_CONTROL_TRAFFIC;
						break;

					case CMD_V2_SET_ID:
						ctrl_val_id = cmd;
						ctrl_flag_id = TRUE;
						break;

					case CMD_V2_TRANS_END:
						ctrl_state = CMD_V2_RESERVED;
						ctrl_protocol_version = 0;
						ctrl_cur_bot_id = BOT_NONE;

						#if CFG_SHOW_CONTROL_TRAFFIC
						if( sys_showControlTraffic )
							led_off(LED_STATUS);
						#endif

						err = 0x01;
						break;

					default:
						// error no command found for value
						err = 0xff;
						break;
					}

					if( err == 0xff )
						// reset state on error
						ctrl_state = CMD_V2_RESERVED;
					else if( !err )
						// recieved value
						ctrl_state = CTRL_STATE_REC_VALUE;

				}
				else
					// skip value and command
					ctrl_state = CTRL_STATE_REC_VALUE;


			}
			else{
				ctrl_state = CMD_V2_RESERVED;
			}

			break;

		}
	}
	else{
		ctrl_state = CMD_V2_RESERVED;
	}


}
