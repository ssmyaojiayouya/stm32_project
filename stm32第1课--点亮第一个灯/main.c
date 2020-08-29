#include "stm32f4xx.h"


static  GPIO_InitTypeDef  GPIO_InitStructure;


void delay()
{

	uint32_t i = 0x100000;
	while(i--);

}

int main()
{
	/* GPIOG Peripheral clock enable---使能端口时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

	/* Configure PG6 and PG8 in output pushpull mode----配置端口功能 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9; //第9号引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 控制IO引脚的最大速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 不需要上下拉电阻
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	while(1)
	{
		// 设置为高电平
		GPIO_SetBits(GPIOF, GPIO_Pin_9);
		delay();
		// 设置为低电平
		GPIO_ResetBits(GPIOF, GPIO_Pin_9);
		delay();
	
	}

}

