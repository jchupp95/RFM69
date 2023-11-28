#ifndef SRC_RFM69_RFM69_STM32_H_
#define SRC_RFM69_RFM69_STM32_H_

#include "stdio.h"
#include "stdbool.h"

void noInterrupts();                // function to disable interrupts
void interrupts();                  // function to enable interrupts
void RFM69_SetCSPin(bool);          // function to control the GPIO tied to RFM69 chip select (parameter HIGH or LOW)
bool RFM69_ReadDIO0Pin(void);       // function to read GPIO connected to RFM69 DIO0 (RFM69 interrupt signalling)
uint8_t SPI_transfer8(uint8_t);     // function to transfer 1byte on SPI with readback
void Serialprint(char*);            // function to print to serial port a string
bool Timeout_IsTimeout1(void);      // function for timeout handling, checks if previously set timeout expired
void Timeout_SetTimeout1(uint16_t); // function for timeout handling, sets a timeout, parameter is in milliseconds (ms)

#endif /* SRC_RFM69_RFM69_STM32_H_ */
