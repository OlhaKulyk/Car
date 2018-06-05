#ifndef RPCONNECTION_H
#define RPCONNECTION_H

//#include "stdarg.h"
//#include <stdio.h>

#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

void RPConnection_Init(void);

//void SendToRaspberryPi(uint8_t* data, uint8_t count);
signed int getNeededAngle(void);
signed int getNeededSpeed(void);

//void SendToRaspberryPi(char* fmt, ...);

#endif /* RPCONNECTION_H */
