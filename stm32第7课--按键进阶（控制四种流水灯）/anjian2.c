#include "stm32f4xx.h"

static GPIO_InitTypeDef  GPIO_InitStructure;

//通过库函数直接读取IO的电平
#define S0 	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) //PA0 --- KEY0
#define S1 	GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) //PE2 --- KEY1
#define S2 	GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) //PE3 --- KEY2
#define S3 	GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) //PE4 --- KEY3


void delayms(uint32_t x)
{
	uint32_t i;
	
	while(x--) for(i = 0;i < 120;i++);
	
}

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

}



int main(void)
{

	
    LedInit();
	KeyInit();
	
	GPIO_SetBits(GPIOF,GPIO_Pin_9); 
	GPIO_SetBits(GPIOF,GPIO_Pin_10); 
	GPIO_SetBits(GPIOE,GPIO_Pin_13); 
	GPIO_SetBits(GPIOE,GPIO_Pin_14); 
	
	while(1)
	{	
		if(S0 == 0) {
		     //将引脚设置为低电平，亮灯
		     GPIO_ResetBits(GPIOF,GPIO_Pin_9); 
		}
		else {
			//将引脚设置为高电平，灭灯
			GPIO_SetBits(GPIOF,GPIO_Pin_9); 
		}
		
		
		if(S1 == 0) {
			GPIO_ResetBits(GPIOF,GPIO_Pin_10); 
		}
		else {
			GPIO_SetBits(GPIOF,GPIO_Pin_10); 
		}
		
		
		if(S2 == 0) {
			GPIO_ResetBits(GPIOE,GPIO_Pin_13); 
		}
		else {
			GPIO_SetBits(GPIOE,GPIO_Pin_13); 
		}

		
		if(S3 == 0) {
			GPIO_ResetBits(GPIOE,GPIO_Pin_14); 
		}
		else {
			GPIO_SetBits(GPIOE,GPIO_Pin_14); 
		}		

	}
	
}
