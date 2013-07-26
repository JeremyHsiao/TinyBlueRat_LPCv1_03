extern int UARTInit(uint32_t Baudrate);
extern int UART_DeInit(void);
extern void UART_IRQHandler(void);
extern inline uint16_t ReadOneByteFromUARTRingBuffer(uint8_t *return_data);
extern inline void WriteOneByteToUARTRingBuffer(uint8_t sent_data);
extern inline uint16_t ReadMultiByteFromUARTRingBuffer(uint8_t *return_data, uint16_t bytes_to_read);
extern inline void WriteMultiByteToUARTRingBuffer(uint8_t *sent_data, uint16_t bytes_to_write);
