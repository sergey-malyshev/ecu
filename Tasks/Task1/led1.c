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

#include "led1.h"
#include "FreeRTOS.h"
#include "task.h"
#include "usbd_hid_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"

extern  uint8_t OutBuffer[64];
USB_OTG_CORE_HANDLE  USB_OTG_dev;
extern USB_OTG_CORE_HANDLE  USB_OTG_dev;
/****************************************************************/
// ���������� ����������
/****************************************************************/

/****************************************************************/
// �������������
/****************************************************************/
void Led1Init (void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	// �������� ������������ ����� D
    
	GPIO_InitTypeDef led;
 	led.GPIO_Mode = GPIO_Mode_OUT;  			// ����������� - �����
	led.GPIO_OType = GPIO_OType_PP;  			// ����������� �����
	led.GPIO_PuPd = GPIO_PuPd_NOPULL;  			// ��� ��������
	led.GPIO_Speed = GPIO_Speed_100MHz;  		// �������� �������
	led.GPIO_Pin = GPIO_Pin_12;				 	// ���� PD12-PD13
	GPIO_Init(GPIOD, &led); 
}

/* ���������� led1 */
void vTaskLED1(void *pvParameters) 
{
	/* ������������� �������� ������*/
	Led1Init();
//	USBD_Init(&USB_OTG_dev,  USB_OTG_FS_CORE_ID,  &USR_desc,  &USBD_HID_cb,  &USR_cb);
	/* ����������� ���� ������ */
	for (;;) 
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
      vTaskDelay(pdMS_TO_TICKS(500));
        GPIO_ResetBits(GPIOD, GPIO_Pin_12);
        vTaskDelay(pdMS_TO_TICKS(500));
/*		if(OutBuffer[0] == 'S')
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
		}
			        USBD_HID_SendReport (&USB_OTG_dev, OutBuffer, 4);
		if(OutBuffer[0] == 'R')
		{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		}
		if(OutBuffer[0] == 'O')
		{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
		}
		if(OutBuffer[0] == 'G')
		{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
		}
		if(OutBuffer[0] == 'B')
		{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
		}
		OutBuffer[0] = 0;*/
    }
}


