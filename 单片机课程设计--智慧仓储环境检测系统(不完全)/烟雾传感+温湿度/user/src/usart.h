#ifndef __USART_H__
#define __USART_H__

#include "stm32f4xx.h"
#include "stdio.h"
#include "string.h"
#include "led.h"

static GPIO_InitTypeDef GPIO_InitStructure;
static USART_InitTypeDef USART_InitStructure;
static NVIC_InitTypeDef NVIC_InitStructure;

static double MQ_value = 0;			//烟雾浓度值
static double light_value = 0;		//光照强度值
static double temp_value = 0;		//温度
static double pres_value = 0;		//气压
static double humi_value = 0;		//湿度
static double alti_value = 0;		//海拔

//static uint32_t values = 0;
static uint8_t GY_SendBuf[128] = {0};
static uint8_t MQ_SendBuf[32] = {0};

static unsigned char MQ_Warm[] = {"!!!!!!烟雾浓度超过70，请检查仓库安全情况!!!!!!\n"};
static unsigned char LIGHT_Warm[] = {"!!!!!!光照强度超过120lux，请注意仓库安全情况!!!!!!\n"};
static unsigned char TEMP_Warm[] = {"!!!!!!温度值超过35℃，请及时降温!!!!!!\n"};
static unsigned char HUMI_Warm[] = {"!!!!!!湿度值超过80%，请注意保持干燥!!!!!!\n"};
		
//volatile static u8 flag = 0;	//volatile拒绝编译器优化变量(此关键字是重点)

extern void usart1_init(uint32_t BaudRate);
extern void usart2_init(uint32_t BaudRate);//PA2，PA3
extern void usart3_init(uint32_t BaudRate);//PB10，PB11

extern void USART_SendDatas(USART_TypeDef * USARTx,uint8_t *SendBuf,uint16_t len);
extern void USART1_IRQHandler(void);
extern void USART2_IRQHandler(void);
extern void USART3_IRQHandler(void);

u8 SUM_Check(u8 *dataBuf, u8 n);
u8 BACK_SUM_Check(u8 *dataBuf, u8 n);
extern void Warming(void);

#endif /*__USART_H__*/
