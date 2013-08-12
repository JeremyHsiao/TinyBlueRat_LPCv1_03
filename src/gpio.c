/****************************************************************************
 *   $Id:: gpio.c 4068 2010-07-30 02:25:13Z usb00423                        $
 *   Project: NXP LPC11xx GPIO example
 *
 *   Description:
 *     This file contains GPIO code example which include GPIO 
 *     initialization, GPIO interrupt handler, and related APIs for 
 *     GPIO access.
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
#include "gpio.h"
#include "Io.h"
#include "LPC11U37_401.h"

extern void Board_LED_Init(void);
/*****************************************************************************
** Function name:		GPIOInit
**
** Descriptions:		Initialize GPIO, install the
**						GPIO interrupt handler
**
** parameters:			None
** Returned value:		true or false, return false if the VIC table
**						is full and GPIO interrupt handler can be
**						installed.
** 
*****************************************************************************/
void GPIOInit( void )
{
	/* Initialize GPIO */
	Chip_GPIO_Init(LPC_GPIO_PORT);

	/* Initialize LEDs */
	Board_LED_Init();

}

void SetGPIOPinInterrupt( uint32_t PinIntNo, uint32_t portNum, uint32_t bitPosi, uint32_t trigger, uint32_t event )
{
	LPC_GPIO_T	*GPIO_NA;		// Don't care variable here
	uint8_t		Bit_NA;			// Don't care variable here

	Chip_SYSCTL_SetPinInterrupt(PinIntNo, portNum, bitPosi);
	if ( trigger != 0 )
	{
		// Single edge
		if ( event & 0x01 )
		{
			Chip_GPIO_IntCmd(GPIO_NA, PinIntNo, Bit_NA, GPIOPININT_RISING_EDGE);
		}
		if ( event & 0x02 )
		{
			Chip_GPIO_IntCmd(GPIO_NA, PinIntNo, Bit_NA, GPIOPININT_FALLING_EDGE);
		}
	}
	else	// level trigger
	{
		// Level Trigger
		if ( event != 0 )
		{
			// Level, Low
			Chip_GPIO_IntCmd(GPIO_NA, PinIntNo, Bit_NA, GPIOPININT_ACTIVE_HIGH_LEVEL);
		}
		else
		{
			// Level, High
			Chip_GPIO_IntCmd(GPIO_NA, PinIntNo, Bit_NA, GPIOPININT_ACTIVE_LOW_LEVEL);
		}
	}
}

