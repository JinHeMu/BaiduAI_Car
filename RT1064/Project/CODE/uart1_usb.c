#include "uart1_usb.h"


UsbStruct usbStr;

uint8 USB_uart_rx_buffer;
lpuart_transfer_t USB_receivexfer;
lpuart_handle_t USB_g_lpuartHandle;

/**
* @brief        USB接受回调函数
* @param              
**/
void USB_UART_Callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    uint8_t Uart1Res;
    if (kStatus_LPUART_RxIdle == status)
    {
        Uart1Res = USB_uart_rx_buffer; 
        if(Uart1Res == USB_FRAME_HEAD && !usbStr.receiveStart)//监测帧头,并且没有开始
        {
            usbStr.receiveStart = true;//开始接收
            usbStr.receiveBuff[0] = Uart1Res;//储存帧头
            usbStr.receiveBuff[2] = USB_FRAME_LENMIN;//储存帧长
            usbStr.receiveIndex = 1;//接收序列为1
        }
        else if(usbStr.receiveIndex == 2)	//接收帧长度
        {
            usbStr.receiveBuff[usbStr.receiveIndex] = Uart1Res;
            usbStr.receiveIndex++;
            
            if(Uart1Res > USB_FRAME_LENMAX || Uart1Res < USB_FRAME_LENMIN) //帧长错误
            {
                usbStr.receiveBuff[2] = USB_FRAME_LENMIN;
                usbStr.receiveIndex = 0;
                usbStr.receiveStart = false;
            }
        }
        else if(usbStr.receiveStart && usbStr.receiveIndex < USB_FRAME_LENMAX)
        {
            usbStr.receiveBuff[usbStr.receiveIndex] = Uart1Res;
            usbStr.receiveIndex++;
        }
                //接收帧完毕
        if((usbStr.receiveIndex >= USB_FRAME_LENMAX || usbStr.receiveIndex >= usbStr.receiveBuff[2]) && usbStr.receiveIndex > USB_FRAME_LENMIN)
        {
            uint8_t check = 0;
            uint8_t length = USB_FRAME_LENMIN;
        
            length = usbStr.receiveBuff[2];
            for(int i=0;i<length-1;i++)
                check += usbStr.receiveBuff[i];
            
            if(check == usbStr.receiveBuff[length-1])//校验位
            {
                memcpy(usbStr.receiveBuffFinished,usbStr.receiveBuff,USB_FRAME_LENMAX);	
                usbStr.receiveFinished = true;
                
                //智能车控制指令特殊处理（保障实时性）
                if(USB_ADDR_CONTROL  == usbStr.receiveBuffFinished[1])
                {
                    Bint16_Union bint16_Union;
                    Bint32_Union bint32_Union;
                    for(int i=0;i<4;i++)
                        bint32_Union.U8_Buff[i] = usbStr.receiveBuffFinished[3+i];
                    
                    bint16_Union.U8_Buff[0] = usbStr.receiveBuffFinished[7];
                    bint16_Union.U8_Buff[1] = usbStr.receiveBuffFinished[8];
                    
                    // SERVO_SetPwmValueCorrect(bint16_Union.U16);
                    // icarStr.ServoPwmSet = bint16_Union.U16;         //方向
                    // icarStr.SpeedSet = bint32_Union.Float;          //速度				
                }
				
                if(!usbStr.connected)//上位机初次连接通信
                {
                    //RGB_SetAllColor(RGB_COLOR_GREEN);
                    //GPIO_BuzzerEnable(BuzzerOk);
                    usbStr.connected = true;
                }
                
                usbStr.counterDrop = 0;
            }
            
            usbStr.receiveIndex = 0;
            usbStr.receiveStart = false;
        }
        
    }

    handle->rxDataSize = USB_receivexfer.dataSize; // 还原缓冲区长度
	handle->rxData = USB_receivexfer.data;			// 还原缓冲区地址

}

/**
* @brief        USB通信处理函数
* @param              
**/
// void USB_Edgeboard_Handle(void)
// {
//     if(usbStr.receiveFinished)																//接收成功
//     {
//         usbStr.receiveFinished = false;
//         Bint32_Union bint32_Union;
//         Bint16_Union bint16_Union;
           
//         // 判断receiveBuffFinished[1]()最高位是否为1,读地址为0x81
//         if(usbStr.receiveBuffFinished[1] & 0x80)	//读数据
//         {
//             uint8_t Addr = (uint8_t)(usbStr.receiveBuffFinished[1] & 0x7F);//将最高位qin
//             switch(Addr)
//             {
//                 case USB_ADDR_BATTERY :             //电池信息
//                     break;
                
