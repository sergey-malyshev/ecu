/***
* led2.c - ������ ���������� ����������
* ������: 1.0
* ������: 01.03.18
***/

#ifndef _LED1_H_
#define _LED1_H_

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
/****************************************************************/
// ���������� ����������
/****************************************************************/
void * pxTaskLed1;

/* ������������� */

void Led1Init (void);

/* ���������� led2 */
void vTaskLED1(void *pvParameters);

#endif
