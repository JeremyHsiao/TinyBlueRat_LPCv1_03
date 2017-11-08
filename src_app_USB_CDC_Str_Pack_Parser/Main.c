
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
#include "parser.h"

extern void SystemInit(void);

void IrDA_Int_Handler(void) {} // empty function in this application

uint32_t itoa_10(uint32_t value, char* result)
{
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

	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return str_len;
}

bool Output_Tx_Buffer_UART(void)
 {
	uint32_t temp_level, temp_width;

	if (IR_Transmit_Buffer_Pop(&temp_level, &temp_width) != FALSE) {
		char str[20];
		int  len = 2;
		str[0] = '0' + temp_level;
		str[1] = ':';
		temp_width = (temp_width * TIMER0_1uS_CNT);
		len += itoa_10(temp_width, (str + 2));
		str[len++] = '\r';
		str[len++] = '\n';
		VirtualSerial_MultiByteToHost(str, (uint16_t) len);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int app_main (void)
{
	uint32_t					IR_Repeat_Cnt;

	SystemInit();
    Board_Init();
    MyUSB_Init();
	Timer_Init();

	GPIOInit();
	Set_LED(1);

	IR_Data_Buffer_Init();
	IR_Transmit_Buffer_Init();
	IR_Repeat_Cnt = 0;

	while (1)                                /* Loop forever */
	{
		uint32_t 					temp_level, temp_width;
		uint8_t						input_char;

		USB_task_in_main_loop();

		if(VirtualSerial_OneByteFromHost(&input_char)!=0)
		{
			ProcessInputChar(input_char);
		}

		USB_task_in_main_loop();

		switch(Read_CMD_Status())
		{
			case ENUM_CMD_STOP_CMD_RECEIVED:
				IR_Repeat_Cnt=0;
				Clear_CMD_Status();
				{
					char str[2];
					int  len=0;
					str[len++] = 'S';
					str[len++] = '\n';
					VirtualSerial_MultiByteToHost(str, (uint16_t) len);
					USB_task_in_main_loop();
				}
				break;

			case ENUM_CMD_REPEAT_COUNT_RECEIVED:
				IR_Repeat_Cnt += Next_Repeat_Count_Get();
				Next_Repeat_Count_Set(0);
				Clear_CMD_Status();
				{
					char str[2];
					int  len=0;
					str[len++] = 'C';
					str[len++] = '\n';
					VirtualSerial_MultiByteToHost(str, (uint16_t) len);
					USB_task_in_main_loop();
				}
				break;

			case ENUM_CMD_WIDTH_DATA_READY:
				while(bIrTimeIndexOut_Output != bIrTimeIndexIn_Output)
				{
					USB_task_in_main_loop();
				}
				while(IR_Data_Buffer_Pop(&temp_level, &temp_width))
				{
					IR_Transmit_Buffer_Push(temp_level, temp_width);
				}
				PWM_period = Next_PWM_Period_Get();
				PWM_duty_cycle = Next_DutyCycle_Period_Get();
				{
					char str[16];
					int  len;
					len = itoa_10(bIrTimeIndexIn_Output, str);
					str[len++] = ' ';
					len += itoa_10(bIrTimeIndexOut_Output, (str+len));
					str[len++] = ' ';
					str[len++] = (Read_If_CheckSum_OK)?'o':'X';
					str[len++] = '\n';
					VirtualSerial_MultiByteToHost(str, (uint16_t) len);
					USB_task_in_main_loop();
				}
				IR_Transmit_Buffer_StartSend();
				Clear_CMD_Status();
				break;

			default:
				break;
		}

		//if(bIrTimeIndexOut_Output == bIrTimeIndexIn_Output)
//		{
//			if (IR_Repeat_Cnt>0)
//			{
//				IR_Repeat_Cnt--;
//				while(IR_Data_Buffer_Pop(&temp_level, &temp_width))
//				{
//                  IR_Transmit_Buffer_Push(temp_level, temp_width);
//				}
//			}
//		}

		//
		// Implement Tx Buffer UART output to make sure Parser performance
		//
		//Output_Tx_Buffer_UART();

//		// Check if pulse available
//		if (bIrTimeIndexOut != bIrTimeIndexIn)
//		{
//		    uint32_t	wTimeStamp;
//			uint8_t 	pause_dec_value[16], bLevel;
//			uint8_t 	*ptr_reverse = pause_dec_value, *ptr = pause_dec_value, bytes_to_write;
//
//			wTimeStamp = sRC_TIMETABLE[bIrTimeIndexOut].wTimeStamp;
//			bLevel = sRC_TIMETABLE[bIrTimeIndexOut].bLevel;
//			bIrTimeIndexOut = INC_INDEX8(bIrTimeIndexOut, IR_TBL_MAX);
//
//			pause_dec_value[0]=(bLevel!=0)?'1':'0';
//			pause_dec_value[1]=':';
//			bytes_to_write = 2;
//
//			ptr_reverse = ptr = pause_dec_value + 2;
//			do
//			{
//				*ptr_reverse++ = (wTimeStamp % 10) + '0';
//				wTimeStamp /= 10;
//				bytes_to_write++;
//			}
//			while (wTimeStamp > 0);
//
//			ptr_reverse--;
//			while(ptr < ptr_reverse)
//			{
//				uint8_t	tmp_char;
//				tmp_char = *ptr_reverse;
//				*ptr_reverse--= *ptr;
//				*ptr++ = tmp_char;
//			}
//
//			pause_dec_value[bytes_to_write++] = '\r';
//			pause_dec_value[bytes_to_write++] = '\n';
//			pause_dec_value[bytes_to_write] = 0;
//
//			USB_task_in_main_loop();
//			VirtualSerial_MultiByteToHost(pause_dec_value,bytes_to_write);
//		}
//
//		USB_task_in_main_loop();

		//
		// Here we assume that previous Tx are either done or same frequency/duty-cycle
		//

//		{
//			char str[16];
//			int  len;
//			len = itoa_10(bIrTimeIndexIn_Output, str);
//			str[len++] = '\n';
//			len += itoa_10(bIrTimeIndexOut_Output, (str+len));
//			str[len++] = '\n';
//			VirtualSerial_MultiByteToHost(str, (uint16_t) len);
//
//		}



	}
}
