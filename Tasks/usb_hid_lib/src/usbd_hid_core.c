/**
  ******************************************************************************
  * @file    usbd_hid_core.c
  * @author  MCD Application Team
  *
  *
  */

/* Includes ------------------------------------------------------------------*/
#include "usbd_hid_core.h"
#include "usbd_desc.h"
#include "usbd_req.h"

// The hid core from ST is not flexible
#ifdef HID_MOUSE_REPORT_DESC_SIZE
#undef HID_MOUSE_REPORT_DESC_SIZE
#endif
#define HID_MOUSE_REPORT_DESC_SIZE 79 //23

#ifdef USB_HID_CONFIG_DESC_SIZ
#undef USB_HID_CONFIG_DESC_SIZ
#endif
#define USB_HID_CONFIG_DESC_SIZ 41

uint8_t OutBuffer[64];   	//буфер выходных данных (относительно РС)

static uint8_t  USBD_HID_Init (void  *pdev, uint8_t cfgidx);

static uint8_t  USBD_HID_DeInit (void  *pdev, uint8_t cfgidx);

static uint8_t  USBD_HID_Setup (void  *pdev, USB_SETUP_REQ *req);

static uint8_t  *USBD_HID_GetCfgDesc (uint8_t speed, uint16_t *length);

static uint8_t  USBD_HID_DataIn (void  *pdev, uint8_t epnum);

static uint8_t  USBD_HID_DataOut (void  *pdev, uint8_t epnum);

USBD_Class_cb_TypeDef  USBD_HID_cb = 
{
  USBD_HID_Init,
  USBD_HID_DeInit,
  USBD_HID_Setup,
  NULL, /*EP0_TxSent*/  
  NULL, /*EP0_RxReady*/
  USBD_HID_DataIn, /*DataIn*/
  USBD_HID_DataOut, /*DataOut*/
  NULL, /*SOF */
  NULL,
  NULL,      
  USBD_HID_GetCfgDesc,
};

static uint32_t  USBD_HID_AltSet = 0;

static uint32_t  USBD_HID_Protocol = 0;

static uint32_t  USBD_HID_IdleState = 0;


/**********************  Дескриптор конфигурации  ********************/
 static uint8_t USBD_HID_CfgDesc[USB_HID_CONFIG_DESC_SIZ] =
{
  0x09, // bLength: Размер дескриптора конфигурации в байтах
  0x02, // bDescriptorType: Тип дескриптора: дескриптор конфигурации
  0x29, // wTotalLength: Полная длина дескриптора: конфигурация + интерфейс + конечные точки
  0x00, //
  0x01, // bNumInterfaces: Количество интерфейсов = 1 (всего 1 интерфейс поддерживается)
  0x01, // bConfigurationValue: Номер конфигурации = 1 (всего 1 конфигурация поддерживается)
  0x00, // iConfiguration: Индекс дескриптора строки, описывающей конфигурацию
  0xE0, // bmAttributes: bus powered and Support Remote Wake-up */
  0x32, // MaxPower 100 mA: полное потребление устройства от шины = 100 мА*/

  /********************  Дескриптор интерфейса  **********************/
  0x09, // bLength: Размер дескриптора интерфейса в байтах
  0x04,	// bDescriptorType: Тип дескриптора: дескриптор интерфейса
  0x00, // bInterfaceNumber: Номер интерфейса = 0
  0x00, // bAlternateSetting: Альтернативные установки для интерфейса (отсутствуют)
  0x02, // bNumEndpoints: Количество конечных точек, используемых интерфейсом = 2
  0x03, // bInterfaceClass: Класс интерфейса - HID
  0x00, // bInterfaceSubClass: Подкласс интерфейса - 0 (no boot)
  0x00, // nInterfaceProtocol: Протокол интерфейса - 0 (none)
  0x00, // iInterface: Индекс дескриптора строки описания интерфейса

  /********************  Дескриптор HID ********************/
  0x09, // bLength: Размер дерскриптора HID в байтах
  0x21, // bDescriptorType: Тип дескриптора - HID
  0x00, // bcdHID: Версия HID - 02.00
  0x02,	//
  0x00, // bCountryCode: Числовой код страны - 0
  0x01, // bNumDescriptors: Число дескрипторов репорта - 1
  0x22, // bDescriptorType: Номер дескриптора репорта, используемый при вызове Set_Descriptor
  0x26, // wItemLength: Размер дескриптора репорта
  0x00,	//

  /******************** Дескриптор конечной точки IN ********************/
  0x07, 		  // bLength: Размер дескриптора в байтах
  0x05, 		  // bDescriptorType: Тип дескриптора - дескриптор конечной точки
  HID_IN_EP, 	  // bEndpointAddress: Адрес конечной точки типа IN (0x01)
  0x03,      	  // bmAttributes: Тип передачи - Interrupt
  HID_IN_PACKET,  // wMaxPacketSize: Максимальный размер пакета в байтах (64 байта)
  0x00,			  //
  0x01,           // bInterval: Интервал опроса конечной точки (10 ms)

  /******************** Дескриптор конечной точки OUT ********************/
  0x07, 		  // bLength: Размер дескриптора в байтах
  0x05, 		  // bDescriptorType: Тип дескриптора - дескриптор конечной точки
  HID_OUT_EP, 	  // bEndpointAddress: Адрес конечной точки типа OUT (0x81)
  0x03,       	  // bmAttributes: Тип передачи - Interrupt
  HID_OUT_PACKET, // wMaxPacketSize: Максимальный размер пакета в байтах (64 байта)
  0x00,			  //
  0x01,           // bInterval: Интервал опроса конечной точки (10 ms)
} ;


