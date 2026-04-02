#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "RS485.h"
#include "delay.h"
#include "Serial.h"    

//float temp_value,humi_value,lux_value,CO2_value;

//u8 lux_temp_humi_Sendbuf[8]={0x02,0x03,0x00,0x00,0x00,0x06,0xC5,0xfb};	

//u8 key1,key2,key3,key4;	

//u8 lux_temp_humi_RS485buf[17]={0};

//void RS485_data(void)
//{
//		
//		RS485_Send_Data(lux_temp_humi_Sendbuf,8);
//		//tim4_init(10000,7200);
//		delay_ms(500);
//    RS485_Receive_Data(lux_temp_humi_RS485buf,&key1);
//		humi_value = ((lux_temp_humi_RS485buf[3] << 8) | lux_temp_humi_RS485buf[4])/10;	
//		temp_value = ((lux_temp_humi_RS485buf[5] << 8) | lux_temp_humi_RS485buf[6])/10;	
//		lux_value = ((lux_temp_humi_RS485buf[7] << 8) | lux_temp_humi_RS485buf[8])/10;			
//					
//}

//__align(8) char UART4_TxBuff[256];  

//void u4_printf(char* fmt,...) 
//{  
//	unsigned int i,length;
//	
//	va_list ap;
//	va_start(ap,fmt);
//	vsprintf(UART4_TxBuff,fmt,ap);
//	va_end(ap);	
//	
//	length=strlen((const char*)UART4_TxBuff);		
//	while((UART4->SR&0X40)==0);
//	for(i = 0;i < length;i ++)
//	{			
//		UART4->DR = UART4_TxBuff[i];
//		while((UART4->SR&0X40)==0);	
//	}	
//}



void RS485_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);//使能GPIOA,D时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//使能USART2时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //PD7端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	//PA2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  GPIO_Init(GPIOC, &GPIO_InitStructure);  

	RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4,ENABLE);//复位串口2
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4,DISABLE);//停止复位
 
	
 #ifdef EN_UART4_RX		  	//如果使能了接收
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8位数据长度
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;///奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式

  USART_Init(UART4, &USART_InitStructure); ; //初始化串口
  
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn; //使能串口2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //从优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启中断
  USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);	
	
	
  USART_Cmd(UART4, ENABLE);                    //使能串口 

 #endif

  RS485_TX_EN=0;			//默认为接收模式
	
}


#ifdef EN_UART4_RX  

u8 RS485_RX_BUF[64];
u8 RS485_RX_CNT=0;
uint8_t RS485_RX_Len = 0;
uint8_t Flag_RS485_Idle = 0;
void UART4_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)//接收到数据
  { 
		res =USART_ReceiveData(UART4);
		RS485_RX_BUF[RS485_RX_Len]=res;
		RS485_RX_Len++;
  }
	else if(USART_GetITStatus(UART4,USART_IT_IDLE) != RESET)//接收到一帧数据,空闲中断，	
	{																													 //接收1个字节的空闲时间内没有数据接收，则发起空闲中断
		UART4->SR;//先读SR，先清理SR
		UART4->DR;//再读DR
		Flag_RS485_Idle = 1;
		//RS485_RX_Len = 0;
	}
	//USART_ClearITPendingBit(UART4, USART_IT_RXNE);
}
#endif

//RS485发送len个字节.
//buf:发送区首地址
//len:发送的字节数(为了和本代码的接收匹配,这里建议不要超过64个字节)
void RS485_Send_Data(u8 *buf,u8 len)
{
	u8 t;
	RS485_TX_EN=1;			//设置为发送模式
  	for(t=0;t<len;t++)		//循环发送数据
	{		   
		while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);	  
		USART_SendData(UART4,buf[t]);
	}	 
 
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);		
	RS485_RX_Len=0;	  
	RS485_TX_EN=0;				//设置为接收模式	
}
//RS485查询接收到的数据
//buf:接收缓存首地址
//len:读到的数据长度
void RS485_Receive_Data(u8 *buf,u8 *len)
{
	u8 rxlen=RS485_RX_Len;
	u8 i=0;
	*len=0;				//默认为0	
	if(Flag_RS485_Idle ==1)
		{
			
			for(i=0;i<rxlen;i++)
		{
			buf[i]=RS485_RX_BUF[i];	
		}		
		*len=RS485_RX_Len;	//记录本次数据长度
		RS485_RX_Len=0;		//清零
		Flag_RS485_Idle =0;
		}
}



