TinyBlueRat_LPCv1_03
====================

This repository gathered all LPCOpen Platform v1.03 code for NXP LPC11U37/401 MCU under one directory.
It is the base for further development.

The following functionality and driver code has been verified with test code and with my real application (not in GitHub because it is company IP)

1. Timer32_0: Capture0 to detect input pulse width (both high and low level)
							Match0 to control output pulse width (both high and low level)
							Match1 Software delay timer in unit of us
							Match2 Software running timer in unit of ms
							Match3 0.5 sec periodic timer
2. Timer32_1: Match0 to control duty cycle of PWM
							Match3 to contorl period of PWM
3. USB: CDC, HID-Mouse, Composite (CDC+HID-Mouse)
4. Interrupt Flexible interrupt#0 on Pin P1_15 (falling edge triggered)
5. I2C:	Master Tx/Rx on EEPROM
6. API to read/write MCU internal EEPROM
7. UART Tx/Rx (using interrupt and ring-buffer so that non-blocking during Tx/Rx)
8. Low-speed ADC on Pin P0_11 to detect ADC-key
9. GPIO as input/outout

Watchdog timer function is implemented but not yet tested.