/**********************  Дескриптор репорта HID   ********************/
static uint8_t HID_MOUSE_ReportDesc[HID_MOUSE_REPORT_DESC_SIZE] =
{
		/* USER CODE BEGIN 0 */
		    0x06, 0x00, 0xff,              // 	USAGE_PAGE (Generic Desktop)
		    0x09, 0x01,                    // 	USAGE (Vendor Usage 1)
		    // System Parameters
		    0xa1, 0x01,                    // 	COLLECTION (Application)
		    0x85, 0x01,                    //   REPORT_ID (1)
		    0x09, 0x01,                    //   USAGE (Vendor Usage 1)
		    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
		    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
		    0x75, 0x08,                    //   REPORT_SIZE (8)
		    0x95, 4, 	                   //   REPORT_COUNT (4)
		    0xb1, 0x82,                    //   FEATURE (Data,Var,Abs,Vol)
		    0x85, 0x01,                    //   REPORT_ID (1)
		    0x09, 0x01,                    //   USAGE (Vendor Usage 1)
		    0x91, 0x82,                    //   OUTPUT (Data,Var,Abs,Vol)

		    0x85, 0x02,                    //   REPORT_ID (4)
		    0x09, 0x02,                    //   USAGE (Vendor Usage 4)
		    0x75, 0x08,                    //   REPORT_SIZE (8)
		    0x95, 4, 	                   //   REPORT_COUNT (4)
		    0x81, 0x82,                    //   INPUT (Data,Var,Abs,Vol)
		  /* USER CODE END 0 */
		  0xC0    /*     END_COLLECTION	             */
};


/**
  * @brief  USBD_HID_Init Initialize the HID interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */

static uint8_t usb_rx_buffer[HID_OUT_PACKET];

static uint8_t  USBD_HID_Init (void  *pdev, uint8_t cfgidx)
{
  /* Open EP IN */
  DCD_EP_Open(pdev, HID_IN_EP, HID_IN_PACKET, USB_OTG_EP_INT);
  
  /* Open EP OUT */
  DCD_EP_Open(pdev, HID_OUT_EP, HID_OUT_PACKET, USB_OTG_EP_INT);
  DCD_EP_PrepareRx(pdev, HID_OUT_EP, usb_rx_buffer, HID_OUT_PACKET);
  
  return USBD_OK;
}

/**
  * @brief  USBD_HID_Init DeInitialize the HID layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_DeInit (void  *pdev, uint8_t cfgidx)
{
  /* Close HID EPs */
  DCD_EP_Close (pdev, HID_IN_EP);
  DCD_EP_Close (pdev, HID_OUT_EP);

  return USBD_OK;
}

