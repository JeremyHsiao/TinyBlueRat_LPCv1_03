
/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
*/
#define RELEASE_MODE DEBUG_ALL_LOG

#include "board.h"
#include "gpio.h"
#include "Timer.h"
#include "Uart.h"
#include "usb_common.h"

#include "Common.h"
#include "app_timer.h"

extern void SystemInit(void);

uint32_t itoa_10_LF_CR(uint32_t value, char* result) {
	// check that the base if valid

	char* ptr = result, *ptr1 = result, tmp_char;
	uint32_t tmp_value, str_len;

	str_len = 0;
	do {
		tmp_value = value % 10;
		value /= 10;
		*ptr++ = "0123456789" [tmp_value];
		str_len++;
	} while ( value );
	*ptr++= '\r';
	*ptr++= '\n';
	str_len++;
	str_len++;

	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return str_len;
}

int app_main (void)
{
    SystemInit();
    Board_Init();
    MyUSB_Init();
	Timer_Init();

	GPIOInit();
	Set_LED(1);

	while (1)                                /* Loop forever */
	{
		USB_task_in_main_loop();

		EchoCharacter();

		// Check if pulse available
		if (bIrTimeIndexOut != bIrTimeIndexIn)
		{
		    uint32_t	wTimeStamp;
			uint8_t 	pause_dec_value[16], bLevel;
			uint8_t 	*ptr_reverse = pause_dec_value, *ptr = pause_dec_value, bytes_to_write;

			wTimeStamp = sRC_TIMETABLE[bIrTimeIndexOut].wTimeStamp;
			bLevel = sRC_TIMETABLE[bIrTimeIndexOut].bLevel;
			bIrTimeIndexOut = INC_INDEX8(bIrTimeIndexOut, IR_TBL_MAX);

			pause_dec_value[0]=(bLevel!=0)?'1':'0';
			pause_dec_value[1]=':';
			bytes_to_write = 2;

			ptr_reverse = ptr = pause_dec_value + 2;
			do
			{
				*ptr_reverse++ = (wTimeStamp % 10) + '0';
				wTimeStamp /= 10;
				bytes_to_write++;
			}
			while (wTimeStamp > 0);

			ptr_reverse--;
			while(ptr < ptr_reverse)
			{
				uint8_t	tmp_char;
				tmp_char = *ptr_reverse;
				*ptr_reverse--= *ptr;
				*ptr++ = tmp_char;
			}

			pause_dec_value[bytes_to_write++] = '\r';
			pause_dec_value[bytes_to_write++] = '\n';
			pause_dec_value[bytes_to_write] = 0;

			USB_task_in_main_loop();
			VirtualSerial_MultiByteToHost(pause_dec_value,bytes_to_write);
		}

		USB_task_in_main_loop();

	}
}
