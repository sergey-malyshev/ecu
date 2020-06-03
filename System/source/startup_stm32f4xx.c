/******************************************************************************
 * @file	startup_stm32f4xx.c
 * @author	Малышев Сергей  <onega.malishev@yandex.ru>
 * @version v1.0
 * @date	21/06/2019
 * @brief	stm32f407 Devices vector table
 * 			Этот модуль предоставляет:
 * 			- инициализирует указатель стека SP (value from address 0x00000000)
 * 			- инициализирует PC == Reset_Handler
 * 			- инициализирует таблицу векторов прерываний
 * 			- инициализирует подсистему тактирования МК
 * 			- выполняет вызов функции main()
 * 			После сброса, Cortex-M4 микроконтроллер находится:
 * 			Режим: поток (Thread);
 * 			Уровень выполненния кода: привелигерованный;
 * 			Cтек: главный (MSP).
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

/*----------Includes files------- ------------------------------------------ */
#include "stm32f4xx.h"
#include "core_cm4.h"
#include "startup_stm32f4xx.h"


/*----------Таблица векторов прерываний ---------------------------------------- */
ISRVectorsTables g_pfnVectors __attribute__((section (".isr_vector"))) =
{
  /*----------Cortex-M4F Processor Exceptions Numbers----------------------------*/
  (void *)&_estack,     	    /*!< The initial stack pointer         			 */
  Reset_Handler,                /*!< -15: Reset Handler                          */
  NMI_Handler,                  /*!< -14: NMI Handler                            */
  HardFault_Handler,            /*!< -13: Hard Fault Handler                     */
  MemManage_Handler,            /*!< -12: MPU Fault Handler                      */
  BusFault_Handler,             /*!< -11: Bus Fault Handler                      */
  UsageFault_Handler,           /*!< -10: Usage Fault Handler                    */
  0,0,0,0,                      /*!< -9...-6: Reserved                           */
  SVC_Handler,                  /*!< -5: SVCall Handler                          */
  DebugMon_Handler,             /*!< -4: Debug Monitor Handler                   */
  0,                            /*!< -3: Reserved                                */
  PendSV_Handler,               /*!< -2: PendSV Handler                          */
  SysTick_Handler,              /*!< -1: SysTick Handler                         */

  /*----------Device specific Interrupt Numbers----------------------------------*/
  WWDG_IRQHandler,              /*!<  0: Window WatchDog                         */
  PVD_IRQHandler,               /*!<  1: PVD through EXTI Line detection         */
  TAMP_STAMP_IRQHandler,        /*!<  2: Tamper, TimeStamps through the EXTI line*/
  RTC_WKUP_IRQHandler,          /*!<  3: RTC Wakeup through the EXTI line        */
  FLASH_IRQHandler,             /*!<  4: FLASH                                   */
  RCC_IRQHandler  ,             /*!<  5: RCC                                     */
  EXTI0_IRQHandler,             /*!<  6: EXTI Line0                              */
  EXTI1_IRQHandler,             /*!<  7: EXTI Line1                              */
  EXTI2_IRQHandler,             /*!<  8: EXTI Line2                              */
  EXTI3_IRQHandler,             /*!<  9: EXTI Line3                              */
  EXTI4_IRQHandler,             /*!< 10: EXTI Line4                              */
  DMA1_Stream0_IRQHandler,      /*!< 11: DMA1 Stream 0                           */
  DMA1_Stream1_IRQHandler,      /*!< 12: DMA1 Stream 1                           */
  DMA1_Stream2_IRQHandler,      /*!< 13: DMA1 Stream 2                           */
  DMA1_Stream3_IRQHandler,      /*!< 14: DMA1 Stream 3                           */
  DMA1_Stream4_IRQHandler,      /*!< 15: DMA1 Stream 4                           */
  DMA1_Stream5_IRQHandler,      /*!< 16: DMA1 Stream 5                           */
  DMA1_Stream6_IRQHandler,      /*!< 17: DMA1 Stream 6                           */
  ADC_IRQHandler,               /*!< 18: ADC1, ADC2 and ADC3s                    */
  CAN1_TX_IRQHandler,           /*!< 19: CAN1 TX                                 */
  CAN1_RX0_IRQHandler,          /*!< 20: CAN1 RX0                                */
  CAN1_RX1_IRQHandler,          /*!< 21: CAN1 RX1                                */
  CAN1_SCE_IRQHandler,          /*!< 22: CAN1 SCE                                */
  EXTI9_5_IRQHandler,           /*!< 23: External Line[9:5]s                     */
  TIM1_BRK_TIM9_IRQHandler,     /*!< 24: TIM1 Break and TIM9                     */
  TIM1_UP_TIM10_IRQHandler,     /*!< 25: TIM1 Update and TIM10                   */
  TIM1_TRG_COM_TIM11_IRQHandler,/*!< 26: TIM1 Trigger and Commutation and TIM11` */
  TIM1_CC_IRQHandler,           /*!< 27: TIM1 Capture Compare                    */
  TIM2_IRQHandler,              /*!< 28: TIM2                                    */
  TIM3_IRQHandler,              /*!< 29: TIM3                                    */
  TIM4_IRQHandler,              /*!< 30: TIM4                                    */
  I2C1_EV_IRQHandler,           /*!< 31: I2C1 Event                              */
  I2C1_ER_IRQHandler,           /*!< 32: I2C1 Error                              */
  I2C2_EV_IRQHandler,           /*!< 33: I2C2 Event                              */
  I2C2_ER_IRQHandler,           /*!< 34: I2C2 Error                              */
  SPI1_IRQHandler,              /*!< 35: SPI1                                    */
  SPI2_IRQHandler,              /*!< 36: SPI2                                    */
  USART1_IRQHandler,            /*!< 37: USART1                                  */
  USART2_IRQHandler,            /*!< 38: USART2                                  */
  USART3_IRQHandler,            /*!< 39: USART3                                  */
  EXTI15_10_IRQHandler,         /*!< 40: External Line[15:10]s                   */
  RTC_Alarm_IRQHandler,         /*!< 41: RTC Alarm (A and B) through EXTI Line   */
  OTG_FS_WKUP_IRQHandler,       /*!< 42: USB OTG FS Wakeup through EXTI line     */
  TIM8_BRK_TIM12_IRQHandler,    /*!< 43: TIM8 Break and TIM12                    */
  TIM8_UP_TIM13_IRQHandler,     /*!< 44: TIM8 Update and TIM13                   */
  TIM8_TRG_COM_TIM14_IRQHandler,/*!< 45:TIM8 Trigger and Commutation and TIM14   */
  TIM8_CC_IRQHandler,           /*!< 46: TIM8 Capture Compare                    */
  DMA1_Stream7_IRQHandler,      /*!< 47: DMA1 Stream7                            */
  FSMC_IRQHandler,              /*!< 48: FSMC                                    */
  SDIO_IRQHandler,              /*!< 49: SDIO                                    */
  TIM5_IRQHandler,              /*!< 50: TIM5                                    */
  SPI3_IRQHandler,              /*!< 51: SPI3                                    */
  UART4_IRQHandler,             /*!< 52: UART4                                   */
  UART5_IRQHandler,             /*!< 53: UART5                                   */
  TIM6_DAC_IRQHandler,          /*!< 54: TIM6 and DAC1&2 underrun errors         */
  TIM7_IRQHandler,              /*!< 55: TIM7                                    */
  DMA2_Stream0_IRQHandler,      /*!< 56: DMA2 Stream 0                           */
  DMA2_Stream1_IRQHandler,      /*!< 57: DMA2 Stream 1                           */
  DMA2_Stream2_IRQHandler,      /*!< 58: DMA2 Stream 2                           */
  DMA2_Stream3_IRQHandler,      /*!< 59: DMA2 Stream 3                           */
  DMA2_Stream4_IRQHandler,      /*!< 60: DMA2 Stream 4                           */
  ETH_IRQHandler,               /*!< 61: Ethernet                                */
  ETH_WKUP_IRQHandler,          /*!< 62: Ethernet Wakeup through EXTI line       */
  CAN2_TX_IRQHandler,           /*!< 63: CAN2 TX                                 */
  CAN2_RX0_IRQHandler,          /*!< 64: CAN2 RX0                                */
  CAN2_RX1_IRQHandler,          /*!< 65: CAN2 RX1                                */
  CAN2_SCE_IRQHandler,          /*!< 66: CAN2 SCE                                */
  OTG_FS_IRQHandler,            /*!< 67: USB OTG FS                              */
  DMA2_Stream5_IRQHandler,      /*!< 68: DMA2 Stream 5                           */
  DMA2_Stream6_IRQHandler,      /*!< 69: DMA2 Stream 6                           */
  DMA2_Stream7_IRQHandler,      /*!< 70: DMA2 Stream 7                           */
  USART6_IRQHandler,            /*!< 71: USART6                                  */
  I2C3_EV_IRQHandler,           /*!< 72: I2C3 event                              */
  I2C3_ER_IRQHandler,           /*!< 73: I2C3 error                              */
  OTG_HS_EP1_OUT_IRQHandler,    /*!< 74: USB OTG HS End Point 1 Out              */
  OTG_HS_EP1_IN_IRQHandler,     /*!< 75: USB OTG HS End Point 1 In               */
  OTG_HS_WKUP_IRQHandler,       /*!< 76: USB OTG HS Wakeup through EXTI          */
  OTG_HS_IRQHandler,            /*!< 77: USB OTG HS                              */
  DCMI_IRQHandler,              /*!< 78: DCMI                                    */
  CRYP_IRQHandler,              /*!< 79: CRYP crypto                             */
  HASH_RNG_IRQHandler,          /*!< 80: Hash and Rng                            */
  FPU_IRQHandler                /*!< 81: FPU                                     */
};