/**
  * @brief  USBD_HID_Setup Handle the HID specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t  USBD_HID_Setup (void  *pdev, USB_SETUP_REQ *req)
{
  uint16_t len = 0;
  uint8_t  *pbuf = NULL;
  
  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
  case USB_REQ_TYPE_CLASS :  
    switch (req->bRequest)
    {
      
      
    case HID_REQ_SET_PROTOCOL:
      USBD_HID_Protocol = (uint8_t)(req->wValue);
      break;
      
    case HID_REQ_GET_PROTOCOL:
      USBD_CtlSendData (pdev, 
                        (uint8_t *)&USBD_HID_Protocol,
                        1);    
      break;
      
    case HID_REQ_SET_IDLE:
      USBD_HID_IdleState = (uint8_t)(req->wValue >> 8);
      break;
      
    case HID_REQ_GET_IDLE:
      USBD_CtlSendData (pdev, 
                        (uint8_t *)&USBD_HID_IdleState,
                        1);        
      break;

    default:
      USBD_CtlError (pdev, req);
      return USBD_FAIL; 
    }
    break;
    
  case USB_REQ_TYPE_STANDARD:
    switch (req->bRequest)
    {
    case USB_REQ_GET_DESCRIPTOR: 
      if( req->wValue >> 8 == HID_REPORT_DESC)
      {
        len = MIN(HID_MOUSE_REPORT_DESC_SIZE , req->wLength);
        pbuf = HID_MOUSE_ReportDesc;
      }
      else if( req->wValue >> 8 == HID_DESCRIPTOR_TYPE)
      {
        
#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
        pbuf = USBD_HID_Desc;
#else
        pbuf = USBD_HID_CfgDesc + 0x12;
#endif
        len = MIN(USB_HID_DESC_SIZ , req->wLength);
      }
      
      USBD_CtlSendData (pdev, 
                        pbuf,
                        len);
      
      break;
      
    case USB_REQ_GET_INTERFACE :
      USBD_CtlSendData (pdev,
                        (uint8_t *)&USBD_HID_AltSet,
                        1);
      break;
      
    case USB_REQ_SET_INTERFACE :
      USBD_HID_AltSet = (uint8_t)(req->wValue);
      break;
    }
  }
  return USBD_OK;
}

/**
  * @brief  USBD_HID_SendReport Send HID Report
  * @param  pdev: device instance
  * @param  buff: pointer to report
  * @retval status
  */
uint8_t USBD_HID_SendReport (USB_OTG_CORE_HANDLE  *pdev, uint8_t *report, uint16_t len)
{
  if (pdev->dev.device_status == USB_OTG_CONFIGURED )
  {
    DCD_EP_Tx (pdev, HID_IN_EP, report, len);
  }
  return USBD_OK;
}

/**
  * @brief  USBD_HID_GetCfgDesc return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_HID_GetCfgDesc (uint8_t speed, uint16_t *length)
{
  *length = sizeof (USBD_HID_CfgDesc);
  return USBD_HID_CfgDesc;
}

/**
  * @brief  USBD_HID_DataIn handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_HID_DataIn (void  *pdev, uint8_t epnum)
{

  /* Ensure that the FIFO is empty before a new transfer, this condition could 
  be caused by  a new transfer before the end of the previous transfer */
  DCD_EP_Flush(pdev, HID_IN_EP);
  return USBD_OK;
}

/**
  * @brief  USBD_HID_DataOut handle data OUT Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_HID_DataOut (void  *pdev, uint8_t epnum)
{
    /* Ensure that the FIFO is empty before a new transfer, this condition could
    be caused by  a new transfer before the end of the previous transfer */
    uint16_t USB_Rx_Cnt;

    if ( epnum != (HID_OUT_EP & 0x0F) )
	    return USBD_FAIL;

	/* Читаем длину принятого пакета в байтах */
	USB_Rx_Cnt = ((USB_OTG_CORE_HANDLE*)pdev)->dev.out_ep[epnum].xfer_count;
	if(USB_Rx_Cnt != 0)			//если USB_Rx_Cnt != 0, то копируем данные
	{
		int8_t i=0;
		while (i<USB_Rx_Cnt)
		{
	  		OutBuffer[i]=usb_rx_buffer[i];
			i++;
		}
		/* Подготовка конечной точки OUT для приема следующего пакета данных */
		DCD_EP_PrepareRx(pdev, HID_OUT_EP, usb_rx_buffer, HID_OUT_PACKET);

	}
	return USBD_OK;
}

