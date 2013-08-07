
/***************************************************************************
* INCLUDE FILES
***************************************************************************/
/*------------------------------------*/
/* Include files					  */
/*------------------------------------*/

#include "chip.h"
#include "board.h"
#include "string.h"
#include "i2c.h"
#include "Timer.h"
#include "ExtEEPROM.h"
/*------------------------------------*/
/* Local data or definition 		  */
/*------------------------------------*/

#define ONEBYTE_WRITE_BUF_SIZE	(2+1)
void WriteEEPROM_OneByte ( uint16_t Address, uint8_t write_data )
{
	uint8_t 			I2CBuffer[ONEBYTE_WRITE_BUF_SIZE];
	int8_t				retry_cnt = I2C_RETRY_TIME;
	int					ret;

	I2CBuffer[0] = (uint8_t)(Address >> 8);
	I2CBuffer[1] = (uint8_t) Address;
	I2CBuffer[2] = write_data;
	ret = Chip_I2C_MasterSend(I2C_INTERFACE_ID, (M24C32_EPROM_SLAVE_ADDR>>1), I2CBuffer, ONEBYTE_WRITE_BUF_SIZE);  // return 0 if all written

	while ((ret>0)&&(retry_cnt>0))
	{
		Delayus(I2C_RETRY_WAIT_MS*1000);
		ret = Chip_I2C_MasterSend(I2C_INTERFACE_ID, (M24C32_EPROM_SLAVE_ADDR>>1), I2CBuffer, ONEBYTE_WRITE_BUF_SIZE);
		retry_cnt--;;
	}

	if (ret>0)
	{
		return;
		// trip error here.
	}
}

#define PAGE_WRITE_BUF_SIZE		(M24C32_EPROM_PAGE_SIZE+2)
void WriteEEPROM_32_64_Page_Write ( uint16_t Address, uint8_t *data_ptr, uint8_t data_length )
{
	uint8_t 			I2CBuffer[PAGE_WRITE_BUF_SIZE];
	int8_t				retry_cnt = I2C_RETRY_TIME;
	int					ret;

	I2CBuffer[0] = (uint8_t)(Address >> 8);
	I2CBuffer[1] = (uint8_t) Address;
	memcpy((I2CBuffer+2),data_ptr,data_length);
	ret = Chip_I2C_MasterSend(I2C_INTERFACE_ID, (M24C32_EPROM_SLAVE_ADDR>>1), I2CBuffer, (data_length+2));  // return 0 if all written

	while ((ret>0)&&(retry_cnt>0))
	{
		Delayus(I2C_RETRY_WAIT_MS*1000);
		ret = Chip_I2C_MasterSend(I2C_INTERFACE_ID, (M24C32_EPROM_SLAVE_ADDR>>1), I2CBuffer, (data_length+2));
		retry_cnt--;
	}

	if (ret>0)
	{
		return;
		// trip error here.
	}
}

void WriteEEPROM_MultiByte ( uint16_t Address, uint8_t *write_data, uint8_t MaxCounter )
{
	uint16_t	Current_addr;
	uint8_t		*data_ptr;
	uint32_t	temp, remaining_length;

#ifdef M24C32_PAGE_WRITE

	Current_addr = Address;
	remaining_length = MaxCounter;
	data_ptr = write_data;

	// Segment 1: data before a complete page
	temp = Current_addr % M24C32_EPROM_PAGE_SIZE;
	if(temp!=0)
	{
		temp = M24C32_EPROM_PAGE_SIZE-temp;				// remaining_byte_cnt before page boundary

		if(temp>remaining_length)					// more than data to be sent, set to length of data
		{
			temp = remaining_length;
		}
		WriteEEPROM_32_64_Page_Write( Current_addr, data_ptr , temp );
		data_ptr += temp;
		Current_addr += temp;
		remaining_length -= temp;
	}

	// Segment 2: full-page data sending at page boundary
	while (remaining_length>=M24C32_EPROM_PAGE_SIZE)
	{
		temp = M24C32_EPROM_PAGE_SIZE;						// full-page
		WriteEEPROM_32_64_Page_Write( Current_addr, data_ptr , temp );
		data_ptr += temp;
		Current_addr += temp;
		remaining_length -= temp;
	}

	// Segment 3: remaining non-full-page data sending at page boundary
	if (remaining_length> 0)
	{
		temp = remaining_length;
		WriteEEPROM_32_64_Page_Write( Current_addr, data_ptr , temp );
//		data_ptr += temp;
//		Current_addr += temp;
//		remaining_length -= temp;
	}


#else
    data_ptr = write_data;
	for ( Counter=0; Counter<MaxCounter; Counter++)
	{
		WriteEEPROM_OneByte(Address,*data_ptr);
		Address++;
		data_ptr++;
	}
#endif
}

void ReadEEPROM ( uint16_t Address, uint8_t *read_data, uint8_t Rcounter )
{
	uint8_t 			I2CBuffer[2];	// Write Address first (2byte)
	int8_t				retry_cnt = I2C_RETRY_TIME;
	int					ret;

	I2CBuffer[0] = (uint8_t)(Address >> 8);
	I2CBuffer[1] = (uint8_t) Address;

	ret = Chip_I2C_MasterCmd2ByteRead(I2C_INTERFACE_ID, (M24C32_EPROM_SLAVE_ADDR>>1), I2CBuffer, read_data, Rcounter);

	while ((ret>0)&&(retry_cnt>0))
	{
		Delayus(I2C_RETRY_WAIT_MS*1000);
		ret = Chip_I2C_MasterCmd2ByteRead(I2C_INTERFACE_ID, (M24C32_EPROM_SLAVE_ADDR>>1), I2CBuffer, read_data, Rcounter);
		retry_cnt--;
	}

	if (ret>0)
	{
		return;
		// trip error here.
	}
}

// Check if data is different before write
void StoreEEPROM(uint16_t wAddr, uint8_t bData)
{
	uint8_t		temp_buffer[1];

	ReadEEPROM(wAddr, temp_buffer, 1);
	if (temp_buffer[0] != bData)
    {
		WriteEEPROM_OneByte(wAddr, bData);
		ReadEEPROM(wAddr, temp_buffer, 1);
		if (temp_buffer[0] != bData)
		{
			return;
			// trip error here.
		}
    }
}
