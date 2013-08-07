#ifndef	_EXTEEPROM_H
#define	_EXTEEPROM_H

//
#define I2C_INTERFACE_ID	(I2C0)
#define I2C_RETRY_TIME		(3)
#define I2C_RETRY_WAIT_MS	(10)


#define M24C32_PAGE_WRITE
#define M24C32_EPROM_PAGE_SIZE			(32)
#define M24C32_EPROM_SLAVE_ADDR			(0xA0)

extern void	WriteEEPROM_OneByte ( uint16_t Address, uint8_t write_data );
extern void	WriteEEPROM_MultiByte ( uint16_t Address, uint8_t *write_data, uint8_t MaxCounter );
extern void ReadEEPROM ( uint16_t Address, uint8_t *read_data, uint8_t Rcounter );
extern void StoreEEPROM(uint16_t wAddr, uint8_t bData);

#endif //_EXTEEPROM_H
