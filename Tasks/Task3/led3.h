/***
* led3.h - ������ ���������� ����������
* ������: 1.0
* ������: 01.03.18
***/
#ifndef _LED3_H_
#define _LED3_H_

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
/****************************************************************/
// ���������� ����������
/****************************************************************/
void * pxTaskLed3;

/* ������������� */
void Led3Init (void);

/* ���������� led2 */
void vTaskLED3(void *pvParameters); 

#endif
