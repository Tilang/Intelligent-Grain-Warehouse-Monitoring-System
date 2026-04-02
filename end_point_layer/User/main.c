#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "Key.h"
#include "string.h"
#include "Serial.h"
#include "Usart3.h"
#include "dht11.h"
#include "Lora.h"
#include "RS485.h"
#include "stepmotor.h"

/*


u16 temp_raw, humi_raw, lux_raw, CO2_raw, tsoil_raw, hsoil_raw, dsoil_raw, phsoil_raw; // 改为整型变量
 
//    u8 lux_Sendbuf[8]={0x01,0x03,0x00,0x00,0x00,0x01,0x84,0x0a};
  u8 air_Sendbuf[8]={0x02,0x03,0x00,0x00,0x00,0x06,0xC5,0xfb};//空气数据
    u8 soil_Sendbuf[8]={0x01,0x03,0x00,0x00,0x00,0x02,0xc4,0x0b};//采集土壤指令接收9位前两位为湿度除十得数据
    u8 asoil_Sendbuf[8]={0x08,0x03,0x00,0x00,0x00,0x04,0x44,0x90};//采集土壤数据接收13位温度湿度电导率ph
    u8 CO2_Sendbuf[8]={0x03,0x03,0x00,0x00,0x00,0x01,0x85,0xE8};//采集二氧化碳指令接收13位直接
                                            
    //02 03 00 00 00 06 C5 FB
    //01 03 00 00 00 01 84 0A
    u8 key1,key2,key3,key4;
    
    u8 air_RS485buf[17]={0};
//    u8 lux_RS485buf[17]={0};
    u8 soil_RS485buf[9]={0};
    u8 asoil_RS485buf[13]={0};
    u8 CO2_RS485buf[7]={0};
    
    void RS485_data(void)
{
        
        RS485_Send_Data(air_Sendbuf,8);
        delay_ms(1000);
    RS485_Receive_Data(air_RS485buf,&key1);
    
        // 发送土壤温湿度指令
    RS485_Send_Data(soil_Sendbuf, 8);
    delay_ms(1000);
    RS485_Receive_Data(soil_RS485buf, &key2);
    
        // 发送土壤电导率/PH指令
    RS485_Send_Data(asoil_Sendbuf, 8);
    delay_ms(1000);
    RS485_Receive_Data(asoil_RS485buf, &key3);
    
        //发送co2对应指令
        RS485_Send_Data(CO2_Sendbuf, 8);
    delay_ms(1000);
    RS485_Receive_Data(CO2_RS485buf, &key4);
//        lux_value = ((air_RS485buf[7] << 8) | air_RS485buf[8])/10;    
//        temp_value = ((air_RS485buf[5] << 8) | air_RS485buf[6])/10;    
//        humi_value = ((air_RS485buf[3] << 8) | air_RS485buf[4])/10;
    
        // 解析原始数据为整数
    humi_raw = (air_RS485buf[3] << 8) | air_RS485buf[4];
    temp_raw = (air_RS485buf[5] << 8) | air_RS485buf[6];
    lux_raw = (air_RS485buf[7] << 8) | air_RS485buf[8];
        
        hsoil_raw = (soil_RS485buf[3] << 8) | soil_RS485buf[4];//土壤湿度
        tsoil_raw = (soil_RS485buf[5] << 8) | soil_RS485buf[6];//土壤温度
        
        
        dsoil_raw = (asoil_RS485buf[6] << 8) | asoil_RS485buf[7];//土壤电导率
        phsoil_raw = (asoil_RS485buf[9] << 8 | asoil_RS485buf[10]);//土壤PH
        
        CO2_raw = (CO2_RS485buf[3] << 8) | CO2_RS485buf[4];
    
        temp_value = ( temp_raw / 10 ) + ( temp_raw % 10 /10 ) ; 
        humi_value = ( humi_raw / 10 ) + ( humi_raw % 10 /10 ) ; 
        lux_value = ( lux_raw / 10 ) + ( lux_raw % 10 / 10) ; 

        hsoil_value = ( hsoil_raw / 10 ) + ( hsoil_raw % 10 /10 ) ; 
        tsoil_value = ( tsoil_raw / 10 ) + ( tsoil_raw % 10 /10 ) ;
        dsoil_value = ( dsoil_raw / 10 ) + ( dsoil_raw % 10 /10 );
        phsoil_value = ( phsoil_raw / 10 ) + ( phsoil_raw % 10 /10 );
        CO2_value = (CO2_raw / 10 ) + ( CO2_raw % 10 /10 );
}

*/

//float temp_value,humi_value,lux_value,CO2_value;
//  u8 air_Sendbuf[8]={0x02,0x03,0x00,0x00,0x00,0x06,0xC5,0xfb};//空气数据
u8 temp_value,humi_value,lux_value,CO2_value;
u8 lux_temp_humi_Sendbuf[8]={0x02,0x03,0x00,0x00,0x00,0x06,0xC5,0xfb};	
u8 CO2_Sendbuf[8]={0x03,0x03,0x00,0x00,0x00,0x01,0x85,0xE8};//采集二氧化碳指令接收13位直接

u8 key1,key2,key3,key4;	

u8 lux_temp_humi_RS485buf[17]={0};
u8 CO2_RS485buf[7]={0};

