/***
* led3.c - ������ ���������� ����������
* ������: 1.0
* ������: 01.03.18
***/

#include "led3.h"
#include "FreeRTOS.h"
#include "task.h"
/****************************************************************/
// ���������� ����������
/****************************************************************/

/****************************************************************/
// ������������� 
/****************************************************************/
void Led3Init (void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	// �������� ������������ ����� D
    
	GPIO_InitTypeDef led;
 	led.GPIO_Mode = GPIO_Mode_OUT;  			// ����������� - �����
	led.GPIO_OType = GPIO_OType_PP;  			// ����������� �����
	led.GPIO_PuPd = GPIO_PuPd_NOPULL;  			// ��� ��������
	led.GPIO_Speed = GPIO_Speed_100MHz;  		// �������� �������
	led.GPIO_Pin = GPIO_Pin_14;				 	// ��� PD14
	GPIO_Init(GPIOD, &led); 
}

/* ���������� led3 */
void vTaskLED3(void *pvParameters) 
{
	/* ������������� �������� ������*/
	Led3Init();
	int a = 1;
	int b = 2;
	/* ����������� ���� ������ */
	for (;;) 
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
        vTaskDelay(pdMS_TO_TICKS(250));
        GPIO_ResetBits(GPIOD, GPIO_Pin_14);
        vTaskDelay(pdMS_TO_TICKS(250));
    }
}
