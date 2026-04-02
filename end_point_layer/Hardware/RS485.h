#ifndef __RS485_H
#define  __RS485_H
#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "stdio.h"      //包含需要的头文件
#include "stdarg.h"		//包含需要的头文件 
#include "string.h"     //包含需要的头文件

#define RS485_TX_EN PDout(7)

//extern float temp_value,humi_value,lux_value,CO2_value;

//extern u8 lux_temp_humi_Sendbuf[8];

//extern u8 key1,key2,key3,key4;	

//extern u8 lux_temp_humi_RS485buf[17];

extern u8 RS485_RX_BUF[64]; 		//接收缓冲,最大64个字节
extern u8 RS485_RX_CNT;   			//接收到的数据长度
extern uint8_t Flag_RS485_Idle;

#define EN_UART4_RX 	1			//0,不接收;1,接收.

//void RS485_data(void);
void RS485_Send_Data(u8 *buf,u8 len);
void RS485_Receive_Data(u8 *buf,u8 *len);
void RS485_Init(u32 bound);
#endif
