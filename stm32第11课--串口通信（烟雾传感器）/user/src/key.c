#include "key.h"

void Key_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	// 使能端口F时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	// 配置端口功能
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;			// 输出模式
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;	// 控制IO引脚的最大速度
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;		// 不需要上下拉电阻
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}



