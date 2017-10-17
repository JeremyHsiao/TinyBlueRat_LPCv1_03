/*
 * Common.c
 *
 *  Created on: 2013/1/22
 *      Author: Jeremy.Hsiao
 */

#include "../src_app_IR_Width_Detector/Common.h"

#include "chip.h"

inline uint32_t TIMER_DIFF32(uint32_t current, uint32_t previous)
{
	uint32_t	timer_diff;

	if ( previous > current )
	{
		timer_diff = (((uint64_t)0x100000000) - previous) + (current);
	}
	else
	{
		timer_diff = (current) - previous;
	}
	return timer_diff;
}

inline uint16_t TIMER_DIFF16(uint16_t current, uint16_t previous)
{
	uint16_t	timer_diff;

	if ( previous > current )
	{
		timer_diff = (((uint32_t)0x10000) - previous) + (current);
	}
	else
	{
		timer_diff = (current) - previous;
	}
	return timer_diff;
}

inline uint16_t INC_INDEX16(uint16_t index, uint16_t max)
{
	index++;
	if(index >= max)
	{
		index = 0;
	}
	return index;
}

inline uint8_t IN_RANGE16(uint16_t value, uint16_t min, uint16_t max)
{
	if ((value>=min)&&(value<=max))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

inline uint8_t CHECK_LEVEL_RANGE16(uint8_t level, uint8_t expected_level, uint16_t value, uint16_t min, uint16_t max)
{
	if ((level==expected_level)&&(value>=min)&&(value<=max))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

inline uint8_t INC_INDEX8(uint8_t index, uint32_t max)
{
	index++;
	if(index >= max)
	{
		index = 0;
	}
	return index;
}

