/*
   流水灯代码-------添加时钟切换功能，支持HSI、HSE、PLL
*/

/*
	//切换至 HSI 内部高速震荡时钟
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
	RCC->CFGR |= RCC_CFGR_SW_HSI;

	//切换至 HSE 外部高速震荡时钟
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
	RCC->CFGR |= RCC_CFGR_SW_HSE;

	//切换至 PLL 锁相环，可以自定义频率
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
	RCC->CFGR |= RCC_CFGR_SW_PLL;

*/


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
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_13|GPIO_Pin_14; // 第9，10号引脚
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽模式，增加驱动能力
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;// 引脚的最大工作速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 没有上下拉电阻
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
		GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10); 		
		GPIO_SetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14); 	
}

int main(void)
{
    //标准C，先定义再使用
	uint32_t i = 0;
	
    LedInit();
	
	
	while(1)
	{	
		
		i++;
		if(i == 1) { 
			//切换至 HSE 外部高速震荡时钟  8M 
			RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
			RCC->CFGR |= RCC_CFGR_SW_HSE;
		}
		
		
		else if(i == 2) {

			//切换至 HSI 内部高速震荡时钟  16M
			RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
			RCC->CFGR |= RCC_CFGR_SW_HSI;						
		}
		
		
		else if(i == 3) {
			//切换至 PLL 锁相环，可以自定义频率  168M
			RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
			RCC->CFGR |= RCC_CFGR_SW_PLL;
			
			//清空标志位
			i = 0;
		}
		
		
		
		
		
		//将引脚设置为低电平，亮灯
		GPIO_ResetBits(GPIOF,GPIO_Pin_9); 
		delay();
		//将引脚设置为高电平，灭灯
		GPIO_SetBits(GPIOF,GPIO_Pin_9); 	
		delay();
		
		GPIO_ResetBits(GPIOF,GPIO_Pin_10); 
		delay();
		GPIO_SetBits(GPIOF,GPIO_Pin_10); 	
		delay();
		
		GPIO_ResetBits(GPIOE,GPIO_Pin_13);
    delay();		
		GPIO_SetBits(GPIOE,GPIO_Pin_13); 	
		delay();
		
	  GPIO_ResetBits(GPIOE,GPIO_Pin_14);
    delay();		
		GPIO_SetBits(GPIOE,GPIO_Pin_14); 	
		delay();
		
	}
	
}
