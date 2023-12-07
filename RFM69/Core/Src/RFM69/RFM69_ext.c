// module interface, platform specific functions

#include "RFM69_ext.h"
#include "Stdio.h"
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "../Debug.h"

extern SPI_HandleTypeDef hspi1;
bool GO_AHEAD_READ_RFM69;
bool rststate;
extern char log_buffer[30];


void RFM69_RST(void) {
  HAL_GPIO_WritePin(RFM69_RST_GPIO_Port, RFM69_RST_Pin, 1);
  HAL_Delay(10);
  HAL_GPIO_WritePin(RFM69_RST_GPIO_Port, RFM69_RST_Pin, 0);
  HAL_Delay(50);
}

// extern functions
bool noInterrupts()                // function to disable interrupts
{
GO_AHEAD_READ_RFM69 = 0;
return true;
}

bool interrupts()                  // function to enable interrupts
{
GO_AHEAD_READ_RFM69 = 1;
return true;
}

void RFM69_SetCSPin(bool SetCSValue)          // function to control the GPIO tied to RFM69 chip select (parameter HIGH or LOW)
{
HAL_GPIO_WritePin(RFM69_CS_GPIO_Port, RFM69_CS_Pin, SetCSValue); //GPIOA, GPIO_PIN_5 is LED on Nucleao, for testing only.
}

bool RFM69_ReadDIO0Pin(void)       // function to read GPIO connected to RFM69 DIO0 (RFM69 interrupt signalling)
{
  if (GO_AHEAD_READ_RFM69 == 1 && HAL_GPIO_ReadPin(RFM69_IRQ_GPIO_Port, RFM69_IRQ_Pin) == 1)
  {
    return true;
  }
  else
  {
    return false;
  }
}

uint8_t SPI_transfer8 (uint8_t tx_byte) // function to transfer 1byte on SPI with readback
{
  uint8_t rx_byte;

  HAL_SPI_TransmitReceive(&hspi1, &tx_byte, &rx_byte, 1, 10);
  return rx_byte;
}

void SerialPrint(char* debugString)            // function to print to serial port a string
{
  Log(debugString);
}


static uint32_t thistimeout1 = 100;
bool Timeout_IsTimeout1(void)      // function for timeout handling, checks if previously set timeout expired
{
  if(HAL_GetTick() >= thistimeout1)
    {
      sprintf(log_buffer,"TimeOut1!\r\n");
      Log(log_buffer);
      return true;
    }
  else
  {
    return false;
  }
}
void Timeout_SetTimeout1(uint16_t settimeoutvalue) // function for timeout handling, sets a timeout, parameter is in milliseconds (ms)
{
  thistimeout1 = HAL_GetTick() + settimeoutvalue;
}
