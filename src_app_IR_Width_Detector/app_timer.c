/****************************************************************************
 *   $Id:: timer32.c 3635 2010-06-02 00:31:46Z usb00423                     $
 *   Project: NXP LPC11xx 32-bit timer example
 *
 *   Description:
 *     This file contains 32-bit timer code example which include timer
 *     initialization, timer interrupt handler, and related APIs for
 *     timer setup.
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

#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif

#include "chip.h"
#include "board.h"
#include "string.h"
#include "Timer.h"

// Common
#include "Common.h"
#include "app_timer.h"
#include "gpio.h"
#include "Io.h"

sRC_TIME_TABLE 	sRC_TIMETABLE[IR_TBL_MAX];
uint8_t 		bIrTimeIndexIn;
uint8_t 		bIrTimeIndexOut;

sRC_TIME_TABLE 	sRC_TIMETABLE_Output[IR_TBL_MAX];
uint8_t  		bIrTimeIndexIn_Output;
uint8_t  		bIrTimeIndexOut_Output;


#ifdef _MY_UNIT_TEST_

  void IR_RX_TIMER32_0_CAP0_IRQHandler(void) {}
id IR_TX_TIMER32_0_MATCH0_IRQHandler(void) {}

#else

void IR_RX_TIMER32_0_CAP0_IRQHandler(void)
{
	uint32_t 		cnt, temp_level, temp_width;

	cnt = Chip_TIMER_ReadCapture(LPC_TIMER32_0, 0);
	temp_width = TIMER_DIFF32(cnt, LastCaptureTime_IR);
	LastCaptureTime_IR = cnt;
	temp_level = Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, IR_RX_GPIO_PORT_NUM, IR_RX_GPIO_BIT_NUM);

//	if (temp_width > 1000000 )		// Check if width is larger than 1 sec
//	{
//		// Skip pulse-width if it is >= 100ms
//		//temp_width = 0xffffff;
//	}
//	else
	{
		sRC_TIMETABLE[bIrTimeIndexIn].wTimeStamp =	( temp_width );		// 1us count

		if(temp_level==0)	// Please check
		{
			// current level is low -> triggered by falling edge -> previous width is high
			sRC_TIMETABLE[bIrTimeIndexIn].bLevel = 0;
		}
		else
		{
			// current level is high -> triggered by rising edge -> previous width is low
			sRC_TIMETABLE[bIrTimeIndexIn].bLevel = 1;
		}

		cnt = INC_INDEX8(bIrTimeIndexIn, IR_TBL_MAX);
		if(cnt==bIrTimeIndexOut)
		{
			while (1);  // Trap
			//printfs ("ERR:ABC\r\n");
		}
		else
		{
			bIrTimeIndexIn = cnt;
		}
	}
}

#endif // #ifdef _MY_UNIT_TEST_

void IR_Transmit_Buffer_Init(void)
{
    Chip_TIMER_MatchDisableInt(LPC_TIMER32_0, MATCH_0);

	bIrTimeIndexIn_Output  = 0;
	bIrTimeIndexOut_Output = 0;
}

uint8_t IR_Transmit_Buffer_Push(uint32_t temp_level, uint32_t temp_width )
{
	uint32_t temp_index;

	temp_index = INC_INDEX8(bIrTimeIndexIn_Output, IR_TBL_MAX);

	if( temp_index == bIrTimeIndexOut_Output )		// Buffer Overrun
	{
		//putstr("IR_Transmit_Buffer_Push_overrun\r\n");
		return FALSE;
	}
	else
	{
		sRC_TIMETABLE_Output[bIrTimeIndexIn_Output].bLevel     = temp_level;
		sRC_TIMETABLE_Output[bIrTimeIndexIn_Output].wTimeStamp = temp_width;
		bIrTimeIndexIn_Output = temp_index;
	}
	return TRUE;
}

uint8_t IR_Transmit_Buffer_Pop(uint32_t *temp_level, uint32_t *temp_width )
{
	if(bIrTimeIndexOut_Output != bIrTimeIndexIn_Output)
	{
		*temp_level = (uint32_t) sRC_TIMETABLE_Output[bIrTimeIndexOut_Output].bLevel;
		*temp_width = (uint32_t) sRC_TIMETABLE_Output[bIrTimeIndexOut_Output].wTimeStamp;
		bIrTimeIndexOut_Output = INC_INDEX8(bIrTimeIndexOut_Output, IR_TBL_MAX);
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

///******************************************************************************
//**                            End Of File
//******************************************************************************/
