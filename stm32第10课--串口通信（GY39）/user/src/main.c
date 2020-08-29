#include "stm32f4xx.h"
#include "bitband.h"
#include "delay.h"
/*
#include "led.h"

#include "usart.h"
#include "key.h"
#include "stdio.h"
#include "string.h"
*/
/**********************************
*程序功能: 烟雾传感器
*		通过串口2把命令发送到传感器，
*		通过串口1读取烟雾浓度值发送到PC端显示
**********************************/

unsigned char Luxcmd[] = {0xA5,0x81,0x26}; //持续输出光照强度
unsigned char Tphhcmd[] = {0xA5,0x82,0x27}; //持续读气压温湿度指令

static GPIO_InitTypeDef  GPIO_InitStructure;

void LedInit()
{
	/* 使能端口F，E时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOE, ENABLE);

	/* 配置端口F,E功能 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_13|GPIO_Pin_14; // 第9，10号引脚
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽模式，增加驱动能力
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;// 引脚的最大工作速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 没有上下拉电阻
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOF, GPIO_Pin_9);
	GPIO_SetBits(GPIOF, GPIO_Pin_10);
	GPIO_SetBits(GPIOE, GPIO_Pin_13);
	GPIO_SetBits(GPIOE, GPIO_Pin_14);

}

int main()
{
		LedInit();
		
		//GPIO_ResetBits(GPIOF, GPIO_Pin_9);
		
		//usart1_init(9600);
		//usart2_init(9600);
		//usart3_init(9600);

		while(1)
		{	
				PFout(9) = 1; 
			USART_SendDatas(USART3,Luxcmd,sizeof(Luxcmd));
				delay_ms(500);
				PFout(9) = 0;
				delay_ms(500);

		}
}


