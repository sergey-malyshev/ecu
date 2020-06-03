/******************************************************************************
 * @file	FreeRTOSConfig.h
 * @author	Малышев Сергей  <onega.malishev@yandex.ru>
 * @version v1.0
 * @date	21/06/2019
 * @brief	Конфигурация ОС FREERTOS
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

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


/* Тип многозадачности (0 - кооперативная, 1 - вытесняющая)	*/
#define configUSE_PREEMPTION            1

/* Частота тактирования ядра */
#define configCPU_CLOCK_HZ              ( ( unsigned long ) 168000000 )

/* Частота срабатывания системного таймера, Гц				 */
#define configTICK_RATE_HZ              ( ( portTickType ) 1000 )

/* Максимальный уровень приоритета задач */
#define configMAX_PRIORITIES            ( 8 )

/* Минимальный размер стека задачи (слов, 1 слово = 4 байта) */
#define configMINIMAL_STACK_SIZE        ( ( unsigned short ) 100 )

/* Размер кучи FREERTOS */
#define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 5 * 1024 ) )

/* Максимальная длина имени задачи(в символах ASCII) */
#define configMAX_TASK_NAME_LEN         ( 16 )

/* Разрядность системного таймера  (0 - 32 бит; 1 - 16 бит) */
#define configUSE_16_BIT_TICKS          0

/* Подключение трассировки (0 - трассировка отключена, 1 - трассировка включена) */
#define configUSE_TRACE_FACILITY        0

#define configIDLE_SHOULD_YIELD         1

#define configUSE_MUTEXES               1
#define configUSE_COUNTING_SEMAPHORES   1
#define configUSE_ALTERNATIVE_API       0
#define configCHECK_FOR_STACK_OVERFLOW  0
#define configUSE_RECURSIVE_MUTEXES     1
#define configQUEUE_REGISTRY_SIZE       8
#define configGENERATE_RUN_TIME_STATS   0
#define configUSE_IDLE_HOOK             0
#define configUSE_TICK_HOOK             0
#define configUSE_CO_ROUTINES           0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Настройки службы таймеров */
#define configUSE_TIMERS				0
#define configTIMER_TASK_PRIORITY		( 2 )
#define configTIMER_QUEUE_LENGTH		10
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 2 )

/* API FREERTOS (1 - API доступен, 0 - API недоступен). */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetIdleTaskHandle 			0
#define INCLUDE_xTaskAbortDelay 				0
#define INCLUDE_xQueueGetMutexHolder 			1
#define INCLUDE_xTaskGetHandle 					0
#define INCLUDE_uxTaskGetStackHighWaterMark 	1
#define INCLUDE_eTaskGetState 					0
#define INCLUDE_xTaskResumeFromISR 				1
#define INCLUDE_xTimerPendFunctionCall 			0
#define INCLUDE_xTaskGetSchedulerState 			1
#define INCLUDE_xTaskGetCurrentTaskHandle		1
#define INCLUDE_xSemaphoreGetMutexHolder		1
#define INCLUDE_vTaskCleanUpResources   		1

/* Cortex-M specific definitions. */
#define configPRIO_BITS       					4        /* 15 priority levels */

/* The lowest interrupt priority that can be used in a call to a "set priority" function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

/* Приоритет 15 для системного таймера (SysTick_Handler) и планировщика (PendSV_Handler) */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Приоритет системных вызовов */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Normal assert() semantics without relying on the provision of an assert.h header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }	

/* Переопределение обработчиков прерываний для порта */
#define vPortSVCHandler 		SVC_Handler		//  Системный вызов (запуск первой задачи)
#define xPortPendSVHandler 		PendSV_Handler	//	Переключение контекста задач
#define xPortSysTickHandler 	SysTick_Handler	//	Системный таймер (тактирование планировщика задач)


#endif /* FREERTOS_CONFIG_H */
