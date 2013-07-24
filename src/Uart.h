extern int UARTInit(uint32_t Baudrate);
extern int UART_DeInit(void);
extern void UART_IRQHandler(void);
extern inline uint8_t ReadOneByteFromUARTRingBuffer(uint8_t *return_data);
extern inline void WriteOneByteToUARTRingBuffer(uint8_t sent_data);
extern inline uint8_t ReadMultiByteFromUARTRingBuffer(uint8_t *return_data, uint8_t bytes_to_read);
extern inline void WriteMultiByteToUARTRingBuffer(uint8_t *sent_data, uint8_t bytes_to_write);
