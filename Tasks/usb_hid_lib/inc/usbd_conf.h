/**
  ******************************************************************************
  * @file    usbd_conf.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   USB Device configuration file
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CONF__H__
#define __USBD_CONF__H__

/* Includes ------------------------------------------------------------------*/

#define USBD_CFG_MAX_NUM           1	//Максимальное количество конфигураций
#define USBD_ITF_MAX_NUM           1	//Максимальное количество интерфейсов
#define USB_MAX_STR_DESC_SIZ       63	//Максимальнный размер дескриптора строки

#define USBD_DYNAMIC_DESCRIPTOR_CHANGE_ENABLED 

#define HID_IN_EP                    0x81	//Адрес конечной точки IN
#define HID_OUT_EP                   0x01	//Адрес конечной точки OUT

#define HID_IN_PACKET                63		//
#define HID_OUT_PACKET               63		//


#endif //__USBD_CONF__H__


