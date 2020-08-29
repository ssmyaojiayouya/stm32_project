#include "stm32f4xx.h"

static GPIO_InitTypeDef  GPIO_InitStructure;

//通过库函数直接读取IO的电平
#define S1 	GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) //PE2 --- KEY1


void delay()
{
	uint32_t i = 0x1000000;
	
	while(i--);
	
}

void KeyInit()
{
	/* GPIOG Peripheral clock enable---使能端口E,A时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //第 2 根引脚 key1 PE2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //设置输入模式[重点修改]
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //设置 IO 的速度为 100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //不需要上拉电阻
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
}


void LedInit()
{
	/* 使能端口F，E时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOE, ENABLE);

	/* 配置端口F,E功能 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // 第9号引脚
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽模式，增加驱动能力
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;// 引脚的最大工作速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 没有上下拉电阻
	GPIO_Init(GPIOF, &GPIO_InitStructure);


}

int main(void)
{

	
    LedInit();
	KeyInit();
	
	while(1)
	{	
		if(S1 == 0) {
		    //将引脚设置为低电平，亮灯
		    GPIO_ResetBits(GPIOF,GPIO_Pin_9); 
		}
		else {
			//将引脚设置为高电平，灭灯
			GPIO_SetBits(GPIOF,GPIO_Pin_9); 	
		}

	}
	
}
