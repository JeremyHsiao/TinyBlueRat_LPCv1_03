/****************************************************************************
 *   $Id:: eeprom.c 6193 2011-01-17 21:18:11Z nxp28548                      $
 *   Project: NXP LPC11xx EEPROM example
 *
 *   Description:
 *     This file contains EEPROM code example which include EEPROM 
 *     initialization, EEPROM interrupt handler, and APIs for EEPROM access.
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

* Permission to use, copy, modify, and distribute this software and its 
* documentation is hereby granted, under NXP Semiconductors� 
* relevant copyright in the software, without fee, provided that it 
* is used in conjunction with NXP Semiconductors microcontrollers.  This 
* copyright, permission, and disclaimer notice must appear in all copies of 
* this code.

****************************************************************************/
#include "chip.h"
#include "board.h"
#include "InternalEEpromAPI.h"

#define IAP_LOCATION 0x1FFF1FF1
typedef void (*IAP) (	unsigned int command[],
						unsigned int result[] );
static const IAP iap_entry = (IAP) IAP_LOCATION;
//1) EEprom Write
//
//Command code: 61
//Param0: eeprom address (byte, half-word or word aligned)
//Param1: RAM address (byte, half-word or word aligned)
//Param2: Number of bytes to be written ( Byte, Half-words write are ok)
//Param3: System Clock Frequency (CCLK) in kHz
//
//Return Code CMD_SUCCESS | SRC_ADDR_NOT_MAPPED | DST_ADDR_NOT_MAPPED 
void writeInternalEEPROM( uint32_t eeAddress, uint8_t* buffAddress, uint32_t byteCount )
{	
	unsigned long command[5], result[4];

	command[0] = 61;                  
	command[1] = (uint32_t) eeAddress;
	command[2] = (uint32_t) buffAddress;
	command[3] = byteCount;            
	command[4] = SystemCoreClock/1000;
	
	/* Invoke IAP call...*/
	iap_entry(command, result);
	if (0 != result[0])
	{
		//Trap error
		while(1);
	}
	return;
}

//2) EEprom Read
//Command code: 62
//Param0: eeprom address (byte, half-word or word aligned)
//Param1: RAM address (byte, half-word or word aligned)
//Param2: Number of bytes to be read ( Byte, Half-words read are ok)
//Param3: System Clock Frequency (CCLK) in kHz
//
//Return Code CMD_SUCCESS | SRC_ADDR_NOT_MAPPED | DST_ADDR_NOT_MAPPED
void readInternalEEPROM( uint32_t eeAddress, uint8_t* buffAddress, uint32_t byteCount )
{
	unsigned long command[5], result[4];
		
	command[0] = 62;                  
	command[1] = (uint32_t) eeAddress;
	command[2] = (uint32_t) buffAddress;
	command[3] = byteCount;            
	command[4] = SystemCoreClock/1000;
	
	/* Invoke IAP call...*/
  	iap_entry( command, result);
	if (0 != result[0])
	{
		//Trap error
		while(1);
	}
	return;
}

// Check if data is different before write
void StoreIntEEPROM(uint32_t wAddr, uint8_t bData)
{
	uint8_t		temp_buffer[1], temp_data[1];

	temp_data[0] = bData;
	readInternalEEPROM( wAddr, temp_buffer, 1 );
	if (temp_buffer[0] != temp_data[0])
    {
		writeInternalEEPROM( wAddr, temp_data, 1 );
		readInternalEEPROM( wAddr, temp_buffer, 1 );
		if (temp_buffer[0] != temp_data[0])
		{
			return;
			// trip error here.
		}
    }
}

/******************************************************************************
**                            End Of File
******************************************************************************/
