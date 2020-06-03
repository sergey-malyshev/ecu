/******************************************************************************
 * @file	startup_stm32f4xx.h
 * @author	Малышев Сергей  <onega.malishev@yandex.ru>
 * @version v1.0
 * @date	21/06/2019
 * @brief	Header file векторов прерываний и глобальных символов компановщика для STM32F4XX
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

/*----------Macro definition-----------------------------------------------------*/
#define WEAK __attribute__ ((weak,used,alias("Default_Handler")))

/*----------Symbols defined in linker script-------------------------------------*/
extern unsigned int _sidata;    /*!< Start address for the .data section(Flash)  */
extern unsigned int _sdata;     /*!< Start address for the .data section(RAM)    */
extern unsigned int _edata;     /*!< End address for the .data section(RAM)      */
extern unsigned int _sbss;      /*!< Start address for the .bss section(RAM)     */
extern unsigned int _ebss;      /*!< End address for the .bss section(RAM)       */
extern unsigned int _estack;	/*!< End address for the stack section           */

/*----------Function prototypes--------------------------------------------------*/
extern int main(void);           	/*!< The entry point for the application.    */
extern void SystemInit(void);    	/*!< Setup the microcontroller system(CMSIS) */
void Default_Reset_Handler(void);   /*!< Default reset handler                */
static void Default_Handler(void);  /*!< Default exception handler            	 */

/*----------Declaration of the default fault handlers----------------------------*/
/*----------Core Exceptions------------------------------------------------------*/
void Reset_Handler(void);
void WEAK NMI_Handler(void);
void WEAK HardFault_Handler(void);
void WEAK MemManage_Handler(void);
void WEAK BusFault_Handler(void);
void WEAK UsageFault_Handler(void);
void WEAK SVC_Handler(void);
void WEAK DebugMon_Handler(void);
void WEAK PendSV_Handler(void);
void WEAK SysTick_Handler(void);		
/*----------External Exceptions--------------------------------------------------*/
void WEAK  WWDG_IRQHandler(void);
void WEAK  PVD_IRQHandler(void);
void WEAK  TAMP_STAMP_IRQHandler(void);
void WEAK  RTC_WKUP_IRQHandler(void);
void WEAK  FLASH_IRQHandler(void);
void WEAK  RCC_IRQHandler(void);
void WEAK  EXTI0_IRQHandler(void);
void WEAK  EXTI1_IRQHandler(void);
void WEAK  EXTI2_IRQHandler(void);
void WEAK  EXTI3_IRQHandler(void);
void WEAK  EXTI4_IRQHandler(void);
void WEAK  DMA1_Stream0_IRQHandler(void);
void WEAK  DMA1_Stream1_IRQHandler(void);
void WEAK  DMA1_Stream2_IRQHandler(void);
void WEAK  DMA1_Stream3_IRQHandler(void);
void WEAK  DMA1_Stream4_IRQHandler(void);
void WEAK  DMA1_Stream5_IRQHandler(void);
void WEAK  DMA1_Stream6_IRQHandler(void);
void WEAK  ADC_IRQHandler(void);
void WEAK  CAN1_TX_IRQHandler(void);
void WEAK  CAN1_RX0_IRQHandler(void);
void WEAK  CAN1_RX1_IRQHandler(void);
void WEAK  CAN1_SCE_IRQHandler(void);
void WEAK  EXTI9_5_IRQHandler(void);
void WEAK  TIM1_BRK_TIM9_IRQHandler(void);
void WEAK  TIM1_UP_TIM10_IRQHandler(void);
void WEAK  TIM1_TRG_COM_TIM11_IRQHandler(void);
void WEAK  TIM1_CC_IRQHandler(void);
void WEAK  TIM2_IRQHandler(void);
void WEAK  TIM3_IRQHandler(void);
void WEAK  TIM4_IRQHandler(void);
void WEAK  I2C1_EV_IRQHandler(void);
void WEAK  I2C1_ER_IRQHandler(void);
void WEAK  I2C2_EV_IRQHandler(void);
void WEAK  I2C2_ER_IRQHandler(void);
void WEAK  SPI1_IRQHandler(void);
void WEAK  SPI2_IRQHandler(void);
void WEAK  USART1_IRQHandler(void);
void WEAK  USART2_IRQHandler(void);
void WEAK  USART3_IRQHandler(void);
void WEAK  EXTI15_10_IRQHandler(void);
void WEAK  RTC_Alarm_IRQHandler(void);
void WEAK  OTG_FS_WKUP_IRQHandler(void);
void WEAK  TIM8_BRK_TIM12_IRQHandler(void);
void WEAK  TIM8_UP_TIM13_IRQHandler(void);
void WEAK  TIM8_TRG_COM_TIM14_IRQHandler(void);
void WEAK  TIM8_CC_IRQHandler(void);
void WEAK  DMA1_Stream7_IRQHandler(void);
void WEAK  FSMC_IRQHandler(void);
void WEAK  SDIO_IRQHandler(void);
void WEAK  TIM5_IRQHandler(void);
void WEAK  SPI3_IRQHandler(void);
void WEAK  UART4_IRQHandler(void);
void WEAK  UART5_IRQHandler(void);
void WEAK  TIM6_DAC_IRQHandler(void);
void WEAK  TIM7_IRQHandler(void);
void WEAK  DMA2_Stream0_IRQHandler(void);
void WEAK  DMA2_Stream1_IRQHandler(void);
void WEAK  DMA2_Stream2_IRQHandler(void);
void WEAK  DMA2_Stream3_IRQHandler(void);
void WEAK  DMA2_Stream4_IRQHandler(void);
void WEAK  ETH_IRQHandler(void);
void WEAK  ETH_WKUP_IRQHandler(void);
void WEAK  CAN2_TX_IRQHandler(void);
void WEAK  CAN2_RX0_IRQHandler(void);
void WEAK  CAN2_RX1_IRQHandler(void);
void WEAK  CAN2_SCE_IRQHandler(void);
void WEAK  OTG_FS_IRQHandler(void);
void WEAK  DMA2_Stream5_IRQHandler(void);
void WEAK  DMA2_Stream6_IRQHandler(void);
void WEAK  DMA2_Stream7_IRQHandler(void);
void WEAK  USART6_IRQHandler(void);
void WEAK  I2C3_EV_IRQHandler(void);
void WEAK  I2C3_ER_IRQHandler(void);
void WEAK  OTG_HS_EP1_OUT_IRQHandler(void);
void WEAK  OTG_HS_EP1_IN_IRQHandler(void);
void WEAK  OTG_HS_WKUP_IRQHandler(void);
void WEAK  OTG_HS_IRQHandler(void);
void WEAK  DCMI_IRQHandler(void);
void WEAK  CRYP_IRQHandler(void);
void WEAK  HASH_RNG_IRQHandler(void);
void WEAK  FPU_IRQHandler(void);

