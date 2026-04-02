#ifndef __USART3_H
#define __USART3_H

#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
extern uint8_t Flag_Usart3_Idle;
extern char Usart3_buff[128];
extern uint8_t len3;

void Usart3_Init(unsigned bound);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);
void USART1_Send_data(char *str);
void Usart_SendString2( USART_TypeDef * pUSARTx, char *str);
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);

#endif
