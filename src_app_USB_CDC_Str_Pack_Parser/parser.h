/*
 * parser.h
 *
 *  Created on: 2017年10月26日
 *      Author: Jeremy.Hsiao
 */

#ifndef SRC_APP_USB_CDC_STR_PACK_PARSER_PARSER_H_
#define SRC_APP_USB_CDC_STR_PACK_PARSER_PARSER_H_

typedef enum {
	ENUM_CMD_NOTHING_AVAILABLE = 0,
	ENUM_CMD_STOP_CMD_RECEIVED,
	ENUM_CMD_REPEAT_COUNT_RECEIVED,
	ENUM_CMD_WIDTH_DATA_READY,
    ENUM_CMD_STATE_MAX
} ENUM_CMD_STATUS;

extern void ProcessInputChar(uint8_t input_byte);

extern Bool Read_If_CheckSum_OK(void);
extern ENUM_CMD_STATUS Read_CMD_Status(void);
extern void Clear_CMD_Status(void);
extern void Next_Repeat_Count_Set(uint8_t new_cnt);
extern uint8_t Next_Repeat_Count_Get(void);
extern void Next_PWM_Period_Set(uint32_t new_period);
extern uint32_t Next_PWM_Period_Get(void);
extern void Next_PWM_DutyCycle_Set(uint8_t new_duty_cycle);
extern uint8_t Next_DutyCycle_Period_Get(void);

#endif /* SRC_APP_USB_CDC_STR_PACK_PARSER_PARSER_H_ */
