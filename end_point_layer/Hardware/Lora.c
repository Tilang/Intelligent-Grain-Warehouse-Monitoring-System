#include "Usart3.h"
#include "Delay.h"
#include "Lora.h"
#include "Serial.h"
#include "string.h"

void LoRa_Config(void)
{
	char sendbuf[50];	
	//Usart3_Init(115200);;//进入配置模式前设置通信波特率和校验位(115200 8位数据 1位停止 无数据校验）
	printf("printf_OK");
	Delay_ms(40);
	
	UsartPrintf(USART3,"+++");
	Delay_ms(100);
	UsartPrintf(USART3,"a");
	Delay_ms(100);
	sprintf((char*)sendbuf,"AT+ADDR=%s%s\r\n",LORA_ADDRH,LORA_ADDRL);//设置设备地址
	Usart_SendString2(USART3,sendbuf);
	if (strstr(Usart3_buff, "OK") ==NULL)  		//没有接收到相要的回复
	{
		printf("AT+ADDR_Error");
		memset(Usart3_buff, 0, sizeof(Usart3_buff));
	}
	Delay_ms(100);
	sprintf((char*)sendbuf,"AT+UART=%s,8,1,NONE,NFC\r\n",LORA_UARTBOUND);//设置串口波特率、数据校验位
	Usart_SendString2(USART3,sendbuf);
	if (strstr(Usart3_buff, "OK") ==NULL)  		//没有接收到相要的回复
	{
		printf("AT+UART_Error");
		memset(Usart3_buff, 0, sizeof(Usart3_buff));
	}
	Delay_ms(100);
	sprintf((char*)sendbuf,"AT+SPD=%s\r\n",LORA_WLRATE);//设置空中速率
	Usart_SendString2(USART3,sendbuf);
	if (strstr(Usart3_buff, "OK") ==NULL)  		//没有接收到相要的回复
	{
		printf("AT+SPD_Error");
		memset(Usart3_buff, 0, sizeof(Usart3_buff));
	}
	Delay_ms(100);	
	sprintf((char*)sendbuf,"AT+CH=%s\r\n",LORA_CHANNEL);//设置信道
	Usart_SendString2(USART3,sendbuf);
	if (strstr(Usart3_buff, "OK") ==NULL)  		//没有接收到相要的回复
	{
		printf("AT+CH_Error");
		memset(Usart3_buff, 0, sizeof(Usart3_buff));
	}
	Delay_ms(100);	
	sprintf((char*)sendbuf,"AT+WMODE=%s\r\n",LORA_WORKMODE);//设置工作模式
	Usart_SendString2(USART3,sendbuf);
	if (strstr(Usart3_buff, "OK") ==NULL)  		//没有接收到相要的回复
	{
		printf("AT+WMODE_Error");
		memset(Usart3_buff, 0, sizeof(Usart3_buff));
	}
	Delay_ms(100);
	sprintf((char*)sendbuf,"AT+ENTM\r\n");//设置工作模式
	Usart_SendString2(USART3,sendbuf);
	if (strstr(Usart3_buff, "OK") ==NULL)  		//没有接收到相要的回复
	{
		printf("AT+ENTM_Error");
		memset(Usart3_buff, 0, sizeof(Usart3_buff));
	}
}

//void LoRa_TRANS_Set(const char* tx)
//{
//	char sendbuf[50];	
//	sprintf((char*)sendbuf,"%s",tx);
//	Usart_SendString2(USART3,sendbuf);
//}

//void LoRa_FP_Set(int ADDH,int ADDL,int channel ,const char* tx)//地址和通道是16进制，发送字符串tx
//{
//	char sendbuf[50];	
//	sprintf((char*)sendbuf,"%c %c %c %s",ADDH,ADDL,channel,tx);
//	Usart_SendString2(USART3,sendbuf);
//}
