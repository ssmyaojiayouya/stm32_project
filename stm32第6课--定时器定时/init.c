#include "myhead.h"

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
	
	// 将引脚设置为高电平,灭灯
    GPIO_SetBits(GPIOF, GPIO_Pin_9|GPIO_Pin_10);
    GPIO_SetBits(GPIOE, GPIO_Pin_13|GPIO_Pin_14);
	
}	








