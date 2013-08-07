/*
 * @brief Make your board becomes a USB Virtual Com
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * Copyright(C) Dean Camera, 2011, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "chip.h"
#include "Board.h"
#include "string.h"
#include "i2c.h"
#include "Uart.h"
#include "VirtualSerial.h"
#include "Timer.h"
#include "adc.h"
#include "ExtEEPROM.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

extern int main_blinky(void);

/*****************************************************************************
 * Private functions
 ****************************************************************************/
/** Checks for data input, reply back to the host. */
void EchoCharacter(void)
{
	/* Echo back character */
	uint8_t recv_byte[1];
	if (VirtualSerial_OneByteFromHost(recv_byte)!=0) {
		VirtualSerial_OneByteToHost(recv_byte[0]);
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
static void SetupHardware(void)
{
	Board_Init();
	VirtualSerial_Init();
	UARTInit(115200);
	Timer_Init();
	I2CInit();
	ADCInit();
#ifdef _MY_UNIT_TEST_
	main_blinky();
#endif // #ifdef _MY_UNIT_TEST_

}

const char MyUARTTestMessageL1[] = "Welcome to the World.\r\n";
const char MyUARTTestMessageL2[] = "Build date: " __DATE__ "\r\n";
const char MyUARTTestMessageL3[] = "Build time: " __TIME__ "\r\n";

static void TestUARTBasicAPI(void)
{
	WriteMultiByteToUARTRingBuffer(MyUARTTestMessageL1,sizeof(MyUARTTestMessageL1)-1);
//	WriteMultiByteToUARTRingBuffer(MyUARTTestMessageL1,sizeof(MyUARTTestMessageL2)-1);
//	WriteMultiByteToUARTRingBuffer(MyUARTTestMessageL1,sizeof(MyUARTTestMessageL3)-1);
}

static void TestReadWriteExternalEEPROM(void)
{
	uint8_t	I2CRx[sizeof(MyUARTTestMessageL1)];

	WriteEEPROM_OneByte(0x102,'0');
	WriteEEPROM_MultiByte(0,MyUARTTestMessageL1,sizeof(MyUARTTestMessageL1)-1);
	WriteEEPROM_OneByte(1,'Z');
	ReadEEPROM(0, I2CRx, sizeof(MyUARTTestMessageL1)-1);
}

extern uint8_t show_message_off, show_message_on;
void TestIrRx(void);

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();
	TestUARTBasicAPI();
	TestReadWriteExternalEEPROM();

	while (1);

	for (;; ) {
//		EchoCharacter();	// Read and write back to Virtual Serial Port
		VirtualSerial_USB_USBTask();
//		if(show_message_off==1)
//		{
//			UARTputstr("123\r\n");
//			show_message_off=0;
//		}
//		if(show_message_on==1)
//		{
//			UARTputstr("987\r\n");
//			show_message_on=0;
//		}

		TestIrRx();

		VirtualSerial_FinishDataTyHost();
	}
}