void RS485_data(void)
{
		
		RS485_Send_Data(lux_temp_humi_Sendbuf,8);
		//tim4_init(10000,7200);
		Delay_ms(500);
    RS485_Receive_Data(lux_temp_humi_RS485buf,&key1);
		humi_value = ((lux_temp_humi_RS485buf[3] << 8) | lux_temp_humi_RS485buf[4])/10;	
		temp_value = ((lux_temp_humi_RS485buf[5] << 8) | lux_temp_humi_RS485buf[6])/10;	
		lux_value = ((lux_temp_humi_RS485buf[7] << 8) | lux_temp_humi_RS485buf[8])/10;			
	
		RS485_Send_Data(CO2_Sendbuf, 8);
    Delay_ms(500);
    RS485_Receive_Data(CO2_RS485buf, &key2);
		CO2_value = ((CO2_RS485buf[3] << 8) | CO2_RS485buf[4])/10;
					
}



//#include "HC06.h"

uint8_t keyNum = 0;
u8 temp;
u8 humi;
int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	LED_Init();			//LED初始化
	Key_Init();
	Serial_Init(9600);		//串口初始化
	Usart3_Init(115200);	
	RS485_Init(9600);
	MOTOR_Init();
	while(DHT11_Init())
	{
		Delay_ms(500);
	}
	/*显示静态字符串*/
	OLED_ShowString(0, 0, "温度:",OLED_8X16);
	OLED_ShowString(0, 15, "湿度:",OLED_8X16);
	OLED_ShowString(0,31,"接收数据:",OLED_8X16);
	printf("OK \r\n");
	OLED_Update();
	Usart_SendString2(USART3,"USART3_OK");
	while (1)
	{			
		
		if(Flag_Usart3_Idle==1)														//如果接收完一帧数据
		{
			Flag_Usart3_Idle = 0;															//标志位清零
			//UsartPrintf(USART3,Usart3_buff);									//串口三发送buf
			UsartPrintf(USART1,Usart3_buff);
			OLED_ClearArea(0,47,128,16);										//OLED清除指定位置
			OLED_ShowString(0, 47, Usart3_buff,OLED_8X16);	//OLED显示buf
			if (strstr(Usart3_buff, "FAN_D3_ON") !=  NULL)					//如果收到LED_ON指令
			{
				LED1_ON();																		//点亮LED
				Serial_SendString("LED_ON_OK\r\n");						//串口1回传一个字符串LED_ON_OK，串口3进入中断后也回传一个
			} if (strstr(Usart3_buff, "FAN_D3_OFF") !=  NULL)	//如果收到LED_OFF指令
			{
				LED1_OFF();																		//熄灭LED
				Serial_SendString("LED_OFF_OK\r\n");					//串口回传一个字符串LED_OFF_OK
			} if (strstr(Usart3_buff, "MOTOR_ON") != NULL)	//如果收到LED_OFF指令
			{
				MOTOR_ON( );																	//熄灭LED
				Serial_SendString("MOTOR_ON_OK\r\n");					//串口回传一个字符串
			}if (strstr(Usart3_buff, "MOTOR_OFF") != NULL)	//如果收到指令
			{
				MOTOR_STOP();																	//熄灭LED
				Serial_SendString("MOTOR_OFF_OK\r\n");					//串口回传一个字符串
			}if (strstr(Usart3_buff, "TTL_ON") != NULL)	//如果收到LED_OFF指令
			{
				LED2_ON();																	//熄灭LED
				Serial_SendString("MOTOR_ON_OK\r\n");					//串口回传一个字符串
			}if (strstr(Usart3_buff, "TTL_OFF") != NULL)	//如果收到指令
			{
				LED2_OFF();																//熄灭LED
				Serial_SendString("MOTOR_OFF_OK\r\n");					//串口回传一个字符串
			}
			memset(Usart3_buff, 0, sizeof(Usart3_buff));		//清除Usart3_buff			
			//TTL_ON
		}
		
		keyNum= Key_GetNum();
		DHT11_Read_Data(&temp,&humi);			//获取温湿度数据
		OLED_Printf(42, 0, OLED_8X16, "%d   ", temp);			//显示
		OLED_Printf(42, 15, OLED_8X16, "%d   ", humi);		
		OLED_Update();			//OLED更新
		UsartPrintf(USART3,"CO:%d,TEMP:%d,HUMI:%d,Lux:%d\r\n",CO2_value,temp_value,humi_value,lux_value);
		UsartPrintf(USART1,"CO:%d,TEMP:%d,HUMI:%d,Lux:40\r\n",humi,temp,humi);
		RS485_data();
		if(keyNum == 1)				//按下PB11
		{								
			//LoRa_Config();			
			UsartPrintf(USART3,"CO:20,TEMP:25.6,HUMI:35\r\n");
			printf("按下1");
		}			
		if(keyNum == 2)			//PB1
		{
			UsartPrintf(USART3,"CO:24,TEMP:55.6,HUMI:45\r\n");
			printf("按下2");
			//UsartPrintf(USART3,"湿度:%d\r\n",humi);
		}
		 //这个我测试了，可以直接用，但是我觉得HC05_init早晚会出问题，我就注释了;对这个代码没问题，详细见HC05_init
							
														
	}
}
