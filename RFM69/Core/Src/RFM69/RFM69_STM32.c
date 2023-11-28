#include "stm32l4xx_hal.h"
#include "stdio.h"
#include "stdbool.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;

// function to disable interrupts
void noInterrupts()
{
	__disable_irq();
}

// function to enable interrupts
void interrupts()
{
	__enable_irq();
}

// function to control the GPIO tied to RFM69 chip select (parameter HIGH or LOW)
void RFM69_SetCSPin(bool state)
{
  HAL_GPIO_WritePin(RFM69_CS_GPIO_Port, RFM69_CS_Pin, state);
}

// function to read GPIO connected to RFM69 DIO0 (RFM69 interrupt signalling)
bool RFM69_ReadDIO0Pin(void)
{
  return HAL_GPIO_ReadPin(RFM69_IRQ_GPIO_Port, RFM69_IRQ_Pin);
}

// function to transfer 1byte on SPI with readback
uint8_t SPI_transfer8 (uint8_t tx_byte) { // function to transfer 1byte on SPI with readback
  uint8_t rx_byte;

  HAL_SPI_TransmitReceive(&hspi1, &tx_byte, &rx_byte, 1, 10);

  return rx_byte;
}

// function to print to serial port a string
void Serialprint(char* logString)
{
 ;// TODO: Implement this
}

static uint32_t thisTimeout;

// function for timeout handling, checks if previously set timeout expired
bool Timeout_IsTimeout1(void)
{
  if(HAL_GetTick() >= thisTimeout)
    {
      return true;
    }
  else
  {
    return false;
  }
}

// function for timeout handling, sets a timeout, parameter is in milliseconds (ms)
void Timeout_SetTimeout1(uint16_t setTimeoutValue)
{
  thisTimeout = HAL_GetTick() + setTimeoutValue;
}
