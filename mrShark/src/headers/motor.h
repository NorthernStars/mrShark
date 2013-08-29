/*
 * motor.h
 *
 *  Created on: 28.05.2013
 *      Author: hannes
 */

#ifndef MOTOR_H_
#define MOTOR_H_

// -------- DEFINES --------
#define MOTOR_ADDR_L		0xC0
#define MOTOR_ADDR_R		0xC4

#define MOTOR_REG_CONTROL	0x00
#define MOTOR_REG_FAULT		0x01

#define MOTOR_STANDBY		0x00
#define MOTOR_FORWARD		0x01
#define MOTOR_BACKWARD		0x02
#define	MOTOR_BRAKE			0x03

// refer to datasheet before changing the next defines.
// values are for an DRV8830 h-bridge motor driver
#define MOTOR_SPEED_MIN		0x06	// for internal use only. use 0xff for setting full speed!
#define MOTOR_SPEED_MAX		0x29	// for internal use only. use 0x00 for settings min speed!

#define MOTOR_SPEED_HALF	0x80

// -------- FAULT CONDITIONS --------
#define MOTOR_FAULT_ILIMIT	16
#define MOTOR_FAULT_OTS		8
#define MOTOR_FAULT_UVLO	4
#define MOTOR_FAULT_OCP		2
#define MOTOR_FAULT			1

#define MOTOR_FAULT_MASK	0x1f
#define MOTOR_FAULT_CLEAR	0x80

// -------- VARIABLES --------
extern uint8_t motor_left_cmd;
extern uint8_t motor_left_speed;
extern uint8_t motor_right_cmd;
extern uint8_t motor_right_speed;

// -------- FUNCTIONS --------
void motor_init(void);
uint8_t motor_test(void);

void motor_set_speed(uint8_t address, uint16_t speed, uint8_t direction);
void motor_brake(uint8_t address);
void motor_all_brake(void);

uint8_t motor_get_direction(uint8_t address);
uint8_t motor_get_speed(uint8_t address);

uint8_t motor_get_fault(uint8_t address);
void motor_clear_fault(uint8_t address);

#endif /* MOTOR_H_ */
