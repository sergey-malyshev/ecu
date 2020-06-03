/***
* led3.h - ������ ���������� ����������
* ������: 1.0
* ������: 01.03.18
***/
#ifndef _LED4_H_
#define _LED4_H_

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
/****************************************************************/
// ���������� ����������
/****************************************************************/
void * pxTaskLed4;

/* ������������� */
void Led4Init (void);

/* ���������� led2 */
void vTaskLED4(void *pvParameters);

#endif
