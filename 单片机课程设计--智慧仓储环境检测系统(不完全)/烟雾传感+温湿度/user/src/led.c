#include "led.h"

void Led_Init()//PF9,PF10,PE13,PE14
{
	GPIO_InitTypeDef    GPIO_InitStructure;
	// 使能端口F时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOE, ENABLE);
	
	// 配置端口功能
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		// 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		// 推挽模式，增加驱动能力
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	// 控制IO引脚的最大速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;		// 不需要上下拉电阻
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	PFout(9) = 1;
	PFout(10) = 1;
	PEout(13) = 1;
	PEout(14) = 1;
}

void Led_flash1()
{
	PFout(9) ^= 1;	//异或实现翻转亮灭
}

void Led_flash2()
{
	PFout(10) ^= 1;
}

void Led_flash3()
{
	PEout(13) ^= 1;
}

void Led_flash4()
{
	PEout(14) ^= 1;
}

void Led_flash5()
{
	PFout(9) ^= 1;
	PFout(10) ^= 1;
	PEout(13) ^= 1;
	PEout(14) ^= 1;
}
