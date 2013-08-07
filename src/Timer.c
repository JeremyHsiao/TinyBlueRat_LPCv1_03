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
#include "Io.h"
#include "VirtualSerial.h"

#ifdef _MY_UNIT_TEST_
extern void IR_RX_TIMER32_0_CAP0_IRQHandler(void) {}
extern void IR_TX_TIMER32_0_MATCH0_IRQHandler(void) {}
#else
extern void IR_RX_TIMER32_0_CAP0_IRQHandler(void);
extern void IR_TX_TIMER32_0_MATCH0_IRQHandler(void);
#endif // _MY_UNIT_TEST_

volatile uint32_t		LastCaptureTime_IR;
volatile uint32_t		LastCaptureTime_CEC;
volatile uint32_t		LastCaptureTime_HSync;
volatile uint32_t		PWM_period =  (uint32_t) (PCLK_FREQUENCY/(38000));		// For 38KHz PWM pulse
volatile uint32_t		PWM_duty_cycle;
volatile uint8_t 		SW_Timer_Timeout;
volatile uint32_t 		SystemTimer;

inline void SW_Delay_Timeout_IRQHandler(void)
{
	SW_Timer_Timeout = 1;
}

inline void SW_System_Timer_IRQHandler(void)
{
	SystemTimer++;
	Chip_TIMER_AddMatch(LPC_TIMER32_0, MATCH_2, ( 1 * TIMER0_1mS_CNT));
}

