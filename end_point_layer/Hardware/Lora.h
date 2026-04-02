#ifndef __LORA_H
#define __LORA_H

#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

#define LORA_ADDRH       "00"                               /* 设备地址 */
#define LORA_ADDRL       "01"
#define LORA_CHANNEL     "4"                               /* 信道 */
#define LORA_WORKMODE    "TRANS"     /* 工作模式 :FP:定点传输，TRANS透传模式*/
#define LORA_TMODE       "RUN"            /* 发射模式 */
#define LORA_WLTIME      "10"           /* 休眠时间 */
#define LORA_UARTBOUND   "115200"  /* UART通讯波特率 */
#define LORA_WLRATE      "10"         /* 空中速率 */

void LoRa_Config(void);

#endif
