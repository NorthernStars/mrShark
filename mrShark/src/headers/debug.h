/*
 * debug.h
 *
 *  Created on: 29.08.2013
 *      Author: hannes
 */

#ifndef DEBUG_H_
#define DEBUG_H_

// -------- FUNCTIONS --------
void debug_init(void);

void debug_process(void);
void debug_send_system_info(char *productName, char *productVersion, char *publisher);
void debug_send_help(void);

void debug_send_msg(char *s, uint8_t endLine);
void debug_send_c(char c, uint8_t endLine);
void debug_send_c_wait(char c, uint8_t endLine);

#endif /* DEBUG_H_ */
