/***
* led2.c - ������ ���������� ����������
* ������: 1.0
* ������: 01.03.18
***/

#include "led2.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stm32f4xx_usart.h>
#include "stm32f4xx_tim.h"
/****************************************************************/
// ���������� ����������
/****************************************************************/

/****************************************************************/
// ������������� 
/****************************************************************/
void Led2Init (void)
{
	/*Установка яркости подсветки в 25% от максимума */
	CCR_Val=0;
	IllumStep = 1;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	// �������� ������������ ����� D
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	// тактирование таймера Т4

//	GPIO_InitTypeDef led;
// 	led.GPIO_Mode = GPIO_Mode_OUT;  			// ����������� - �����
//	led.GPIO_OType = GPIO_OType_PP;  			// ����������� �����
//	led.GPIO_PuPd = GPIO_PuPd_NOPULL;  			// ��� ��������
//	led.GPIO_Speed = GPIO_Speed_100MHz;  		// �������� �������
//	led.GPIO_Pin = GPIO_Pin_13;				 	// ��� PD12
//	GPIO_Init(GPIOD, &led);

	/* Порт D: TIM4 CH4 (PD15) - управление подсветкой клавиатуры*/
	led.GPIO_Mode = GPIO_Mode_AF;
	led.GPIO_OType = GPIO_OType_PP;
	led.GPIO_PuPd = GPIO_PuPd_UP ;
	led.GPIO_Speed = GPIO_Speed_100MHz;
	led.GPIO_Pin = GPIO_Pin_13 ;
	GPIO_Init(GPIOD, &led);

	/* Назначение пинов Т4 на AF2 */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);

	/* Расчет прескаляра */
	PrescalerValue = (uint16_t) (42-1);

	/* Установка периода таймера (Т = 1 мс) */
	Period = 20000;

	/* Настройка таймера Т4 */
	TIM_TimeBaseStructInit(&led_timer);
	led_timer.TIM_Period = Period;
	led_timer.TIM_Prescaler = PrescalerValue;
	led_timer.TIM_ClockDivision = 0;
	led_timer.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &led_timer);

	/* Конфигурация канала №4 ШИМ Т4 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR_Val;
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	/* Разрешаем буферизацию регистра перезагрузки */
  	TIM_ARRPreloadConfig(TIM4, ENABLE);

  	/* Запуск таймера Т4 */
  	TIM_Cmd(TIM4, ENABLE);
}

/* ���������� led2 */
void vTaskLED2(void *pvParameters) 
{
	/* ������������� �������� ������*/
	Led2Init();
	KLineInit();
	/* ����������� ���� ������ */
	for (;;) 
	{
//		GPIO_SetBits(GPIOD, GPIO_Pin_13);
//        vTaskDelay(pdMS_TO_TICKS(500));
//        GPIO_ResetBits(GPIOD, GPIO_Pin_13);
//        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

/****************************************************************/
//				 Управление яркостью подсветки (в процентах)
/****************************************************************/
void IllumSet (uint16_t Value)
{
	CCR_Val = Value;
	Value = (Period * Value)/100;
	TIM_SetCompare2(TIM4,(uint32_t)Value);
}


/****************************************************************
***                 Глобальные переменные
****************************************************************/
// Структура настройки пинов порта под USART
GPIO_InitTypeDef TxRxPin;

// Структура настройки USART
USART_InitTypeDef usart;

// Счетчик отправленных байт
uint8_t sendDataCounter = 0;

// Принятый байт данных
uint16_t InDataByte = 0;

// Указатель на буфер данных
uint8_t *dataPtr = 0;

// Общее число байт к передаче
uint8_t dataLength = 0;

/****************************************************************/
//Инициализация канала связи K-Line
/****************************************************************/
void KLineInit (void)
{
    //Установка скорости USART по умолчанию (19200 бит/с)
    int BaudRate = 19200;

    // Сброс Флага успешной передачи пакета
    int TxComplite = 0;

    // Запускаем тактирование
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    // Инициализация пинов контроллера, для USART1 – PA9 (TX) и PA10 (RX)
    GPIO_StructInit(&TxRxPin);

	// PD5 (TX)
    TxRxPin.GPIO_Mode = GPIO_Mode_AF;
    TxRxPin.GPIO_Pin = GPIO_Pin_5;
    TxRxPin.GPIO_Speed = GPIO_Speed_50MHz;
    TxRxPin.GPIO_OType = GPIO_OType_PP;
    TxRxPin.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &TxRxPin);

	// PD6 (RX)
    TxRxPin.GPIO_Mode = GPIO_Mode_AF;
    TxRxPin.GPIO_Pin = GPIO_Pin_6;
    TxRxPin.GPIO_Speed = GPIO_Speed_50MHz;
    TxRxPin.GPIO_OType = GPIO_OType_PP;
    TxRxPin.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &TxRxPin);

    // Включение альтернативных функций для пинов USART
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

    // Настраиваем USART
    USART_StructInit(&usart);
    usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart.USART_BaudRate = BaudRate;
    USART_Init(USART2, &usart);

    // Включаем прерывания и запускаем USART
    NVIC_EnableIRQ(USART2_IRQn);
    USART_Cmd(USART2, ENABLE);

	// Разрешаем прерывания по приему байта
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	// Разрешаем прерывания по завершению передачи буфера
	USART_ITConfig(USART2, USART_IT_TC, ENABLE);
}


/****************************************************************/
// Обработчик прерывания USART
/****************************************************************/
void USART2_IRQHandler()
{
	// Передан байт
    if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
    {
        // Отправляем очередной байт данных
        USART_SendData(USART2, *dataPtr);

        // Инкремент счетчика отправленных байт
        sendDataCounter++;

		// Инкремент адреса указателя очередного байта
		dataPtr++;

        // Если отправили все данные, то ждем окончания передачи последнего байта
        if  (sendDataCounter == dataLength)
        {
            // Запрещаем прерывание прерывание по окончанию передачи байта
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
        }
    }

	// Передача полностью завершена
    if (USART_GetITStatus(USART2, USART_IT_TC) != RESET)
    {
        // Очищаем флаг прерывания
        USART_ClearITPendingBit(USART2, USART_IT_TC);

    }

	// Принят байт
    if (USART_GetITStatus (USART2, USART_IT_RXNE) != RESET)
    {
        // Очищаем флаг прерывания
        USART_ClearITPendingBit (USART1, USART_IT_RXNE);

		// Читаем принятый байт данных
        InDataByte = ReceiveByte ();
        IllumSet (InDataByte);
	}
}


/****************************************************************/
// Передача одного байта
/****************************************************************/
void SendByte (uint16_t byte)
{
	USART_SendData(USART2, byte);
}

/****************************************************************/
// Прием одного байта
/****************************************************************/
uint16_t ReceiveByte (void)
{
	return USART_ReceiveData(USART2);
}

/****************************************************************/
// Передача буфера данных (пакета)
/****************************************************************/
void SendPacket (uint8_t *Ptr, uint8_t length)
{
	// Сброс счетика отправленных байт
	sendDataCounter = 0;

	// Число байт к передаче из буфера
	dataLength = length;

	// Указатель на буфер передачи
	dataPtr = Ptr;

	// Разрешаем прерывание по окончанию передачи байта
    USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
}


/****************************************************************/
// Передача link байта - 0x55 (проверка исправности соединения)
/****************************************************************/
void LinkSend (void)
{
	SendByte (0x55);
}