/*****************************************************************************
** Function name:		GPIOSetInterrupt
**
** Descriptions:		Set interrupt sense, event, etc.
**						edge or level, 0 is edge, 1 is level
**						single or double edge, 0 is single, 1 is double 
**						active high or low, etc.
**						falling edge 0; rising edge 1;
**
** parameters:			port num, bit position, sense, single/doube, polarity
** Returned value:		None
** 
*****************************************************************************/
//void GPIOSetInterrupt( uint32_t portNum, uint32_t bitPosi, uint32_t sense,
//			uint32_t single, uint32_t event )
//{
//	IP_GPIOPININT_MODE_T mode_value;
//
//	 if ( sense == 0 )
//	 {
//		 // Edge Trigger
//		 if ( single == 0 )
//		 {
//			 // Single edge
//			 if ( event == 0 )
//			 {
//				 // Edge, Single, Falling
//				 mode_value = GPIOPININT_FALLING_EDGE;
//			 }
//			 else
//			 {
//				 // Edge, Single, Rising
//				 mode_value = GPIOPININT_RISING_EDGE;
//			 }
//		 }
//		 else
//		 {
//			 // Both edge
//			 mode_value = GPIOPININT_BOTH_EDGES;
//		 }
//	 }
//	 else
//	 {
//		 // Level Trigger
//		 if ( event == 0 )
//		 {
//			 // Level, Low
//			 mode_value = GPIOPININT_ACTIVE_LOW_LEVEL;
//		 }
//		 else
//		 {
//			 // Level, High
//			 mode_value =  GPIOPININT_ACTIVE_HIGH_LEVEL;
//		 }
//	 }
//	 Chip_GPIO_IntCmd(LPC_GPIO_PORT, portNum, bitPosi, mode_value );
//
//  switch ( portNum )
//  {
//	case PORT0:
//	  if ( sense == 0 )
//	  {
//		LPC_GPIO0->IS &= ~(0x1<<bitPosi);
//		/* single or double only applies when sense is 0(edge trigger). */
//		if ( single == 0 )
//		  LPC_GPIO0->IBE &= ~(0x1<<bitPosi);
//		else
//		  LPC_GPIO0->IBE |= (0x1<<bitPosi);
//	  }
//	  else
//	  	LPC_GPIO0->IS |= (0x1<<bitPosi);
//	  if ( event == 0 )
//		LPC_GPIO0->IEV &= ~(0x1<<bitPosi);
//	  else
//		LPC_GPIO0->IEV |= (0x1<<bitPosi);
//	break;
// 	case PORT1:
//	  if ( sense == 0 )
//	  {
//		LPC_GPIO1->IS &= ~(0x1<<bitPosi);
//		/* single or double only applies when sense is 0(edge trigger). */
//		if ( single == 0 )
//		  LPC_GPIO1->IBE &= ~(0x1<<bitPosi);
//		else
//		  LPC_GPIO1->IBE |= (0x1<<bitPosi);
//	  }
//	  else
//	  	LPC_GPIO1->IS |= (0x1<<bitPosi);
//	  if ( event == 0 )
//		LPC_GPIO1->IEV &= ~(0x1<<bitPosi);
//	  else
//		LPC_GPIO1->IEV |= (0x1<<bitPosi);
//	break;
//	case PORT2:
//	  if ( sense == 0 )
//	  {
//		LPC_GPIO2->IS &= ~(0x1<<bitPosi);
//		/* single or double only applies when sense is 0(edge trigger). */
//		if ( single == 0 )
//		  LPC_GPIO2->IBE &= ~(0x1<<bitPosi);
//		else
//		  LPC_GPIO2->IBE |= (0x1<<bitPosi);
//	  }
//	  else
//	  	LPC_GPIO2->IS |= (0x1<<bitPosi);
//	  if ( event == 0 )
//		LPC_GPIO2->IEV &= ~(0x1<<bitPosi);
//	  else
//		LPC_GPIO2->IEV |= (0x1<<bitPosi);
//	break;
//	case PORT3:
//	  if ( sense == 0 )
//	  {
//		LPC_GPIO3->IS &= ~(0x1<<bitPosi);
//		/* single or double only applies when sense is 0(edge trigger). */
//		if ( single == 0 )
//		  LPC_GPIO3->IBE &= ~(0x1<<bitPosi);
//		else
//		  LPC_GPIO3->IBE |= (0x1<<bitPosi);
//	  }
//	  else
//	  	LPC_GPIO3->IS |= (0x1<<bitPosi);
//	  if ( event == 0 )
//		LPC_GPIO3->IEV &= ~(0x1<<bitPosi);
//	  else
//		LPC_GPIO3->IEV |= (0x1<<bitPosi);
//	break;
//	default:
//	  break;
//  }
//  return;
//}
//
///*****************************************************************************
//** Function name:		GPIOIntEnable
//**
//** Descriptions:		Enable Interrupt Mask for a port pin.
//**
//** parameters:			port num, bit position
//** Returned value:		None
//**
//*****************************************************************************/
//void GPIOIntEnable( uint32_t portNum, uint32_t bitPosi )
//{
//  switch ( portNum )
//  {
//	case PORT0:
//	  LPC_GPIO0->IE |= (0x1<<bitPosi);
//	break;
// 	case PORT1:
//	  LPC_GPIO1->IE |= (0x1<<bitPosi);
//	break;
//	case PORT2:
//	  LPC_GPIO2->IE |= (0x1<<bitPosi);
//	break;
//	case PORT3:
//	  LPC_GPIO3->IE |= (0x1<<bitPosi);
//	break;
//	default:
//	  break;
//  }
//  return;
//}
//
///*****************************************************************************
//** Function name:		GPIOIntDisable
//**
//** Descriptions:		Disable Interrupt Mask for a port pin.
//**
//** parameters:			port num, bit position
//** Returned value:		None
//**
//*****************************************************************************/
//void GPIOIntDisable( uint32_t portNum, uint32_t bitPosi )
//{
//  switch ( portNum )
//  {
//	case PORT0:
//	  LPC_GPIO0->IE &= ~(0x1<<bitPosi);
//	break;
// 	case PORT1:
//	  LPC_GPIO1->IE &= ~(0x1<<bitPosi);
//	break;
//	case PORT2:
//	  LPC_GPIO2->IE &= ~(0x1<<bitPosi);
//	break;
//	case PORT3:
//	  LPC_GPIO3->IE &= ~(0x1<<bitPosi);
//	break;
//	default:
//	  break;
//  }
//  return;
//}
//
///*****************************************************************************
//** Function name:		GPIOIntStatus
//**
//** Descriptions:		Get Interrupt status for a port pin.
//**
//** parameters:			port num, bit position
//** Returned value:		None
//**
//*****************************************************************************/
//uint32_t GPIOIntStatus( uint32_t portNum, uint32_t bitPosi )
//{
//  uint32_t regVal = 0;
//
//  switch ( portNum )
//  {
//	case PORT0:
//	  if ( LPC_GPIO0->MIS & (0x1<<bitPosi) )
//		regVal = 1;
//	break;
// 	case PORT1:
//	  if ( LPC_GPIO1->MIS & (0x1<<bitPosi) )
//		regVal = 1;
//	break;
//	case PORT2:
//	  if ( LPC_GPIO2->MIS & (0x1<<bitPosi) )
//		regVal = 1;
//	break;
//	case PORT3:
//	  if ( LPC_GPIO3->MIS & (0x1<<bitPosi) )
//		regVal = 1;
//	break;
//	default:
//	  break;
//  }
//  return ( regVal );
//}

