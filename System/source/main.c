/******************************************************************************
 * @file	main.c
 * @author	Малышев Сергей  <onega.malishev@yandex.ru>
 * @version v1.0
 * @date	21/06/2019
 * @brief	Application Entry Point (AEP).
 * 			- Создание и инициализация задач xTaskCreate()
 * 			- Запуск планировщика vTaskStartScheduler()
 *
 ********************************************************************************
 * ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ «КАК ЕСТЬ», БЕЗ КАКИХ-ЛИБО
 * ГАРАНТИЙ, ЯВНО ВЫРАЖЕННЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ ГАРАНТИИ ТОВАРНОЙ
 * ПРИГОДНОСТИ, СООТВЕТСТВИЯ ПО ЕГО КОНКРЕТНОМУ НАЗНАЧЕНИЮ И ОТСУТСТВИЯ
 * НАРУШЕНИЙ, НО НЕ ОГРАНИЧИВАЯСЬ ИМИ. ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ
 * ПРЕДНАЗНАЧЕНО ДЛЯ ОЗНАКОМИТЕЛЬНЫХ ЦЕЛЕЙ И НАПРАВЛЕНО ТОЛЬКО НА
 * ПРЕДОСТАВЛЕНИЕ ДОПОЛНИТЕЛЬНОЙ ИНФОРМАЦИИ О ПРОДУКТЕ, С ЦЕЛЬЮ СОХРАНИТЬ ВРЕМЯ
 * ПОТРЕБИТЕЛЮ. НИ В КАКОМ СЛУЧАЕ АВТОРЫ ИЛИ ПРАВООБЛАДАТЕЛИ НЕ НЕСУТ
 * ОТВЕТСТВЕННОСТИ ПО КАКИМ-ЛИБО ИСКАМ, ЗА ПРЯМОЙ ИЛИ КОСВЕННЫЙ УЩЕРБ, ИЛИ
 * ПО ИНЫМ ТРЕБОВАНИЯМ, ВОЗНИКШИМ ИЗ-ЗА ИСПОЛЬЗОВАНИЯ ПРОГРАММНОГО ОБЕСПЕЧЕНИЯ
 * ИЛИ ИНЫХ ДЕЙСТВИЙ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ.
 *
 *                              2019 "KeyPi"
 *********************************************************************************/

/* Include General */
#include "misc.h"
#include "FreeRTOS.h"
#include "task.h"

/* Include Tasks header files */
#include "led1.h"
#include "led2.h"
#include "led3.h"
#include "led4.h"

/* Application Entry Point. Попадаем сюда из Reset_Handler после начальной инициализации */
int main(void)
{
	/* Configure priority format. 4 bits for pre-emption priority; 0 bits for subpriority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	/* Создаем задачи для планирования */
	/*--------------------------------------------------------------------------------------*/
	/* LED1  */
	xTaskCreate( vTaskLED1, ( const char * const ) "LED1", configMINIMAL_STACK_SIZE, NULL, 2,
	                                 ( xTaskHandle * ) &pxTaskLed1);

	/* LED2  */
	xTaskCreate( vTaskLED2, ( const char * const ) "LED2", configMINIMAL_STACK_SIZE, NULL, 2,
		                            ( xTaskHandle * ) &pxTaskLed2);

	/* LED3  */
	xTaskCreate( vTaskLED3, ( const char * const ) "LED3", configMINIMAL_STACK_SIZE, NULL, 2,
		                            ( xTaskHandle * ) &pxTaskLed3);

	/* LED4  */
	xTaskCreate( vTaskLED4, ( const char * const ) "LED4", configMINIMAL_STACK_SIZE, NULL, 2,
									( xTaskHandle * ) &pxTaskLed4);

	/*---------------------------------------------------------------------------------------*/

	/* Запускаем планировщик задач */
	vTaskStartScheduler();

	/* ловушка, сюда мы попасть не должны */
	for(;;);

	return 0;
}
