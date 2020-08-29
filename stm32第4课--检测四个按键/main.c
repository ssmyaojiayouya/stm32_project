#include "stm32f4xx.h"

static GPIO_InitTypeDef  GPIO_InitStructure;


void delay()
{
	uint32_t i = 0x1000000;
	
	while(i--);
	
}


void LedInit()
{
	/* 使能端口F，E时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOE, ENABLE);

	/* 配置端口F,E功能 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10| GPIO_Pin_13|GPIO_Pin_14; // 第9，10号引脚
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽模式，增加驱动能力
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;// 引脚的最大工作速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 没有上下拉电阻
	// 初始化gpio
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_Init(GPIOE, &GPIO_InitStructure);

}

void KeyInit()
{
	/* 使能端口A，E时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // 输入模式，检测端口电平
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽模式，增加驱动能力
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;// 引脚的最大工作速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 没有上下拉电阻
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

int main(void)
{
	LedInit();
	KeyInit();
	
	GPIO_SetBits(GPIOF, GPIO_Pin_9|GPIO_Pin_10);
	GPIO_SetBits(GPIOE, GPIO_Pin_13|GPIO_Pin_14);
	while(1)
	{
		
		// 判断按键PA0是否按下
		if(Bit_RESET == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
		{
			// 将引脚设置为低电平，亮灯
			GPIO_ResetBits(GPIOF, GPIO_Pin_9);
		}
		else
			// 将引脚设置为高电平,灭灯
			GPIO_SetBits(GPIOF, GPIO_Pin_9);
		
		
		// 判断按键PE2是否按下
		if(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2))
		{
			// 将引脚设置为低电平，亮灯
			GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		}
		else
			// 将引脚设置为高电平,灭灯
			GPIO_SetBits(GPIOF, GPIO_Pin_10);
		
		// 判断按键PE3是否按下
		if(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3))
		{
			// 将引脚设置为低电平，亮灯
			GPIO_ResetBits(GPIOE, GPIO_Pin_9|GPIO_Pin_13);
		}
		else
			// 将引脚设置为高电平,灭灯
			GPIO_SetBits(GPIOE, GPIO_Pin_9|GPIO_Pin_13);
			
		
		// 判断按键PE4是否按下
		if(Bit_RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4))
		{
			// 将引脚设置为低电平，亮灯
			GPIO_ResetBits(GPIOE, GPIO_Pin_9|GPIO_Pin_14);
		}
		else
			// 将引脚设置为高电平,灭灯
			GPIO_SetBits(GPIOE, GPIO_Pin_9|GPIO_Pin_14);
			
			
	}
	
	
}
