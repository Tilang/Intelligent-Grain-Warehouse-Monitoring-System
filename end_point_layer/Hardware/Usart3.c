#include <Usart3.h>

uint8_t Flag_Usart3_Idle = 0;//空闲中断的标记
//uint8_t Rx_Usart3 = 0;		 //接收中断的标记
char Usart3_buff[128];
uint8_t len3 = 0;

void Usart3_Init(unsigned bound)
{
		GPIO_InitTypeDef GPIO_InitStructure;                         
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE); 
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;               
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB , &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;             
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOB , &GPIO_InitStructure);
		
		USART_InitStructure.USART_BaudRate = bound;               
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART3,&USART_InitStructure);                   
		
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;         
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;       
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         
		NVIC_Init(&NVIC_InitStructure);                         
		
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);     
		USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);		
		
		USART_Cmd(USART3,ENABLE);
}


void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{

	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);									//发送数据
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//等待发送完成
	}

}

void USART1_Send_data(char *str)//用于发送字符串
{
	while(*str != '\0')
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
		USART_SendData(USART1,*str);
		str++;
	}
}


/*****************  发送字符串 **********************/
void Usart_SendString2( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*
************************************************************
*	函数名称：	UsartPrintf
*
*	函数功能：	格式化打印
*
*	入口参数：	USARTx：串口组
*				fmt：不定长参
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{

	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//格式化
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}

}


void USART3_IRQHandler(void)
{ 
	u8 res3; 
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//接收到数据
  { 
		res3 =USART_ReceiveData(USART3);
		Usart3_buff[len3]=res3;
		len3++;
  } else if(USART_GetITStatus(USART3,USART_IT_IDLE) != RESET)//接收到一帧数据,空闲中断，	
	{																													 //接收1个字节的空闲时间内没有数据接收，则发起空闲中断
		USART3->SR;//先读SR，先清理SR
		USART3->DR;//再读DR
		Flag_Usart3_Idle = 1;
		len3 = 0;
	}
} 

