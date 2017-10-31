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

volatile uint32_t		IR_Transmitter_Running;

#ifdef _MY_UNIT_TEST_

void IR_RX_TIMER32_0_CAP0_IRQHandler(void) {}
void IR_TX_TIMER32_0_MATCH0_IRQHandler(void) {}

#else

void IR_RX_TIMER32_0_CAP0_IRQHandler(void)
{
}

void IR_TX_TIMER32_0_MATCH0_IRQHandler(void)
{
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

//
//
//

uint32_t Check_PWM_Pulse_Width(uint32_t temp_width)
{
	// Error prevention
	// Compare based on the same ground
	if((temp_width*(TIMER0_PRESCALER)*(TIMER0_1uS_CNT))<PWM_period)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void IR_Transmit_Buffer_StartSend(void)
{
	uint32_t temp_level;
	uint32_t temp_width;
	uint32_t temp_tc, temp_mr0;

	if (IR_Transmitter_Running!=0)
	{
	  return;			// already running, no need to start timer match and interrupt
	}

	// Get next pulse width and level
	if(IR_Transmit_Buffer_Pop(&temp_level, &temp_width)!=FALSE)
	{
//		// Error prevention
//		if (Check_PWM_Pulse_Width(temp_width)==FALSE)
//		{
//			printfs("timer32.c L834\n");
//		}

		// Please set up first pulse here
		Setup_IR_PWM_Pulse_by_IR_Level(temp_level);

		// Load Timer0_MATCH first match value (based on TC) and enable interrupt here
		temp_tc = Chip_TIMER_ReadCount(LPC_TIMER32_0);
		temp_mr0 = (temp_width*TIMER0_1uS_CNT) + temp_tc;
		Chip_TIMER_SetMatch(LPC_TIMER32_0,MATCH_0,temp_mr0); // MR0 Match for IR Transmitter

		Chip_TIMER_MatchEnableInt(LPC_TIMER32_0,MATCH_0); /* Interrupt/Reset on MRx */
		// Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC.
		IR_Transmitter_Running = 1;
	}
	else
	{
		// printf("Nothing to send\r\n");
		// Nothing to send
	}
}

void Setup_IR_PWM_Pulse_by_IR_Level(uint32_t bLevel)
{
	uint32_t	temp;
	if(bLevel != 0)
	{
		temp = (PWM_period*PWM_duty_cycle)/100;  /* Duty cycle X% output on PIO1_1 */
	}
	else
	{
		temp = ~(0x1);  /* (almost, for a very long time) always low */
	}

	//Debug Purpose I/O
	Chip_GPIO_WritePortBit(LPC_GPIO_PORT, TEST_OUT1_GPIO_PORT_NUM, TEST_OUT1_GPIO_BIT_NUM, (bLevel!=0)?0:1 );
	//Set_LED(0);
	//

	Chip_TIMER_SetMatch(LPC_TIMER32_1, MATCH_0, temp);
	Chip_TIMER_Reset(LPC_TIMER32_1);
}

void Setup_IR_PWM_duty_cycle(uint32_t duty_cycle)
{
	// 0~100
	if(duty_cycle>100)
	{
		duty_cycle = 100;
	}
	PWM_duty_cycle = 100 - duty_cycle;
}

///******************************************************************************
//**                            End Of File
//******************************************************************************/
