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


#include "chip.h"
#include "board.h"
#include "string.h"
#include "Timer.h"

extern void TEST_TIMER_Match_IRQHandler(void);

/******************************************************************************
** Function name:		TIMER32_0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**				executes each 10ms @ 60 MHz CPU Clock
**
** parameters:		None
** Returned value:	None
** 
******************************************************************************/
// 32bit Timer0 for counting pulse-width
void TIMER32_0_IRQHandler(void)
{
	if (Chip_TIMER_CapturePending(LPC_TIMER32_0, CAPTURE_0))
	{
		Chip_TIMER_ClearCapture(LPC_TIMER32_0, CAPTURE_0);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_0, MATCH_0))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, MATCH_0);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_0, MATCH_1))
	{
		TEST_TIMER_Match_IRQHandler();
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, MATCH_1);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_0, MATCH_2))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, MATCH_2);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_0, MATCH_3))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, MATCH_3);
	}
	return;
}

/******************************************************************************
** Function name:		TIMER32_1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**				executes each 10ms @ 60 MHz CPU Clock
**
** parameters:		None
** Returned value:	None
**
******************************************************************************/
void TIMER32_1_IRQHandler(void)
{
	if (Chip_TIMER_CapturePending(LPC_TIMER32_1, CAPTURE_0))
	{
		Chip_TIMER_ClearCapture(LPC_TIMER32_1, CAPTURE_0);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_1, MATCH_0))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER32_1, MATCH_0);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_1, MATCH_1))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER32_1, MATCH_1);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_1, MATCH_2))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER32_1, MATCH_2);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_1, MATCH_3))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER32_1, MATCH_3);
	}
	return;
}

/******************************************************************************
** Function name:		TIMER16_0_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**				executes each 10us @ 48 MHz CPU Clock
**
** parameters:		None
** Returned value:	None
**
******************************************************************************/
void TIMER16_0_IRQHandler(void)
{
	if (Chip_TIMER_CapturePending(LPC_TIMER16_0, CAPTURE_0))
	{
		Chip_TIMER_ClearCapture(LPC_TIMER16_0, CAPTURE_0);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER16_0, MATCH_0))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER16_0, MATCH_0);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER16_0, MATCH_1))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER16_0, MATCH_1);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER16_0, MATCH_2))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER16_0, MATCH_2);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER16_0, MATCH_3))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER16_0, MATCH_3);
	}
	return;
}

/******************************************************************************
** Function name:		TIMER16_1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**				executes each 10us @ 48 MHz CPU Clock
**
** parameters:		None
** Returned value:	None
**
******************************************************************************/
void TIMER16_1_IRQHandler(void)
{
	if (Chip_TIMER_CapturePending(LPC_TIMER16_1, CAPTURE_0))
	{
		Chip_TIMER_ClearCapture(LPC_TIMER16_1, CAPTURE_0);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER16_1, MATCH_0))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER16_1, MATCH_0);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER16_1, MATCH_1))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER16_1, MATCH_1);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER16_1, MATCH_2))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER16_1, MATCH_2);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER16_1, MATCH_3))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER16_1, MATCH_3);
	}
	return;
}