//                 case USB_ADDR_SERVOTHRESHOLD :      //舵机阈值
//                     break;
//             }
//         }
//         // 写地址为0x01
//         else //写数据
//         {
//             switch(usbStr.receiveBuffFinished[1])
//             {
//                 case USB_ADDR_SERVOTHRESHOLD :   //舵机阈值
//                     if(usbStr.receiveBuffFinished[3] == 1)          //左转阈值
//                     {
//                         bint16_Union.U8_Buff[0] = usbStr.receiveBuffFinished[4];
//                         bint16_Union.U8_Buff[1] = usbStr.receiveBuffFinished[5];
//                         servoStr.thresholdLeft = bint16_Union.U16;
//                         flashSaveEnable = true; //等待Flash存储
//                         SERVO_SetPwmValue(servoStr.thresholdLeft);
//                         GPIO_BuzzerEnable(BuzzerDing);
//                     }
//                     else if(usbStr.receiveBuffFinished[3] == 2)     //右转阈值
//                     {
//                         bint16_Union.U8_Buff[0] = usbStr.receiveBuffFinished[4];
//                         bint16_Union.U8_Buff[1] = usbStr.receiveBuffFinished[5];
//                         servoStr.thresholdRight = bint16_Union.U16;
//                         flashSaveEnable = true; //等待Flash存储
//                         SERVO_SetPwmValue(servoStr.thresholdRight);
//                         GPIO_BuzzerEnable(BuzzerDing);
//                     }
//                     else if(usbStr.receiveBuffFinished[3] == 3)     //中值
//                     {
//                         bint16_Union.U8_Buff[0] = usbStr.receiveBuffFinished[4];
//                         bint16_Union.U8_Buff[1] = usbStr.receiveBuffFinished[5];
//                         servoStr.thresholdMiddle = bint16_Union.U16;
//                         flashSaveEnable = true; //等待Flash存储
//                         SERVO_SetPwmValue(servoStr.thresholdMiddle);
//                         GPIO_BuzzerEnable(BuzzerDing);
//                     }
//                     break;
                
//                 case USB_ADDR_BUZZER :      //蜂鸣器音效
//                     if(usbStr.receiveBuffFinished[3] == 1)          //OK
//                         GPIO_BuzzerEnable(BuzzerOk);
//                     else if(usbStr.receiveBuffFinished[3] == 2)     //Warnning
//                         GPIO_BuzzerEnable(BuzzerWarnning);
//                     else if(usbStr.receiveBuffFinished[3] == 3)     //Finish
//                         GPIO_BuzzerEnable(BuzzerFinish);
//                     else if(usbStr.receiveBuffFinished[3] == 4)     //Ding
//                         GPIO_BuzzerEnable(BuzzerDing);
//                     else if(usbStr.receiveBuffFinished[3] == 5)     //SystemStart
//                         GPIO_BuzzerEnable(BuzzerSysStart);
                    
//                     break;
                
//                 case USB_ADDR_LIGHT :         //LED灯效
//                     for(int i=0;i<4;i++)
//                         bint32_Union.U8_Buff[i] = usbStr.receiveBuffFinished[i+3];
                
//                     RGB_SetAllColor((unsigned long)bint32_Union.U32);
//                     rgbStr.lastColor = (unsigned long)bint32_Union.U32;
                
//                     break;

//                 case USB_ADDR_SPEEDMODE:        //速控模式切换
//                     if(usbStr.receiveBuffFinished[3] == 1)    //开环模式
//                         motorStr.CloseLoop = false;                    
//                     else
//                         motorStr.CloseLoop = true;
                    
//                     icarStr.SpeedSet = 0;
//                     GPIO_BuzzerEnable(BuzzerDing);
//                     break;
                
                    
//                 //-----------------------------[自检软件相关]-------------------------------------------
//                 case USB_ADDR_INSPECTOR :           //自检软件心跳
//                     usbStr.inspectorEnable = true;
//                     break;
                
//                 case USB_ADDR_SELFCHECK :           //开始自检
//                     ICAR_SelfcheckControl(usbStr.receiveBuffFinished[3]);
//                     break;             
//             }      
            
//         }
//     }
    
    
    //-----------------------[自检软件数据发送]-----------------------------
    // if(usbStr.inspectorEnable && usbStr.connected && usbStr.counterSend > 150)//150ms
    // {
    //     USB_Edgeboard_ServoThreshold(1);        //发送舵机阈值
    //     Delay_Ms(1);
    //     USB_Edgeboard_ServoThreshold(2);        
    //     Delay_Ms(1);
    //     USB_Edgeboard_ServoThreshold(3);
    //     Delay_Ms(1);
    //     USB_Edgeboard_BatteryInfo();            //发送电池信息
    //     Delay_Ms(1);
    //     USB_Edgeboard_CarSpeed();               //发送车速
    //     usbStr.counterSend = 0; 
    // }
// }


// void USB_Edgeboard_Timr(void)
// {
//     if(usbStr.connected)//USB通信掉线检测
//     {
//         usbStr.counterDrop++;
//         if(usbStr.counterDrop >3000)//3s
//         {
//             usbStr.connected = false;
//             usbStr.inspectorEnable = false;
//             icarStr.selfcheckEnable = false;
//         }
        
//         if(usbStr.inspectorEnable)
//         {
//             usbStr.counterSend++;
//         }
//     }
// }



/**
* @brief        USB-Edgeboard发送一个字节数据
* @param                     
**/
void USB_Edgeboard_TransmitByte(uint8_t data)
{
    uart_putchar(USART_1, data);
}