/* Структура указателей на функции обработчиков прерываний */
typedef struct {
/*----------Core Exceptions-----------------------------------------------------*/
	void (*_estack)(void);	
	void (*Reset_Handler)(void);
	void (*NMI_Handler)(void);
	void (*HardFault_Handler)(void);
	void (*MemManage_Handler)(void);
	void (*BusFault_Handler)(void);
	void (*UsageFault_Handler)(void);
	void (*Reserved1)(void);
	void (*Reserved2)(void);
	void (*Reserved3)(void);
	void (*Reserved4)(void);
	void (*SVC_Handler)(void);
	void (*DebugMon_Handler)(void);
	void (*Reserved5)(void);
	void (*PendSV_Handler)(void);
	void (*SysTick_Handler)(void);
/*----------External Exceptions-----------------------------------------------*/
	void (*WWDG_IRQHandler)(void);
	void (*PVD_IRQHandler)(void);
	void (*TAMP_STAMP_IRQHandler)(void);
	void (*RTC_WKUP_IRQHandler)(void);
	void (*FLASH_IRQHandler)(void);
	void (*RCC_IRQHandler)(void);
	void (*EXTI0_IRQHandler)(void);
	void (*EXTI1_IRQHandler)(void);
	void (*EXTI2_IRQHandler)(void);
	void (*EXTI3_IRQHandler)(void);
	void (*EXTI4_IRQHandler)(void);
	void (*DMA1_Stream0_IRQHandler)(void);
	void (*DMA1_Stream1_IRQHandler)(void);
	void (*DMA1_Stream2_IRQHandler)(void);
	void (*DMA1_Stream3_IRQHandler)(void);
	void (*DMA1_Stream4_IRQHandler)(void);
	void (*DMA1_Stream5_IRQHandler)(void);
	void (*DMA1_Stream6_IRQHandler)(void);
	void (*ADC_IRQHandler)(void);
	void (*CAN1_TX_IRQHandler)(void);
	void (*CAN1_RX0_IRQHandler)(void);
	void (*CAN1_RX1_IRQHandler)(void);
	void (*CAN1_SCE_IRQHandler)(void);
	void (*EXTI9_5_IRQHandler)(void);
	void (*TIM1_BRK_TIM9_IRQHandler)(void);
	void (*TIM1_UP_TIM10_IRQHandler)(void);
	void (*TIM1_TRG_COM_TIM11_IRQHandler)(void);
	void (*TIM1_CC_IRQHandler)(void);
	void (*TIM2_IRQHandler)(void);
	void (*TIM3_IRQHandler)(void);
	void (*TIM4_IRQHandler)(void);
	void (*I2C1_EV_IRQHandler)(void);
	void (*I2C1_ER_IRQHandler)(void);
	void (*I2C2_EV_IRQHandler)(void);
	void (*I2C2_ER_IRQHandler)(void);
	void (*SPI1_IRQHandler)(void);
	void (*SPI2_IRQHandler)(void);
	void (*USART1_IRQHandler)(void);
	void (*USART2_IRQHandler)(void);
	void (*USART3_IRQHandler)(void);
	void (*EXTI15_10_IRQHandler)(void);
	void (*RTC_Alarm_IRQHandler)(void);
	void (*OTG_FS_WKUP_IRQHandler)(void);
	void (*TIM8_BRK_TIM12_IRQHandler)(void);
	void (*TIM8_UP_TIM13_IRQHandler)(void);
	void (*TIM8_TRG_COM_TIM14_IRQHandler)(void);
	void (*TIM8_CC_IRQHandler)(void);
	void (*DMA1_Stream7_IRQHandler)(void);
	void (*FSMC_IRQHandler)(void);
	void (*SDIO_IRQHandler)(void);
	void (*TIM5_IRQHandler)(void);
	void (*SPI3_IRQHandler)(void);
	void (*UART4_IRQHandler)(void);
	void (*UART5_IRQHandler)(void);
	void (*TIM6_DAC_IRQHandler)(void);
	void (*TIM7_IRQHandler)(void);
	void (*DMA2_Stream0_IRQHandler)(void);
	void (*DMA2_Stream1_IRQHandler)(void);
	void (*DMA2_Stream2_IRQHandler)(void);
	void (*DMA2_Stream3_IRQHandler)(void);
	void (*DMA2_Stream4_IRQHandler)(void);
	void (*ETH_IRQHandler)(void);
	void (*ETH_WKUP_IRQHandler)(void);
	void (*CAN2_TX_IRQHandler)(void);
	void (*CAN2_RX0_IRQHandler)(void);
	void (*CAN2_RX1_IRQHandler)(void);
	void (*CAN2_SCE_IRQHandler)(void);
	void (*OTG_FS_IRQHandler)(void);
	void (*DMA2_Stream5_IRQHandler)(void);
	void (*DMA2_Stream6_IRQHandler)(void);
	void (*DMA2_Stream7_IRQHandler)(void);
	void (*USART6_IRQHandler)(void);
	void (*I2C3_EV_IRQHandler)(void);
	void (*I2C3_ER_IRQHandler)(void);
	void (*OTG_HS_EP1_OUT_IRQHandler)(void);
	void (*OTG_HS_EP1_IN_IRQHandler)(void);
	void (*OTG_HS_WKUP_IRQHandler)(void);
	void (*OTG_HS_IRQHandler)(void);
	void (*DCMI_IRQHandler)(void);
	void (*CRYP_IRQHandler)(void);
	void (*HASH_RNG_IRQHandler)(void);
	void (*FPU_IRQHandler)(void);
} ISRVectorsTables;

/*@}*/