///*****************************************************************************
//** Function name:		GPIOIntClear
//**
//** Descriptions:		Clear Interrupt for a port pin.
//**
//** parameters:			port num, bit position
//** Returned value:		None
//**
//*****************************************************************************/
//void GPIOIntClear( uint32_t portNum, uint32_t bitPosi )
//{
//  switch ( portNum )
//  {
//	case PORT0:
//	  LPC_GPIO0->IC |= (0x1<<bitPosi);
//	break;
// 	case PORT1:
//	  LPC_GPIO1->IC |= (0x1<<bitPosi);
//	break;
//	case PORT2:
//	  LPC_GPIO2->IC |= (0x1<<bitPosi);
//	break;
//	case PORT3:
//	  LPC_GPIO3->IC |= (0x1<<bitPosi);
//	break;
//	default:
//	  break;
//  }
//  return;
//}
//
///*****************************************************************************
//** Function name:		GPIOSetValue
//**
//** Descriptions:		Set/clear a bitvalue in a specific bit position
//**						in GPIO portX(X is the port number.)
//**
//** parameters:			port num, bit position, bit value
//** Returned value:		None
//**
//*****************************************************************************/
//void GPIOSetValue( uint32_t portNum, uint32_t bitPosi, uint32_t bitVal )
//{
//  LPC_GPIO[portNum]->MASKED_ACCESS[(1<<bitPosi)] = (bitVal<<bitPosi);
//}
//
///*****************************************************************************
//** Function name:		GPIOSetDir
//**
//** Descriptions:		Set the direction in GPIO port
//**
//** parameters:			port num, bit position, direction (1 out, 0 input)
//** Returned value:		None
//**
//*****************************************************************************/
//void GPIOSetDir( uint32_t portNum, uint32_t bitPosi, uint32_t dir )
//{
//  if(dir)
//	LPC_GPIO[portNum]->DIR |= 1<<bitPosi;
//  else
//	LPC_GPIO[portNum]->DIR &= ~(1<<bitPosi);
//}

//void Init_LED(void)
//{
//	/* Set port 0_7 to output */ // LED on board
//	GPIOSetDir( 0, 7, 1 );
//	GPIOSetValue(0,7,0);
//	current_led = 0;
//}

inline void Set_LED(uint32_t LED_On_Off)
{
	if(LED_On_Off==0)
	{
		Board_LED_Set(0, false);
	}
	else
	{
		Board_LED_Set(0, true);
	}
}


inline void Toggle_LED(void)
{
	if(Board_LED_Test(0)!=false)
	{
		Board_LED_Set(0, false);
	}
	else
	{
		Board_LED_Set(0, true);
	}
}


/******************************************************************************
**                            End Of File
******************************************************************************/