///******************************************************************************
//** Function name:		enable_timer
//**
//** Descriptions:		Enable timer
//**
//** parameters:		timer number: 0 or 1
//** Returned value:	None
//**
//******************************************************************************/
//void enable_timer32(uint8_t timer_num)
//{
//  if ( timer_num == 0 )
//  {
//    LPC_TMR32B0->TCR = 1;
//  }
//  else
//  {
//    LPC_TMR32B1->TCR = 1;
//  }
//  return;
//}
//
//void enable_timer16(uint8_t timer_num)
//{
//  if ( timer_num == 0 )
//  {
//    LPC_TMR16B0->TCR = 1;
//  }
//  else
//  {
//    LPC_TMR16B1->TCR = 1;
//  }
//  return;
//}
//
///******************************************************************************
//** Function name:		disable_timer
//**
//** Descriptions:		Disable timer
//**
//** parameters:		timer number: 0 or 1
//** Returned value:	None
//**
//******************************************************************************/
//void disable_timer32(uint8_t timer_num)
//{
//  if ( timer_num == 0 )
//  {
//    LPC_TMR32B0->TCR = 0;
//  }
//  else
//  {
//    LPC_TMR32B1->TCR = 0;
//  }
//  return;
//}
//
//void disable_timer16(uint8_t timer_num)
//{
//  if ( timer_num == 0 )
//  {
//    LPC_TMR16B0->TCR = 0;
//  }
//  else
//  {
//    LPC_TMR16B1->TCR = 0;
//  }
//  return;
//}
//
///******************************************************************************
//** Function name:		reset_timer
//**
//** Descriptions:		Reset timer
//**
//** parameters:		timer number: 0 or 1
//** Returned value:	None
//**
//******************************************************************************/
//void reset_timer32(uint8_t timer_num)
//{
//  uint32_t regVal;
//
//  if ( timer_num == 0 )
//  {
//    regVal = LPC_TMR32B0->TCR;
//    LPC_TMR32B0->TCR = regVal | 0x02;
//    LPC_TMR32B0->TCR = regVal;
//  }
//  else
//  {
//    regVal = LPC_TMR32B1->TCR;
//    LPC_TMR32B1->TCR = regVal  | 0x02;
//    LPC_TMR32B1->TCR = regVal;
//  }
//  return;
//}
//
//void reset_timer16(uint8_t timer_num)
//{
//  uint32_t regVal;
//
//  if ( timer_num == 0 )
//  {
//    regVal = LPC_TMR16B0->TCR;
//    regVal |= 0x02;
//    LPC_TMR16B0->TCR = regVal;
//  }
//  else
//  {
//    regVal = LPC_TMR16B1->TCR;
//    regVal |= 0x02;
//    LPC_TMR16B1->TCR = regVal;
//  }
//  return;
//}
//
///******************************************************************************
//** Function name:		init_timer
//**
//** Descriptions:		Initialize timer, set timer interval, reset timer,
//**				install timer interrupt handler
//**
//** parameters:		timer number and timer interval
//** Returned value:	None
//**
//******************************************************************************/
//void init_timer32(uint8_t timer_num, uint32_t TimerInterval)
//{
//  if ( timer_num == 0 )
//  {
//    /* Some of the I/O pins need to be clearfully planned if
//    you use below module because JTAG and TIMER CAP/MAT pins are muxed. */
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);
//    LPC_IOCON->PIO1_5 &= ~0x07;	/*  Timer0_32 I/O config */
//    LPC_IOCON->PIO1_5 |= 0x02;	/* Timer0_32 CAP0 */
//    // Selects function CT32B0_CAP0. (P1_5)
//
//#ifdef __JTAG_DISABLED
//    LPC_IOCON->R_PIO0_11 &= ~0x07;
//    LPC_IOCON->R_PIO0_11 |= 0x03;	/* Timer0_32 MAT3 */
//#endif
//
//    // MR2 Match for SystemTimer (1ms-based)
//    LPC_TMR32B0->MR2 = LPC_TMR32B0->TC + (1 * TIMER0_1mS_CNT); // 1 ms
//    // 31:0 MATCH Timer counter match value.
//    LPC_TMR32B0->MCR |= ((0x1)<<6);//;			/* Interrupt/Reset on MRx */
//    // Interrupt on MR2: an interrupt is generated when MR0 matches the value in the TC.
//
//    // MR3 Match for blinking LED every 0.5 sec
//    LPC_TMR32B0->MR3 = LPC_TMR32B0->TC + (500 * TIMER0_1mS_CNT); // next 0.5 sec
//    // 31:0 MATCH Timer counter match value.
//    LPC_TMR32B0->MCR |= ((0x1)<<9);//;			/* Interrupt/Reset on MRx */
//    // Interrupt on MR3: an interrupt is generated when MR0 matches the value in the TC.
//
//	LPC_TMR32B0->CCR = ((0x1<<1)|(0x1<<2)|(0x1));
//	// Capture on CT32Bn_CAP0 falling edge: a sequence of 1 then 0 on CT32Bn_CAP0 will cause CR0 to be loaded with the contents of TC.
//	// Interrupt on CT32Bn_CAP0 event: a CR0 load due to a CT32Bn_CAP0 event will generate an interrupt.
//	// Capture on CT32Bn_CAP0 rising edge: a sequence of 0 then 1 on CT32Bn_CAP0 will cause CR0 to be loaded with the contents of TC.
//    // P1_5 falling edge, CR0 loaded with TC, and interrupt generated
//	LPC_TMR32B0->PR = TIMER0_PRESCALER - 1; // Prescaler set to 47 (means prescaler is 48), making a 1 MHz timer
//	LastCaptureTime_IR = LPC_TMR32B0->TC;
//
//    /* Enable the TIMER0 Interrupt */
//    NVIC_EnableIRQ(TIMER_32_0_IRQn);
//  }
//  else if ( timer_num == 1 )
//  {
//#if 0
//	  /* Some of the I/O pins need to be clearfully planned if
//    you use below module because JTAG and TIMER CAP/MAT pins are muxed. */
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10);
//    LPC_IOCON->R_PIO1_0 &= ~0x07;	/*  Timer1_32 I/O config */
//    LPC_IOCON->R_PIO1_0 |= 0x03;	/* Timer1_32 CAP0 */ // NOTE: different value from P1_5!!
//    // Selects function CT32B1_CAP0. (P1_0)
//
//#ifdef __JTAG_DISABLED
//    LPC_IOCON->R_PIO1_0  &= ~0x07;	/*  Timer1_32 I/O config */
//    LPC_IOCON->R_PIO1_0  |= 0x03;	/* Timer1_32 CAP0 */
//    LPC_IOCON->R_PIO1_1  &= ~0x07;
//    LPC_IOCON->R_PIO1_1  |= 0x03;	/* Timer1_32 MAT0 */
//    LPC_IOCON->R_PIO1_2 &= ~0x07;
//    LPC_IOCON->R_PIO1_2 |= 0x03;	/* Timer1_32 MAT1 */
//    LPC_IOCON->SWDIO_PIO1_3  &= ~0x07;
//    LPC_IOCON->SWDIO_PIO1_3  |= 0x03;	/* Timer1_32 MAT2 */
//#endif
//
//	LPC_TMR32B1->CCR = ((0x1<<1)|(0x1<<2)|(0x1));
//	// Capture on CT32Bn_CAP0 falling edge: a sequence of 1 then 0 on CT32Bn_CAP0 will cause CR0 to be loaded with the contents of TC.
//	// Interrupt on CT32Bn_CAP0 event: a CR0 load due to a CT32Bn_CAP0 event will generate an interrupt.
//	// Capture on CT32Bn_CAP0 rising edge: a sequence of 0 then 1 on CT32Bn_CAP0 will cause CR0 to be loaded with the contents of TC.
//    // P1_5 falling edge, CR0 loaded with TC, and interrupt generated
//
//	LPC_TMR32B1->PR = TIMER1_PRESCALER - 1; // Prescaler set to 0 (means prescaler is 1), making a 48 MHz timer
//	LastCaptureTime_CEC = LPC_TMR32B1->TC;
//
//    /* Enable the TIMER1 Interrupt */
//    NVIC_EnableIRQ(TIMER_32_1_IRQn);
//#endif // #if 0
//  }
//  return;
//}
//
//void init_timer16(uint8_t timer_num)
//{
//	if ( timer_num == 0 )
//	{
//		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);
//		LPC_IOCON->PIO0_2 &= ~0x07;	/* Timer0_16 I/O config */
//		LPC_IOCON->PIO0_2 |= 0x02;	/* Timer0_16 CAP0 */
//		// Selects function CT16_CAP0. (P0_2)
//
//		LPC_TMR16B0->CCR = ((0x1<<1)|(0x1<<2)|(0x1));
//		// Capture on CT16_CAP0 falling edge: a sequence of 1 then 0 on CT16_CAP0 will cause CR0 to be loaded with the contents of TC.
//		// Capture on CT16_CAP0 rising edge:  a sequence of 0 then 1 on CT16_CAP0 will cause CR0 to be loaded with the contents of TC.
//		// Interrupt on CT16_CAP0 event: a CR0 load due to a CT16_CAP0 event will generate an interrupt.
//
//		LPC_TMR16B0->PR = TIMER16B0_PRESCALER - 1;
//		LastCaptureTime_CEC = (LPC_TMR16B0->TC) & 0xffff;
//
//		/* Enable the TIMER1 Interrupt */
//		NVIC_EnableIRQ(TIMER_16_0_IRQn);
//	}
//	else if ( timer_num == 1 )
//	{
//		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<8);
//		LPC_IOCON->PIO1_8 &= ~0x07;	/* Timer16_1 I/O config */
//		LPC_IOCON->PIO1_8 |= 0x01;	/* Timer16_1 CAP0 */
//		// Selects function CT16B1_CAP0. (P1_8)
//
//		LPC_TMR16B1->CCR = ((0x1<<1)|(0x1<<2)|(0x1));
//		// Capture on CT16_CAP1 falling edge: a sequence of 1 then 0 on CT16_CAP1 will cause CR0 to be loaded with the contents of TC.
//		// Capture on CT16_CAP1 rising edge:  a sequence of 0 then 1 on CT16_CAP1 will cause CR0 to be loaded with the contents of TC.
//		// Interrupt on CT16_CAP1 event: a CR0 load due to a CT16_CAP1 event will generate an interrupt.
//
//		LPC_TMR16B1->PR = TIMER16B1_PRESCALER - 1;
//		LastCaptureTime_HSync = (LPC_TMR16B1->TC) & 0xffff;
//
//		/* Enable the TIMER1 Interrupt */
//		NVIC_EnableIRQ(TIMER_16_1_IRQn);
//	}
//	return;
//}
//
///******************************************************************************
//** Function name:		init_timer32PWM
//**
//** Descriptions:		Initialize timer as PWM
//**
//** parameters:		timer number, period and match enable:
//**				match_enable[0] = PWM for MAT0
//**				match_enable[1] = PWM for MAT1
//**				match_enable[2] = PWM for MAT2
//** Returned value:	None
//**
//******************************************************************************/
//void init_timer32PWM(uint8_t timer_num, uint32_t period, uint8_t match_enable)
//{
//  uint32_t		timer32_1_period;
//
//  disable_timer32(timer_num);
//  if (timer_num == 1)
//  {
//    /* Some of the I/O pins need to be clearfully planned if
//    you use below module because JTAG and TIMER CAP/MAT pins are muxed. */
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10);
//
//    /* Setup the external match register */
//    LPC_TMR32B1->EMR = (1<<EMC3)|(1<<EMC2)|(2<<EMC1)|(1<<EMC0)|(1<<3)|(match_enable);
//
//    /* Setup the outputs */
//    /* If match0 is enabled, set the output */
//    if (match_enable & 0x01)
//    {
//      LPC_IOCON->R_PIO1_1  &= ~0x07;
//      LPC_IOCON->R_PIO1_1  |= 0x03;		/* Timer1_32 MAT0 */
//    }
//    /* If match1 is enabled, set the output */
//    if (match_enable & 0x02)
//    {
//      LPC_IOCON->R_PIO1_2 &= ~0x07;
//      LPC_IOCON->R_PIO1_2 |= 0x03;		/* Timer1_32 MAT1 */
//    }
//    /* If match2 is enabled, set the output */
//    if (match_enable & 0x04)
//    {
//      LPC_IOCON->SWDIO_PIO1_3   &= ~0x07;
//      LPC_IOCON->SWDIO_PIO1_3   |= 0x03;		/* Timer1_32 MAT2 */
//    }
//    /* If match3 is enabled, set the output */
//    if (match_enable & 0x08)
//    {
//      LPC_IOCON->PIO1_4           &= ~0x07;
//      LPC_IOCON->PIO1_4           |= 0x02;		/* Timer1_32 MAT3 */
//    }
//
//    /* Enable the selected PWMs and enable Match3 */
//    LPC_TMR32B1->PWMC = (1<<3)|(match_enable);
//
//    /* Setup the match registers */
//    /* set the period value to a global variable */
//    timer32_1_period = period;
//    LPC_TMR32B1->MR3 = timer32_1_period;
//    timer32_1_period = period / 2;
//    LPC_TMR32B1->MR0 = timer32_1_period;
//    LPC_TMR32B1->MR1 = timer32_1_period;
//    LPC_TMR32B1->MR2 = timer32_1_period;
//    LPC_TMR32B1->MCR = 1<<10;				/* Reset on MR3 */
//  }
//  else
//  {
//// PWM for Timer32_0 is not used here
//#if 0
//    /* Some of the I/O pins need to be clearfully planned if
//    you use below module because JTAG and TIMER CAP/MAT pins are muxed. */
//    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);
//
//    /* Setup the external match register */
//    LPC_TMR32B0->EMR = (1<<EMC3)|(2<<EMC2)|(1<<EMC1)|(1<<EMC0)|(1<<3)|(match_enable);
//
//    /* Setup the outputs */
//    /* If match0 is enabled, set the output */
//    if (match_enable & 0x01)
//    {
////	 	LPC_IOCON->PIO1_6           &= ~0x07;
////	  	LPC_IOCON->PIO1_6           |= 0x02;		/* Timer0_32 MAT0 */
//    }
//    /* If match1 is enabled, set the output */
//    if (match_enable & 0x02)
//    {
//      LPC_IOCON->PIO1_7           &= ~0x07;
//      LPC_IOCON->PIO1_7           |= 0x02;		/* Timer0_32 MAT1 */
//    }
//    /* If match2 is enabled, set the output */
//    if (match_enable & 0x04)
//    {
//      LPC_IOCON->PIO0_1           &= ~0x07;
//      LPC_IOCON->PIO0_1           |= 0x02;		/* Timer0_32 MAT2 */
//    }
//    /* If match3 is enabled, set the output */
//    if (match_enable & 0x08)
//    {
//      LPC_IOCON->R_PIO0_11 &= ~0x07;
//      LPC_IOCON->R_PIO0_11 |= 0x03;		/* Timer0_32 MAT3 */
////        LPC_IOCON->JTAG_TDI_PIO0_11 &= ~0x07;
////        LPC_IOCON->JTAG_TDI_PIO0_11 |= 0x03;		/* Timer0_32 MAT3 */
//
//    }
//
//    /* Enable the selected PWMs and enable Match3 */
//    LPC_TMR32B0->PWMC = (1<<3)|(match_enable);
//
//    /* Setup the match registers */
//    /* set the period value to a global variable */
//    timer32_0_period = period;
//    LPC_TMR32B0->MR3 = timer32_0_period;
//    LPC_TMR32B0->MR0	= timer32_0_period;	///2;
//    LPC_TMR32B0->MR1	= timer32_0_period/2;
//    LPC_TMR32B0->MR2	= timer32_0_period/2;
//
//    LPC_TMR32B0->MCR = 1<<10;				/* Reset on MR3 */
//#endif // 0
//  }
//}
//
///******************************************************************************
//** Function name:		pwm32_setMatch
//**
//** Descriptions:		Set the pwm32 match values
//**
//** parameters:		timer number, match numner and the value
//**
//** Returned value:	None
//**
//******************************************************************************/
//void setMatch_timer32PWM (uint8_t timer_num, uint8_t match_nr, uint32_t value)
//{
//  if (timer_num)
//  {
//    switch (match_nr)
//    {
//      case 0:
//        LPC_TMR32B1->MR0 = value;
//      break;
//      case 1:
//        LPC_TMR32B1->MR1 = value;
//      break;
//      case 2:
//        LPC_TMR32B1->MR2 = value;
//      break;
//      case 3:
//        LPC_TMR32B1->MR3 = value;
//      break;
//      default:
//      break;
//    }
//  }
//  else
//  {
//    switch (match_nr)
//    {
//      case 0:
//        LPC_TMR32B0->MR0 = value;
//      break;
//      case 1:
//        LPC_TMR32B0->MR1 = value;
//      break;
//      case 2:
//        LPC_TMR32B0->MR2 = value;
//      break;
//      case 3:
//        LPC_TMR32B0->MR3 = value;
//      break;
//      default:
//      break;
//    }
//  }
//}
//
//uint32_t Check_PWM_Pulse_Width(uint32_t temp_width)
//{
//	// Error prevention
//	// Compare based on the same ground
//	if((temp_width*(TIMER0_PRESCALER)*(TIMER0_1uS_CNT))<PWM_period)
//	{
//		return FALSE;
//	}
//	else
//	{
//		return TRUE;
//	}
//}
//
//void IR_Transmit_Buffer_Init(void)
//{
//    LPC_TMR32B0->MCR &= ~((0x1));   //;			/* Disable Interrupt on MR0 */
//
//	bIrTimeIndexIn_Output  = 0;
//	bIrTimeIndexOut_Output = 0;
//	IR_Transmitter_Running = 0;
//}
//
//void IR_Transmit_Buffer_StartSend(void)
//{
//	uint32_t temp_level;
//	uint32_t temp_width;
//	uint32_t temp_tc, temp_mr0;
//
//	if (IR_Transmitter_Running!=0)
//	{
//	  return;			// already running, no need to start timer match and interrupt
//	}
//
//	// Get next pulse width and level
//	if(IR_Transmit_Buffer_Pop(&temp_level, &temp_width)!=FALSE)
//	{
////		// Error prevention
////		if (Check_PWM_Pulse_Width(temp_width)==FALSE)
////		{
////			printfs("timer32.c L834\n");
////		}
//
//		// Please set up first pulse here
//		Setup_IR_PWM_Pulse_by_IR_Level(temp_level);
//		// Load Timer0_MATCH first match value (based on TC) and enable interrupt here
//		temp_tc = LPC_TMR32B0->TC;
//		temp_mr0 = (temp_width*TIMER0_1uS_CNT) + temp_tc;
//		LPC_TMR32B0->MR0 = temp_mr0;   // MR0 Match for IR Transmitter
//		LPC_TMR32B0->MCR |= ((0x1));//;			/* Interrupt/Reset on MRx */
//		// Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC.
//		IR_Transmitter_Running = 1;
//	}
//	else
//	{
//		// printf("Nothing to send\r\n");
//		// Nothing to send
//	}
//}
//
//void IR_Transmit_Buffer_Push(uint32_t temp_level, uint32_t temp_width )
//{
//	// Store into IR transmitter table
//	sRC_TIMETABLE_Output[bIrTimeIndexIn_Output].bLevel     = temp_level;
//	sRC_TIMETABLE_Output[bIrTimeIndexIn_Output].wTimeStamp = (temp_width&0xffff);
//	bIrTimeIndexIn_Output++;
//	if(bIrTimeIndexIn_Output >= IR_TBL_MAX)
//	{
//		bIrTimeIndexIn_Output = 0;
//	}
//}
//
//uint8_t IR_Transmit_Buffer_Pop(uint32_t *temp_level, uint32_t *temp_width )
//{
//	if(bIrTimeIndexOut_Output != bIrTimeIndexIn_Output)
//	{
//		*temp_level = (uint32_t) sRC_TIMETABLE_Output[bIrTimeIndexOut_Output].bLevel;
//		*temp_width = (uint32_t) sRC_TIMETABLE_Output[bIrTimeIndexOut_Output].wTimeStamp;
//		bIrTimeIndexOut_Output++;
//		if(bIrTimeIndexOut_Output >= IR_TBL_MAX)
//		{
//			bIrTimeIndexOut_Output = 0;
//		}
//		return TRUE;
//	}
//	else
//	{
//		return FALSE;
//	}
//}
//
//void Setup_IR_PWM_Pulse_by_IR_Level(uint32_t bLevel)
//{
//	uint32_t	temp;
//	if(bLevel != 0)
//	{
//		temp = (PWM_period*PWM_duty_cycle)/100;  /* Duty cycle X% output on PIO1_1 */
//	}
//	else
//	{
//		temp = ~(0x1);  /* low output on PIO1_1 */
////		temp = 0;  				/* low output on PIO1_1 */
//	}
//	reset_timer32(1); 		// For a better 1st PWM pulse
//	setMatch_timer32PWM (1, 0, temp);
//}
//
//void Setup_IR_PWM_duty_cycle(uint32_t duty_cycle)
//{
//	// 0~100
//	if(duty_cycle>100)
//	{
//		duty_cycle = 100;
//	}
//	PWM_duty_cycle = 100 - duty_cycle;
//}
//
////
////
////
//
//void Delayus(uint32_t uint32_Value)
//{
//	uint32_t wCount, wTc;
//
//    wTc = (LPC_TMR32B0->TC);
//    wCount = wTc + (uint32_Value * TIMER0_1uS_CNT);
//
//    LPC_TMR32B0->MR1 = wCount;
//    // 31:0 MATCH Timer counter match value.
//    LPC_TMR32B0->MCR |= ((0x1)<<3); //;			/* Interrupt on MR1 */
//    // Interrupt on MR1: an interrupt is generated when MR1 matches the value in the TC.
//
//    SW_Timer_Timeout = 0;
//    while (SW_Timer_Timeout==0) { }
//    LPC_TMR32B0->MCR &= ~((0x1)<<3); //;		/* Disable Interrupt on MR1 */
//}
//
//void ClearWatchdogTimer(void)
//{
//}
//
//
///******************************************************************************
//**                            End Of File
//******************************************************************************/
