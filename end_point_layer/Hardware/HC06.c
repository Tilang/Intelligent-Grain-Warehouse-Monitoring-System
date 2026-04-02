#include "HC06.h"
#include "sys.h"
#include "Delay.h"
#include "Usart3.h"
#include "Serial.h"

char str_temp[100];
//extern char res_buf[100];			 //串口一的接收数组
//u8 Find_char(char *a,char *b)  //b为子串,寻找发过来的数据里面有没有相应的字符串，但是串口一的中断没改，可参看串口3
//{ 
//  if(strstr(a,b)!=NULL)
//	    return 0;
//	else
//			return 1;
//}
void HC05_SetName(void)
{
	sprintf(str_temp,"AT+NAME=%s\r\n",HC05_NAME);
	Usart_SendString2(USART1,str_temp);
	Delay_ms(500);
}

void HC05_SetPassword(void)
{
	sprintf(str_temp,"AT+PSWD=%s\r\n",HC05_PWD);
	Usart_SendString2(USART1,str_temp);
	Delay_ms(500);
}
void HC05_SetBaud(void)
{
	sprintf(str_temp,"AT+UART=%s,0,0\r\n",HC05_Baund);	
	Usart_SendString2(USART1,str_temp);
	Delay_ms(500);
}
void HC05_AT(void)
{
	printf("AT\r\n");
	Delay_ms(500);
	//while(Find_char((char*)res_buf,"OK"));                      
	//printf("English_message_OK1\r\n");
}

void HC05_init(void)
{
	Serial_Init(38400); //可以发出来但是我不知道有没有问题，感觉会影响串口，万一串口正在接收数据，结果换波特率了
	HC05_SetName();			//但是如果是顺序执行的话，应该问题不大
	HC05_SetPassword();	//除非波特率换成38400，还没换回9600时，触发串口中断,传感器发送9600波特率的数据
	HC05_SetBaud(); 		//所以说还得是HC06更好用直接发AT，不用改波特率
	Serial_Init(9600);
}