/**
* @brief        发送按键响应信息
* @param        time: 按下时长/ms       
**/
void USB_Edgeboard_TransmitKey(uint16_t time)
{
    uint8_t check = 0;
    uint8_t buff[8];
    Bint16_Union bint16_Union;
    
    buff[0] = 0x42; //帧头
    buff[1] = USB_ADDR_KEYINPUT; //地址
    buff[2] = 0x06; //帧长

    bint16_Union.U16 = time;
    buff[3] = bint16_Union.U8_Buff[0];
    buff[4] = bint16_Union.U8_Buff[1];
    
    for(int i=0;i<5;i++)
        check += buff[i];

    buff[5] = check;

	for(int i=0;i<8;i++)
		USB_Edgeboard_TransmitByte(buff[i]);
}

/**
* @brief        发送车速信息
* @ref                
**/
 void USB_Edgeboard_CarSpeed(void)
 {
     Bint32_Union bint32_Union;
     uint8_t check = 0;
     uint8_t buff[10];
     buff[0] = 0x42; //帧头
     buff[1] = USB_ADDR_SPEEDBACK; //地址
     buff[2] = 0x08; //帧长
        
     bint32_Union.Float = icarStr.SpeedFeedback;
     buff[3] = bint32_Union.U8_Buff[0];
     buff[4] = bint32_Union.U8_Buff[1];
     buff[5] = bint32_Union.U8_Buff[2];
     buff[6] = bint32_Union.U8_Buff[3];

     for(int i=0;i<7;i++)
         check += buff[i];
    
     buff[7] = check;
    
     for(int i=0;i<10;i++)
         USB_Edgeboard_TransmitByte(buff[i]);
 }


/**
* @brief        发送自检信息
* @ref          
* @author       Leo
* @note         
**/
 void USB_Edgeboard_Selfcheck(uint8_t step)
 {
     Bint16_Union bint16_Union;
     uint8_t check = 0;
     uint8_t buff[9];
     buff[0] = 0x42; //帧头
     buff[1] = USB_ADDR_SELFCHECK; //地址
     buff[2] = 0x07; //帧长
        
     buff[3] = step;
    
     bint16_Union.U16 = icarStr.errorCode;
     buff[4] = bint16_Union.U8_Buff[0];
     buff[5] = bint16_Union.U8_Buff[1];

     for(int i=0;i<6;i++)
         check += buff[i];
    
     buff[6] = check;
    
     for(int i=0;i<9;i++)
         USB_Edgeboard_TransmitByte(buff[i]);
 }


//----------------------------------------------[UNIT-智能汽车自检软件通信内容（此部分未开源）]----------------------------------------------------------
 /**
 * @brief        发送舵机阈值
 * @param        chanel: 1/左转阈值，2/右转阈值，3/中值
 * @ref          
 * @author       Leo
 * @note         
 **/
 void USB_Edgeboard_ServoThreshold(uint8_t chanel)
 {
     if(chanel<1 || chanel>3)
         return;
    
     Bint16_Union bint16_Union;
     uint8_t check = 0;
     uint8_t buff[9];
     buff[0] = 0x42; //帧头
     buff[1] = USB_ADDR_SERVOTHRESHOLD; //地址
     buff[2] = 0x07; //帧长
     buff[3] = chanel; //通道
    
     switch(chanel)
     {
         case 1:
         {  
             bint16_Union.U16 = servoStr.thresholdLeft;
             buff[4] = bint16_Union.U8_Buff[0];
             buff[5] = bint16_Union.U8_Buff[1];
             break;
         }
         case 2:
         {
             bint16_Union.U16 = servoStr.thresholdRight;
             buff[4] = bint16_Union.U8_Buff[0];
             buff[5] = bint16_Union.U8_Buff[1];
             break;
         }
         case 3:
         {
             bint16_Union.U16 = servoStr.thresholdMiddle;
             buff[4] = bint16_Union.U8_Buff[0];
             buff[5] = bint16_Union.U8_Buff[1];
             break;
         }
     }
    
     for(int i=0;i<6;i++)
         check += buff[i];
    
     buff[6] = check;
    
     for(int i=0;i<9;i++)
         USB_Edgeboard_TransmitByte(buff[i]);
 }


/**
* @brief        USB/UART初始化(串口1)
* @param              
**/
void USB_Edgeboard_Init(void)
{
  uart_init(USART_1, 115200, UART1_TX_B12, UART1_RX_B13);
	NVIC_SetPriority(LPUART1_IRQn, 0); // 设置串口中断优先级 范围0-15 越小优先级越高
	uart_rx_irq(USART_1, 1);
	uart_tx_irq(USART_1, 1);
	// 配置串口接收的缓冲区及缓冲区长度
	USB_receivexfer.dataSize = 1;
	USB_receivexfer.data = &USB_uart_rx_buffer;
	// 设置中断函数及其参数
	uart_set_handle(USART_1, &USB_g_lpuartHandle, USB_UART_Callback, NULL, 0, USB_receivexfer.data, 1);

}