#ifndef MY_UART2_H
#define MY_UART2_H
/*

void u2_printf(const char *fmt, ...);
*/
extern int text_a;
extern int Lora_CO;
extern int FAN_value;
void my_uart_init(void);
void u2_printf(const char *fmt, ...);
#endif