inline void BLINKY_LED_MATCH_IRQHandler(void)
{
	const char *Str_Off = "01234\r\n";
	const char *Str_On  = "98765\r\n";

	Chip_TIMER_AddMatch(LPC_TIMER32_0,MATCH_3,(500 * TIMER0_1mS_CNT));
	if(Board_LED_Test(0)!=false)
	{
		Board_LED_Set(0, false);
		//show_message_off=1;
		//UARTputstr("123\r\n");
//		VirtualSerial_MultiByteToHost(Str_Off,strlen(Str_Off));
	}
	else	// If LED is false => set to true
	{
		Board_LED_Set(0, true);
		//show_message_on=1;
		//UARTputstr("987\r\n");
//		VirtualSerial_MultiByteToHost(Str_On,strlen(Str_On));
	}
}

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
		IR_RX_TIMER32_0_CAP0_IRQHandler();
		Chip_TIMER_ClearCapture(LPC_TIMER32_0, CAPTURE_0);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_0, MATCH_0))
	{
		IR_TX_TIMER32_0_MATCH0_IRQHandler();
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, MATCH_0);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_0, MATCH_1))
	{
		SW_Delay_Timeout_IRQHandler();						// For Delayus()
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, MATCH_1);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_0, MATCH_2))
	{
		SW_System_Timer_IRQHandler();						// For always running SW system timer - 1ms per tick
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, MATCH_2);
	}

	if (Chip_TIMER_MatchPending(LPC_TIMER32_0, MATCH_3))
	{
		BLINKY_LED_MATCH_IRQHandler();						// For blinky LED
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

/******************************************************************************
** Function name:		Timer_Init
**
** Descriptions:		Initialize timer, set timer interval, reset timer,
**				install timer interrupt handler
**
** parameters:
** Returned value:	None
**
******************************************************************************/
void Timer_Init(void)
{
	//
	// Init Timer32_0
	//
	Chip_TIMER_Init(LPC_TIMER32_0);
	Chip_TIMER_PrescaleSet(LPC_TIMER32_0, (TIMER0_PRESCALER - 1)); // Prescaler set to 47 (means prescaler is 48), making a 1 MHz timer

	// Selects function CT32B0_CAP0. (P1_28)
	Chip_IOCON_PinMuxSet(LPC_IOCON, IR_RX_GPIO_PORT_NUM, IR_RX_GPIO_BIT_NUM, (PIO1_28_FUNC_CT32B0_CAP0 | PIO1_28_DEFAULT));
	// Capture 0 is for IR Rx High/Low detection
	// Capture on CT32Bn_CAP0 falling edge: a sequence of 1 then 0 on CT32Bn_CAP0 will cause CR0 to be loaded with the contents of TC.
	// Interrupt on CT32Bn_CAP0 event: a CR0 load due to a CT32Bn_CAP0 event will generate an interrupt.
	// Capture on CT32Bn_CAP0 rising edge: a sequence of 0 then 1 on CT32Bn_CAP0 will cause CR0 to be loaded with the contents of TC.
	// P1_28 falling edge, CR0 loaded with TC, and interrupt generated
	Chip_TIMER_CaptureRisingEdgeEnable(LPC_TIMER32_0,CAPTURE_0);
	Chip_TIMER_CaptureFallingEdgeEnable(LPC_TIMER32_0,CAPTURE_0);
	Chip_TIMER_CaptureEnableInt(LPC_TIMER32_0,CAPTURE_0);
	LastCaptureTime_IR = Chip_TIMER_ReadCount(LPC_TIMER32_0);

	// MR0 is IR Tx High/Low control, and set when starting IR Tx
	Chip_TIMER_MatchDisableInt(LPC_TIMER32_0,MATCH_0);

	// MR1 is SW Delay and set when it is used
	Chip_TIMER_MatchDisableInt(LPC_TIMER32_0,MATCH_1);

	// MR2 Match for SystemTimer (1ms-based)
	Chip_TIMER_SetMatch(LPC_TIMER32_0,MATCH_2,(Chip_TIMER_ReadCount(LPC_TIMER32_0)+(1 * TIMER0_1mS_CNT)));
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_0,MATCH_2);
	// Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC.

	// MR3 Match for blinking LED every 0.5 sec
	Chip_TIMER_SetMatch(LPC_TIMER32_0,MATCH_3,(Chip_TIMER_ReadCount(LPC_TIMER32_0)+(500 * TIMER0_1mS_CNT)));
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_0,MATCH_3);
	// Interrupt on MR3: an interrupt is generated when MR0 matches the value in the TC.
	Chip_TIMER_Enable(LPC_TIMER32_0);

	/* Enable the TIMER32_0 Interrupt */
	NVIC_EnableIRQ(TIMER_32_0_IRQn);

	//
	// End of Init Timer32_0
	//

	//
	// Init Timer32_1
	//
	Chip_TIMER_Init(LPC_TIMER32_1);
	/* Setup the external match register */
	// Match0 from high-to-low for PWM output pin
	Chip_TIMER_ExtMatchControlSet(LPC_TIMER32_1, 1, TIMER_EXTMATCH_CLEAR, MATCH_0);
	Chip_TIMER_SetMatch(LPC_TIMER32_1,MATCH_0,PWM_period/2);	// 50% duty cycle as default
	Chip_IOCON_PinMuxSet(LPC_IOCON, IR_TX_GPIO_PORT_NUM, IR_TX_GPIO_BIT_NUM, (PIO1_28_FUNC_CT32B0_CAP0 | PIO1_28_DEFAULT));

	// Match3 is for PWM resetting counter value
	Chip_TIMER_ExtMatchControlSet(LPC_TIMER32_1, 1, TIMER_EXTMATCH_CLEAR, MATCH_3);
	Chip_TIMER_SetMatch(LPC_TIMER32_1,MATCH_3,PWM_period);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER32_1,MATCH_3);

	/* Enable the selected PWMs and enable Match3 */
	IP_TIMER_SetPWMMatchMode(LPC_TIMER32_1, MATCH_PWM_MODE_ENABLE, MATCH_0);
	IP_TIMER_SetPWMMatchMode(LPC_TIMER32_1, MATCH_PWM_MODE_ENABLE, MATCH_3);

	Chip_TIMER_Enable(LPC_TIMER32_1);
	/* Enable the TIMER32_1 Interrupt */
	NVIC_EnableIRQ(TIMER_32_1_IRQn);

	//
	// End of Init Timer32_1
	//

	//
	// Init Timer16_0
	//
	Chip_TIMER_Init(LPC_TIMER16_0);
	Chip_TIMER_PrescaleSet(LPC_TIMER16_0, (TIMER16B0_PRESCALER - 1));
	LastCaptureTime_CEC = Chip_TIMER_ReadCount(LPC_TIMER16_0) & 0xffff;
	// Selects function CT16_CAP0. (P1_16)
	Chip_IOCON_PinMuxSet(LPC_IOCON, IR_RX_GPIO_PORT_NUM, IR_RX_GPIO_BIT_NUM, (PIO1_16_FUNC_CT32B0_CAP0 | PIO1_16_DEFAULT));
	Chip_TIMER_CaptureRisingEdgeEnable(LPC_TIMER16_0,0);
	Chip_TIMER_CaptureFallingEdgeEnable(LPC_TIMER16_0,0);
	Chip_TIMER_CaptureEnableInt(LPC_TIMER16_0,0);
	// Capture on CT16_CAP0 falling edge: a sequence of 1 then 0 on CT16_CAP0 will cause CR0 to be loaded with the contents of TC.
	// Capture on CT16_CAP0 rising edge:  a sequence of 0 then 1 on CT16_CAP0 will cause CR0 to be loaded with the contents of TC.
	// Interrupt on CT16_CAP0 event: a CR0 load due to a CT16_CAP0 event will generate an interrupt.
	Chip_TIMER_Enable(LPC_TIMER16_0);

	/* Enable the TIMER16_0 Interrupt */
	NVIC_EnableIRQ(TIMER_16_0_IRQn);


	//
	// End of Init Timer16_0
	//

	//
	// Init Timer16_1
	//
	Chip_TIMER_Init(LPC_TIMER16_1);
	Chip_TIMER_PrescaleSet(LPC_TIMER16_1, (TIMER16B1_PRESCALER - 1));
	LastCaptureTime_HSync = ( Chip_TIMER_ReadCount(LPC_TIMER16_1) ) & 0xffff;
	// Selects function CT16B1_CAP0. (P0_20)
	Chip_IOCON_PinMuxSet(LPC_IOCON, IR_RX_GPIO_PORT_NUM, IR_RX_GPIO_BIT_NUM, (PIO0_20_FUNC_CT32B0_CAP0 | PIO0_20_DEFAULT));
	Chip_TIMER_CaptureRisingEdgeEnable(LPC_TIMER16_1,0);
	Chip_TIMER_CaptureFallingEdgeEnable(LPC_TIMER16_1,0);
	Chip_TIMER_CaptureEnableInt(LPC_TIMER16_1,0);
	// Capture on CT16_CAP1 falling edge: a sequence of 1 then 0 on CT16_CAP1 will cause CR0 to be loaded with the contents of TC.
	// Capture on CT16_CAP1 rising edge:  a sequence of 0 then 1 on CT16_CAP1 will cause CR0 to be loaded with the contents of TC.
	// Interrupt on CT16_CAP1 event: a CR0 load due to a CT16_CAP1 event will generate an interrupt.
	Chip_TIMER_Enable(LPC_TIMER16_1);

	/* Enable the TIMER16_1 Interrupt */
	NVIC_EnableIRQ(TIMER_16_1_IRQn);

	//
	// End of Init Timer16_1
	//
}

void Delayus(uint32_t delay_us_value)
{
	uint32_t wCount, wTc;

    wTc = Chip_TIMER_ReadCount(LPC_TIMER32_0);
    wCount = wTc + (delay_us_value * TIMER0_1uS_CNT) + 1;    // Take 1 extra count value as delay calibration value.

    Chip_TIMER_SetMatch(LPC_TIMER32_0, MATCH_1, wCount);	// Timer32_0 match 1
    // 31:0 MATCH Timer counter match value.
    Chip_TIMER_MatchEnableInt(LPC_TIMER32_0, 1);			/* Interrupt on MR1 */
    // Interrupt on MR1: an interrupt is generated when MR1 matches the value in the TC.

    SW_Timer_Timeout = 0;
    while (SW_Timer_Timeout==0) { }
    Chip_TIMER_MatchDisableInt(LPC_TIMER32_0, MATCH_1);	/* Disable Interrupt on MR1 */
}

/******************************************************************************
/**                            End Of File
/******************************************************************************/
