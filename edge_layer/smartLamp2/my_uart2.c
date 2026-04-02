#include <stdarg.h>
#include <stdio.h>

#include <hi_uart.h>
#include "hi_io.h"
#include <cmsis_os2.h>


#define BUF_SIZE 128

static hi_u8 uart_rx_buf[BUF_SIZE];
static hi_u32 uart_rx_len = 0;

osMutexId_t uart_mutex;
int text_a = 24;
int Lora_CO = 20;
int FAN_value=0;

// 自定义UART2的printf函数

void u2_printf(const char *fmt, ...)
{
    osMutexAcquire(uart_mutex, osWaitForever);
    char buff[128];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buff, sizeof(buff), fmt, args);
    va_end(args);
    hi_uart_write(HI_UART_IDX_2, (uint8_t *)buff, strlen(buff));
        // ... 原有代码 ...
    osMutexRelease(uart_mutex);
}

// 初始化UART2
void my_uart_init(void)
{
    hi_io_set_func(HI_IO_NAME_GPIO_11, HI_IO_FUNC_GPIO_11_UART2_TXD);
    hi_io_set_func(HI_IO_NAME_GPIO_12, HI_IO_FUNC_GPIO_12_UART2_RXD);

    hi_uart_attribute uart_param = {
        .baud_rate = 115200,
        .data_bits = 8,
        .stop_bits = 1,
        .parity = 0,
    };
    hi_uart_init(HI_UART_IDX_2, &uart_param, NULL);

     //   hi_uart_init(HI_UART_IDX_2, &attr);
    // 注册中断服务函数
    //hi_uart_register_irq(HI_UART_IDX_2, HI_UART_RX_INT, uart_rx_isr);
    //hi_uart_enable_irq(HI_UART_IDX_2, HI_UART_RX_INT); // 使能接收中断
}

