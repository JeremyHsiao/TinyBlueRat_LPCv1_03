/****************************************************************************
 *   $Id:: timer32.h 3635 2010-06-02 00:31:46Z usb00423                     $
 *   Project: NXP LPC11xx software example
 *
 *   Description:
 *     This file contains definition and prototype for 32-bit timer 
 *     configuration.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#ifndef _APP_TIMER_H_
#define _APP_TIMER_H_

extern void 			IR_Transmit_Buffer_Init(void);
extern uint8_t 			IR_Transmit_Buffer_Push(uint32_t temp_level, uint32_t temp_width );
extern uint8_t 			IR_Transmit_Buffer_Pop(uint32_t *temp_level, uint32_t *temp_width );

typedef struct _RC_TIME_TABLE
{
	uint32_t  wTimeStamp;  	// width
	uint8_t   bLevel; 		// high-low level
}sRC_TIME_TABLE;

#define IR_TBL_MAX      250
extern sRC_TIME_TABLE 	sRC_TIMETABLE[IR_TBL_MAX];
extern uint8_t 			bIrTimeIndexIn;
extern uint8_t 			bIrTimeIndexOut;
extern sRC_TIME_TABLE 	sRC_TIMETABLE_Output[IR_TBL_MAX];
extern uint8_t 			bIrTimeIndexIn_Output;
extern uint8_t 			bIrTimeIndexOut_Output;

#endif /* end _APP_TIMER_H_ */
/*****************************************************************************
**                            End Of File
******************************************************************************/
