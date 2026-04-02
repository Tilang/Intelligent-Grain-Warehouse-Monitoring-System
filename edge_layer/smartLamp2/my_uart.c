
int Lora_CO = 20;
int FAN_value=0;
/*
void my_uart_init(void)
{

    uint32_t ret = 0;
    // 初始化串口
    hi_io_set_func(HI_IO_NAME_GPIO_11, HI_IO_FUNC_GPIO_11_UART2_TXD);
    hi_io_set_func(HI_IO_NAME_GPIO_12, HI_IO_FUNC_GPIO_12_UART2_RXD);

    hi_uart_attribute uart_param = {
        .baud_rate = 9600,
        .data_bits = 8,
        .stop_bits = 1,
        .parity = 0,
    };
    ret = hi_uart_init(HI_UART_IDX_2, &uart_param, NULL);
    if (ret != HI_ERR_SUCCESS) {
        printf("hi uart init is faild.\r\n");
    }
}
void my_uart_send_buff(unsigned char *str, unsigned short len) {
    hi_u32 ret = hi_uart_write(HI_UART_IDX_2, str, len);
    if (ret == HI_ERR_FAILURE) {
        printf("uart send failed.\n");
    }
}

// 接收函数
void my_uart_recv_buff(unsigned char *str, unsigned short msg_len) {
    unsigned char recv_buf[128];
    hi_u32 len = hi_uart_read(HI_UART_IDX_2, recv_buf, sizeof(recv_buf));
    if (len == HI_ERR_FAILURE) {
        printf("uart read failed.\n");
        return;
    }
    // 确保不溢出并添加终止符
    unsigned short copy_len = len < msg_len ? len : msg_len - 1;
    memcpy(str, recv_buf, copy_len);
    str[copy_len] = '\0';
}
*/
/*
void my_uart_send_task(void)
{
    char buf[32] = "hello";
    while(1){ 
        my_uart_send_buff(buf,8);
        sleep(2);
    }
}

void my_uart_recv_task(void)
{
    //char buf[32] = {0};
    while(1){
        memset(stm_buf,0,sizeof(stm_buf));
        my_uart_recv_buff(stm_buf,32);
        printf("recv_buf:%s\n",stm_buf);

    }
}
*/