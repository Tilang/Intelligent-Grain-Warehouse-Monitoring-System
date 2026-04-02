#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "ohos_init.h"
#include "cmsis_os2.h"
#include "cJSON.h"
#include "sys_config.h"

#include "hal_bsp_wifi.h"
#include "hal_bsp_mqtt.h"
#include "hal_bsp_key.h"
#include "hal_bsp_ap3216c.h"
#include "hal_bsp_aw2013.h"
#include "hal_bsp_ssd1306.h"
#include "hal_bsp_pcf8574.h"
#include "hal_bsp_sht20.h"
#include "hal_bsp_nfc.h"
#include "hal_bsp_nfc_to_wifi.h"
#include "mqtt_send_task.h"
#include "mqtt_recv_task.h"
#include "sensor_collect_task.h"
#include "oled_show_log.h"

#include "hi_io.h"
#include "hi_gpio.h"
#include "hi_uart.h"
#include "my_uart2.h"



#define TASK_STACK_SIZE (5 * 1024)
#define TASK_INIT_DELAY 1 // s

osThreadId_t mqtt_send_task_id;      // mqtt 发布数据任务ID
osThreadId_t mqtt_recv_task_id;      // mqtt 接收数据任务ID
osThreadId_t sensor_collect_task_id; // 传感器采集任务ID

osThreadId_t my_485_id;
osThreadId_t auto_mode_id;
osThreadId_t uart_recv_task_id;
osThreadId_t uart_send_task_id;


//rs485数组
uint8_t air_arr[8]={0x01,0x03,0x00,0x00,0x00,0x06,0xC5,0xC8};//
uint8_t co2_arr[8]={0x02,0x03,0x00,0x00,0x00,0x01,0x84,0x39};//
uint8_t soil_arr[8] = {0X03,0X03,0X00,0X00,0X00,0X04,0X45,0XEB};//
uint8_t voltage_arr[8] = {0X04,0X04,0X00,0X00,0X00,0X02,0X71,0X9E};//
//接收数组

uint8_t air_RS485buf[17]={0};
uint8_t co2_RS485buf[13]={0};
uint8_t soil_RS485buf[13]={0};
uint8_t voltage_RS485buf[13]={0};	

//定义int

//extern float voltage=0,water=0,soil_temp=0,conductivity=0,ph=0;
// uint16_t temp_value,humi_value,lux_value,CO2_value;
uint16_t water_h=0,water_l=0,temp_h=0,temp_l=0,dd_h=0,dd_l=0,ph_h=0,ph_l=0,voltage_h=0,voltage_l=0;
float voltage=0,water=0,soil_temp=0,conductivity=0,ph=0;
uint16_t temp_value_max = 30,temp_value_min = 20 ,humi_value_max = 85,humi_value_min = 40;lux_value_max = 100,lux_value_min = 18,
water_max=29,water_min=10,voltage_max=10,voltage_min = 2;

//int *auto_bool1 = 0;
//int  auto_bool = 0;
static a = 0;

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
// 发送任务
void my_uart_send_task2(void) {
    char buf[] = "hello"; // 自动包含 '\0'
}

