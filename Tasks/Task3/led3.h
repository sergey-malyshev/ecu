/***
* led3.h - задача управлени€ индикацией
* верси€: 1.0
* создан: 01.03.18
***/
#ifndef _LED3_H_
#define _LED3_H_

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
/****************************************************************/
// √лобальные переменные
/****************************************************************/
void * pxTaskLed3;

/* »нициализаци€ */
void Led3Init (void);

/* управление led2 */
void vTaskLED3(void *pvParameters); 

#endif
