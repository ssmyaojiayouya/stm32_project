#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"
//#include "usart.h"

/**********************************
*程序功能: 串口实验
*		（1）按下按键，向串口发出字符串，并被串口助手接收
    （2）通过串口助手，向MCU发送数据，发送字符'A'把LED全点亮，发送字符'B'把LED全熄灭
**********************************/


static GPIO_InitTypeDef  GPIO_InitStructure;

#define S0 	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) //PA0 --- KEY0

void KeyInit()
{
	/* GPIOG Peripheral clock enable---使能端口E,A时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOA, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4; //第 0,2,3,4 根引脚 key0,1,2,3 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //设置输入模式[重点修改]
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //设置 IO 的速度为 100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //不需要上拉电阻
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

void LedInit()
{
	/* 使能端口F，E时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOE, ENABLE);

	/* 配置端口F,E功能 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_13 | GPIO_Pin_14; // 第9,10,13,14号引脚
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽模式，增加驱动能力
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;// 引脚的最大工作速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 没有上下拉电阻
	
	GPIO_Init(GPIOF, &GPIO_InitStructure);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOF,GPIO_Pin_9); 
	GPIO_SetBits(GPIOF,GPIO_Pin_10); 
	GPIO_SetBits(GPIOE,GPIO_Pin_13); 	
	GPIO_SetBits(GPIOE,GPIO_Pin_14); 	

}


unsigned char str[] = {"hello,are you ok?\r\n"};

int main()
{
    usart1_init(9600);
		LedInit();
	  KeyInit();
	  while(1)
		{
			if(S0 == 0) {
				 USART_SendDatas(USART1,str,sizeof(str));		
         delay_ms(1000);	
			}				
		}
}