// 接收任务
char stm_buf[128]; // 全局缓冲区
char recv_stm_buf[32]; // 全局缓冲区
//int Lora_temp;
//int Lora_humi;
extern int Lora_CO;
void my_uart_recv_task2(void) {
    //char buf[] = "FAN_ON";
    while(1) {
       memset(stm_buf, 0, sizeof(stm_buf)); // 确保stm_buf足够大
        my_uart_recv_buff(stm_buf, 128);     // 接收数据

        char *token = strtok(stm_buf, ","); // 分割逗号分隔的数据
        //sys_msg_data.CO2_value = 100;
        while (token != NULL) {
            // 解析每个数据项
            if (sscanf(token, "CO:%d", &Lora_CO) == 1) {
                //u2_printf("CO:%d\r\n", sys_msg_data.CO2_value);
                //sprintf(ssd1306_buf, "CO:%d", Lora_CO);
            } else if (sscanf(token, "TEMP:%d", &sys_msg_data.temp_value) == 1) {
                //u2_printf("TEMP:%d\r\n", sys_msg_data.temp_value);
                //sprintf(ssd1306_buf, "TEMP:%.1f", temperature);
            } else if (sscanf(token, "HUMI:%d", &sys_msg_data.humi_value) == 1) {
                //u2_printf("HUMI:%d\r\n", sys_msg_data.humi_value);
            } else if (sscanf(token, "Lux:%d", &sys_msg_data.lux_value) == 1) {
                //u2_printf("HUMI:%d\r\n", sys_msg_data.humi_value);
            } // 添加更多传感器解析...
            token = strtok(NULL, ","); // 处理下一个数据项
        }
    }
}
/*
void my_uart(void)
{
    char buf[32] = "hello";
    while(1){ 
        my_uart_send_buff(buf,8);
        sleep(2);
    }
}
*/
//自动模式
void my_auto_mode(void)
{
}



