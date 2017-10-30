/*
 * parser.c
 *
 *  Created on: 2017年10月26日
 *      Author: Jeremy.Hsiao
 */

#include "board.h"
#include "gpio.h"
#include "Timer.h"
#include "Uart.h"
#include "usb_common.h"

#include "Common.h"
#include "app_timer.h"
#include "parser.h"

ENUM_PARSING_STATE ProcessInputChar_and_ReturnNextState(ENUM_PARSING_STATE current_state, uint8_t input_byte)
{
    static uint32_t         		temp_buf = 0;
    static uint32_t         		temp_level = 0;
    ENUM_PARSING_STATE      		next_state;

    switch (current_state)
    {
    	case ENUM_PARSING_STATE_WAIT_SYNC_BYTE:
            if(input_byte!=0xff)
            {
                next_state = ENUM_PARSING_STATE_WAIT_SYNC_BYTE;
            }
            else // Neither 0xffxx is allowed for carrier_width not 0xffffffff is allowed for pulse width, so it is used as "preamble" of data string (at least 4 0xff)
            {
                next_state = ENUM_PARSING_STATE_WAIT_CARRIER_WIDTH_HIGH;
            }
            break;

        case ENUM_PARSING_STATE_WAIT_CARRIER_WIDTH_HIGH:
            if(input_byte!=0xff)
            {
                temp_buf = input_byte;
                next_state = ENUM_PARSING_STATE_WAIT_CARRIER_WIDTH_LOW;
            }
            else // Neither 0xffxx is allowed for carrier_width not 0xffffffff is allowed for pulse width, so it is used as "preamble" of data string (at least 4 0xff)
            {
                next_state = ENUM_PARSING_STATE_WAIT_CARRIER_WIDTH_HIGH;
            }
            break;

        case ENUM_PARSING_STATE_WAIT_CARRIER_WIDTH_LOW:
            PWM_period = ((temp_buf*256) + input_byte)/8;   // here we use 1us-count, original unit is 1/8us for each count so divided by 8
            temp_level = 1;
            next_state = ENUM_PARSING_STATE_WAIT_PULSE_WIDTH_WAIT_1ST_INPUT;
            break;

        case ENUM_PARSING_STATE_WAIT_PULSE_WIDTH_WAIT_1ST_INPUT:
            if((input_byte&0x80)!=0)    // High bit not zero --> 4 bytes width data (highest bit will be removed)
            {
                temp_buf = (input_byte&0x80);
                next_state = ENUM_PARSING_STATE_WAIT_PULSE_WIDTH_WAIT_LONG_2ND;
            }
            else // otherwise 2 byte width data
            {
                temp_buf = input_byte;
                next_state = ENUM_PARSING_STATE_WAIT_PULSE_WIDTH_WAIT_WORD_LOW;
            }
            break;

        //
        // Finish receiving 2-byte width
        //
        case ENUM_PARSING_STATE_WAIT_PULSE_WIDTH_WAIT_WORD_LOW:
            temp_buf = (temp_buf<<8) + input_byte;
            IR_Transmit_Buffer_Push(temp_level,temp_buf);
            temp_level = (temp_level!=0)?0:1;
            next_state = ENUM_PARSING_STATE_WAIT_PULSE_WIDTH_WAIT_1ST_INPUT;
            break;
        //END

        //
        //  receiving 4-byte width
        //
        case ENUM_PARSING_STATE_WAIT_PULSE_WIDTH_WAIT_LONG_2ND:
            temp_buf = (temp_buf<<8) + input_byte;
            next_state = ENUM_PARSING_STATE_WAIT_PULSE_WIDTH_WAIT_LONG_3RD;
            break;

        case ENUM_PARSING_STATE_WAIT_PULSE_WIDTH_WAIT_LONG_3RD:
            temp_buf = (temp_buf<<8) + input_byte;
            next_state = ENUM_PARSING_STATE_WAIT_PULSE_WIDTH_WAIT_LONG_4TH;
            break;

        case ENUM_PARSING_STATE_WAIT_PULSE_WIDTH_WAIT_LONG_4TH:
            temp_buf = (temp_buf<<8) + input_byte;
            if(temp_buf==0xffffffff)
            {
                next_state = ENUM_PARSING_STATE_WAIT_SYNC_BYTE;    // 0xffffffff not allowed, so back to initial state
            }
            else
            {
                IR_Transmit_Buffer_Push(temp_level,temp_buf);
                temp_level = (temp_level!=0)?0:1;
                next_state = ENUM_PARSING_STATE_WAIT_PULSE_WIDTH_WAIT_1ST_INPUT;
            }
            break;
        //END

        case ENUM_PARSING_STATE_UNKNOWN_STATE:
            if(input_byte==0xff)
            {
                next_state = ENUM_PARSING_STATE_WAIT_SYNC_BYTE;		// at least 0xffff to be sure
            }
            else
            {
                next_state = ENUM_PARSING_STATE_UNKNOWN_STATE;
            }
            IR_Transmit_Buffer_Init();
            break;

        default:
            next_state = ENUM_PARSING_STATE_UNKNOWN_STATE;  // Use to catch unknown-unknown situation
            break;
    }

    return next_state;
}

