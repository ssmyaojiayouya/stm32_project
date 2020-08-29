#include "myhead.h"

/*
    函数功能：将所有的按键的检测使用外部中断进行实现
*/




int main(void)
{
	//灭灯状态
	GPIO_SetBits(GPIOF,GPIO_Pin_9); 
	GPIO_SetBits(GPIOF,GPIO_Pin_10); 
	GPIO_SetBits(GPIOE,GPIO_Pin_13); 
	GPIO_SetBits(GPIOE,GPIO_Pin_14); 

	
	LedInit();
	KeyInit();
	EXTI0_Init();
	
	EXTI2_Init();
	
	EXTI3_Init();
	
	EXTI4_Init();
	
	while(1)
	{
      
	}
	
	
}


