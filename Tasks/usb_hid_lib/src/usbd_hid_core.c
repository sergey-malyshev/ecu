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

uint8_t OutBuffer[64];   	//����� �������� ������ (������������ ��)

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


/**********************  ���������� ������������  ********************/
 static uint8_t USBD_HID_CfgDesc[USB_HID_CONFIG_DESC_SIZ] =
{
  0x09, // bLength: ������ ����������� ������������ � ������
  0x02, // bDescriptorType: ��� �����������: ���������� ������������
  0x29, // wTotalLength: ������ ����� �����������: ������������ + ��������� + �������� �����
  0x00, //
  0x01, // bNumInterfaces: ���������� ����������� = 1 (����� 1 ��������� ��������������)
  0x01, // bConfigurationValue: ����� ������������ = 1 (����� 1 ������������ ��������������)
  0x00, // iConfiguration: ������ ����������� ������, ����������� ������������
  0xE0, // bmAttributes: bus powered and Support Remote Wake-up */
  0x32, // MaxPower 100 mA: ������ ����������� ���������� �� ���� = 100 ��*/

  /********************  ���������� ����������  **********************/
  0x09, // bLength: ������ ����������� ���������� � ������
  0x04,	// bDescriptorType: ��� �����������: ���������� ����������
  0x00, // bInterfaceNumber: ����� ���������� = 0
  0x00, // bAlternateSetting: �������������� ��������� ��� ���������� (�����������)
  0x02, // bNumEndpoints: ���������� �������� �����, ������������ ����������� = 2
  0x03, // bInterfaceClass: ����� ���������� - HID
  0x00, // bInterfaceSubClass: �������� ���������� - 0 (no boot)
  0x00, // nInterfaceProtocol: �������� ���������� - 0 (none)
  0x00, // iInterface: ������ ����������� ������ �������� ����������

  /********************  ���������� HID ********************/
  0x09, // bLength: ������ ������������ HID � ������
  0x21, // bDescriptorType: ��� ����������� - HID
  0x00, // bcdHID: ������ HID - 02.00
  0x02,	//
  0x00, // bCountryCode: �������� ��� ������ - 0
  0x01, // bNumDescriptors: ����� ������������ ������� - 1
  0x22, // bDescriptorType: ����� ����������� �������, ������������ ��� ������ Set_Descriptor
  0x26, // wItemLength: ������ ����������� �������
  0x00,	//

  /******************** ���������� �������� ����� IN ********************/
  0x07, 		  // bLength: ������ ����������� � ������
  0x05, 		  // bDescriptorType: ��� ����������� - ���������� �������� �����
  HID_IN_EP, 	  // bEndpointAddress: ����� �������� ����� ���� IN (0x01)
  0x03,      	  // bmAttributes: ��� �������� - Interrupt
  HID_IN_PACKET,  // wMaxPacketSize: ������������ ������ ������ � ������ (64 �����)
  0x00,			  //
  0x01,           // bInterval: �������� ������ �������� ����� (10 ms)

  /******************** ���������� �������� ����� OUT ********************/
  0x07, 		  // bLength: ������ ����������� � ������
  0x05, 		  // bDescriptorType: ��� ����������� - ���������� �������� �����
  HID_OUT_EP, 	  // bEndpointAddress: ����� �������� ����� ���� OUT (0x81)
  0x03,       	  // bmAttributes: ��� �������� - Interrupt
  HID_OUT_PACKET, // wMaxPacketSize: ������������ ������ ������ � ������ (64 �����)
  0x00,			  //
  0x01,           // bInterval: �������� ������ �������� ����� (10 ms)
} ;


/**********************  ���������� ������� HID   ********************/
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

	/* ������ ����� ��������� ������ � ������ */
	USB_Rx_Cnt = ((USB_OTG_CORE_HANDLE*)pdev)->dev.out_ep[epnum].xfer_count;
	if(USB_Rx_Cnt != 0)			//���� USB_Rx_Cnt != 0, �� �������� ������
	{
		int8_t i=0;
		while (i<USB_Rx_Cnt)
		{
	  		OutBuffer[i]=usb_rx_buffer[i];
			i++;
		}
		/* ���������� �������� ����� OUT ��� ������ ���������� ������ ������ */
		DCD_EP_PrepareRx(pdev, HID_OUT_EP, usb_rx_buffer, HID_OUT_PACKET);

	}
	return USBD_OK;
}

