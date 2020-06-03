/***
* led2.c - задача управлени€ индикацией
* верси€: 1.0
* создан: 01.03.18
***/

#ifndef _LED1_H_
#define _LED1_H_

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
/****************************************************************/
// √лобальные переменные
/****************************************************************/
void * pxTaskLed1;

/* »нициализаци€ */

void Led1Init (void);

/* управление led2 */
void vTaskLED1(void *pvParameters);

#endif