int mqtt_init(void)
{
    // 连接MQTT服务器
    while (MQTTClient_connectServer(SERVER_IP_ADDR, SERVER_IP_PORT) != WIFI_SUCCESS) {
        printf("mqttClient_connectServer\r\n");
        oled_consle_log("==mqtt ser no==");
        sleep(TASK_INIT_DELAY);
        SSD1306_CLS(); // 清屏
    }
    printf("mqttClient_connectServer\r\n");
    oled_consle_log("==mqtt ser yes=");
    sleep(TASK_INIT_DELAY);

    // 初始化MQTT客户端
    while (MQTTClient_init(MQTT_CLIENT_ID, MQTT_USER_NAME, MQTT_PASS_WORD) != WIFI_SUCCESS) {
        printf("mqttClient_init\r\n");
        oled_consle_log("==mqtt cli no==");
        sleep(TASK_INIT_DELAY);
        SSD1306_CLS(); // 清屏
    }
    printf("mqttClient_init\r\n");
    oled_consle_log("==mqtt cli yes=");
    sleep(TASK_INIT_DELAY);

    // 订阅MQTT主题
    while (MQTTClient_subscribe(MQTT_TOPIC_SUB_COMMANDS) != 0) {
        printf("mqttClient_subscribe\r\n");
        oled_consle_log("==mqtt sub no==");
        sleep(TASK_INIT_DELAY);
        SSD1306_CLS(); // 清屏
    }
    printf("mqttClient_subscribe\r\n");
    oled_consle_log("=mqtt sub yes==");
    sleep(TASK_INIT_DELAY);
    SSD1306_CLS(); // 清屏

    return 0;
}
int nfc_connect_wifi_init(void)
{
    // 通过NFC芯片进行连接WiFi
    uint8_t ndefLen = 0;      // ndef包的长度
    uint8_t ndef_Header = 0;  // ndef消息开始标志位-用不到
    uint32_t result_code = 0; // 函数的返回值
    oled_consle_log("===start nfc===");

    // 读整个数据的包头部分，读出整个数据的长度
    if (result_code = NT3HReadHeaderNfc(&ndefLen, &ndef_Header) != true) {
        printf("NT3HReadHeaderNfc is failed. result_code = %d\r\n", result_code);
        return -1;
    }
    ndefLen += NDEF_HEADER_SIZE; // 加上头部字节
    if (ndefLen <= NDEF_HEADER_SIZE) {
        printf("ndefLen <= 2\r\n");
        return -1;
    }
    
    uint8_t *ndefBuff = (uint8_t *)malloc(ndefLen + 1);
    if (ndefBuff == NULL) {
        printf("ndefBuff malloc is Falied!\r\n");
        return -1;
    }
    if (result_code = get_NDEFDataPackage(ndefBuff, ndefLen) != HI_ERR_SUCCESS) {
        printf("get_NDEFDataPackage is failed. result_code = %d\r\n", result_code);
        return -1;
    }
    // 打印读出的数据
    printf("start print ndefBuff.\r\n");
    for (size_t i = 0; i < ndefLen; i++) {
        printf("0x%x ", ndefBuff[i]);
    }
    oled_consle_log("=== end nfc ===");
    sleep(TASK_INIT_DELAY);

    oled_consle_log("== start wifi==");
    // 连接WiFi
    while (NFC_configuresWiFiNetwork(ndefBuff) != WIFI_SUCCESS) {
        printf("nfc connect wifi is failed!\r\n");
        oled_consle_log("=== wifi no ===");
        sleep(TASK_INIT_DELAY);
        SSD1306_CLS(); // 清屏
    }
    printf("nfc connect wifi is SUCCESS\r\n");
    oled_consle_log("===wifi  yes===");
    sleep(TASK_INIT_DELAY);
    return 0;
}
void SL_peripheral_init(void)
{
    // 外设的初始化
    KEY_Init();    // 按键初始化
    PCF8574_Init();  // 初始化IO扩展芯片
    AW2013_Init(); // 三色LED灯的初始化
    AW2013_Control_RGB(0, 0, 0);
    AP3216C_Init(); // 三合一传感器初始化
    SSD1306_Init(); // OLED 显示屏初始化
    SSD1306_CLS();  // 清屏
    nfc_Init();
    SHT20_Init(); 
    
    set_D1(true);
    set_D2(true);
    set_D3(true);
    set_D4(true);

}
static void smartLamp_Project_example(void)
{
    printf("Enter smartLamp_Project_example()!\r\n");
    p_MQTTClient_sub_callback = &mqttClient_sub_callback;
    // 全局变量的初始化
    sys_msg_data.led_light_value = 100; // RGB灯的亮度值为100%的状态
    
    SL_peripheral_init();
    nfc_connect_wifi_init();
    mqtt_init();

    my_uart_init();




    //  创建线程
    osThreadAttr_t options;
    options.name = "mqtt_send_task";
    options.attr_bits = 0;
    options.cb_mem = NULL;
    options.cb_size = 0;
    options.stack_mem = NULL;
    options.stack_size = TASK_STACK_SIZE;
    options.priority = osPriorityNormal;
    mqtt_send_task_id = osThreadNew((osThreadFunc_t)mqtt_send_task, NULL, &options);
    if (mqtt_send_task_id != NULL) {
        printf("ID = %d, Create mqtt_send_task_id is OK!\r\n", mqtt_send_task_id);
    }

    options.name = "mqtt_recv_task";
    mqtt_recv_task_id = osThreadNew((osThreadFunc_t)mqtt_recv_task, NULL, &options);
    if (mqtt_recv_task_id != NULL) {
        printf("ID = %d, Create mqtt_recv_task_id is OK!\r\n", mqtt_recv_task_id);
    }

    options.name = "sensor_collect_task";
    sensor_collect_task_id = osThreadNew((osThreadFunc_t)sensor_collect_task, NULL, &options);
    if (sensor_collect_task_id != NULL) {
        printf("ID = %d, Create sensor_collect_task_id is OK!\r\n", sensor_collect_task_id);
    }


    osThreadAttr_t auto_opt;
    auto_opt.name = "my_auto_mode";
    auto_opt.stack_size = 1024;
    auto_opt.priority = osPriorityNormal;
    auto_mode_id = osThreadNew((osThreadFunc_t)my_auto_mode,NULL,&auto_opt);

    osThreadAttr_t uart_send_task_opt;
    uart_send_task_opt.name = "uart_send";
    uart_send_task_opt.stack_size = 1024;
    uart_send_task_opt.priority = osPriorityNormal;
    uart_send_task_id = osThreadNew((osThreadFunc_t)my_uart_send_task2,NULL,&uart_send_task_opt);

   osThreadAttr_t uart_recv_task_opt;
    uart_recv_task_opt.name = "uart_recv";
    uart_recv_task_opt.stack_size = 1024;
    uart_recv_task_opt.priority = osPriorityNormal;
    uart_recv_task_id = osThreadNew((osThreadFunc_t)my_uart_recv_task2,NULL,&uart_recv_task_opt);
}
SYS_RUN(smartLamp_Project_example);
