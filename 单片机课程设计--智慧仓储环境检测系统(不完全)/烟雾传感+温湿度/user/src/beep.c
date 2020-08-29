#include "beep.h"

void Beep_Init()//PF8
{
	GPIO_InitTypeDef    GPIO_InitStructure;
	// 使能端口F时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	// 配置端口功能
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		// 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		// 推挽模式，增加驱动能力
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	// 控制IO引脚的最大速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;		// 不需要上下拉电阻
	GPIO_Init(GPIOF, &GPIO_InitStructure);
}