/**
  * @brief  This is the code that gets called when the processor first
  *         starts execution following a reset event. Only the absolutely
  *         necessary set is performed, after which the application
  *         supplied main() routine is called.
  * @param  None
  * @retval None
  */
void Reset_Handler(void)
{
	/* Инициализируем сегменты data and bss */
	unsigned int *pulSrc, *pulDest;

	/* Копируем сегмент data из FLASH в SRAM */
	pulSrc = &_sidata;

	for(pulDest = &_sdata; pulDest < &_edata; )	{
	  *(pulDest++) = *(pulSrc++);
	}
  
 	/* Заполняем нулями сегмент bss */
	for(pulDest = &_sbss; pulDest < &_ebss; )	{
	  *(pulDest++) = 0;
	}

	/* Инициализация подсистемы тактирования */
	SystemInit();

	/* Application Entry Point (Точка входа в приложение) */
	main();
  
	/* Из main() вернутся не должны, но если так, то висим в бесконечном цикле */
	while(1){};
}
/*----------------------------------------------------------------------------*/

/**
  * @brief  This is the code that gets called when the processor receives an
  *         unexpected interrupt.  This simply enters an infinite loop,
  *         preserving the system state for examination by a debugger.
  * @param  None
  * @retval None
  *
  */
void Default_Handler(void)
{
	/* Пришло незадекларированное прерывание, висим в бесконечном цикле */
	while (1){}
}
/*----------------------------------------------------------------------------*/

/*@}*/

