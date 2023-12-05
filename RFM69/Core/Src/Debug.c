#include "string.h"
#include "stdio.h"
#include "main.h"


extern UART_HandleTypeDef huart2;

void Log(char *inputString){
	char debugString[100];
	int debugStringLen;
	debugStringLen = sprintf(debugString,inputString);
	HAL_UART_Transmit(&huart2, (uint8_t *)debugString, debugStringLen, 100);
}
