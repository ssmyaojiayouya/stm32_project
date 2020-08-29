#include "led.h"

/*
	led_init:初始化LED灯的引脚
	参数：
		无
	返回值：
		无
*/
void led_init(void)//PD0~PD7
{
		/*使能GPIOD的时钟*/
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); 

	  /*GPIO初始化为输出推挽模式*/
	  GPIO_InitTypeDef   GPIO_InitStruct;
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1| GPIO_Pin_2|GPIO_Pin_3|
	  GPIO_Pin_4|GPIO_Pin_5| GPIO_Pin_6|GPIO_Pin_7;
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;  
	  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	  GPIO_Init(GPIOD,&GPIO_InitStruct); 

	  /*默认LED灯为熄灭状态*/
	  GPIO_ResetBits(GPIOD, GPIO_Pin_0); 
	  GPIO_ResetBits(GPIOD, GPIO_Pin_1); 
	  GPIO_ResetBits(GPIOD, GPIO_Pin_2); 
	  GPIO_ResetBits(GPIOD, GPIO_Pin_3); 
	  GPIO_ResetBits(GPIOD, GPIO_Pin_4); 
	  GPIO_ResetBits(GPIOD, GPIO_Pin_5); 
	  GPIO_ResetBits(GPIOD, GPIO_Pin_6); 
	  GPIO_ResetBits(GPIOD, GPIO_Pin_7); 
}


/*
	led_ctl:控制某个LED灯
	@LedN: 要控制的那个灯的编号，如:	
			LED_D1
			LED_D2
			...
	@OnOff: 开灯或关灯，如
			LED_ON
			LEF_OFF
	返回值:
		无
*/
void led_ctl(int LedN, int OnOff)
{
		switch(LedN)
		{
			case LED_D1:
				if(OnOff == LED_ON)
				{
						GPIO_SetBits(GPIOD,GPIO_Pin_0);
				}
				else if(OnOff == LED_OFF)
				{
						GPIO_ResetBits(GPIOD, GPIO_Pin_0);
				}
				break;
			case LED_D2:
				if(OnOff == LED_ON)
				{
						GPIO_SetBits(GPIOD,GPIO_Pin_1);
				}
				else if(OnOff == LED_OFF)
				{
						GPIO_ResetBits(GPIOD, GPIO_Pin_1);
				}
				break;
			case LED_D3:
				if(OnOff == LED_ON)
				{
						GPIO_SetBits(GPIOD,GPIO_Pin_2);
				}
				else if(OnOff == LED_OFF)
				{
						GPIO_ResetBits(GPIOD, GPIO_Pin_2);
				}
				break;
			case LED_D4:
				if(OnOff == LED_ON)
				{
						GPIO_SetBits(GPIOD,GPIO_Pin_3);
				}
				else if(OnOff == LED_OFF)
				{
						GPIO_ResetBits(GPIOD, GPIO_Pin_3);
				}
				break;
			case LED_D5:
				if(OnOff == LED_ON)
				{
						GPIO_SetBits(GPIOD,GPIO_Pin_4);
				}
				else if(OnOff == LED_OFF)
				{
						GPIO_ResetBits(GPIOD, GPIO_Pin_4);
				}
				break;
			case LED_D6:
				if(OnOff == LED_ON)
				{
						GPIO_SetBits(GPIOD,GPIO_Pin_5);
				}
				else if(OnOff == LED_OFF)
				{
						GPIO_ResetBits(GPIOD, GPIO_Pin_5);
				}
				break;
			case LED_D7:
				if(OnOff == LED_ON)
				{
						GPIO_SetBits(GPIOD,GPIO_Pin_6);
				}
				else if(OnOff == LED_OFF)
				{
						GPIO_ResetBits(GPIOD, GPIO_Pin_6);
				}
				break;
			case LED_D8:
				if(OnOff == LED_ON)
				{
						GPIO_SetBits(GPIOD,GPIO_Pin_7);
				}
				else if(OnOff == LED_OFF)
				{
						GPIO_ResetBits(GPIOD, GPIO_Pin_7);
				}
				break;
		}
}

/*
	all_led_ctl:根据LedState的每一位控制对应的LED的状态
	@LedState: LedState的8位表示每一盏灯的状态
	返回值:
		无
*/
void all_led_ctl(u8 LedState)
{
		if(LedState & 1<<0) 
		{
				GPIO_SetBits(GPIOD,GPIO_Pin_0);
		}
		else
		{
				GPIO_ResetBits(GPIOD, GPIO_Pin_0);
		}
		
		if(LedState & 1<<1)
		{
				GPIO_SetBits(GPIOD,GPIO_Pin_1);
		}
		else
		{
				GPIO_ResetBits(GPIOD, GPIO_Pin_1);
		}
		
		if(LedState & 1<<2)
		{
				GPIO_SetBits(GPIOD,GPIO_Pin_2);
		}
		else
		{
				GPIO_ResetBits(GPIOD, GPIO_Pin_2);
		}
		
		if(LedState & 1<<3)
		{
				GPIO_SetBits(GPIOD,GPIO_Pin_3);
		}
		else
		{
				GPIO_ResetBits(GPIOD, GPIO_Pin_3);
		}
		
		if(LedState & 1<<4)
		{
				GPIO_SetBits(GPIOD,GPIO_Pin_4);
		}
		else
		{
				GPIO_ResetBits(GPIOD, GPIO_Pin_4);
		}
		
		if(LedState & 1<<5)
		{
				GPIO_SetBits(GPIOD,GPIO_Pin_5);
		}
		else
		{
				GPIO_ResetBits(GPIOD, GPIO_Pin_5);
		}
		
		if(LedState & 1<<6)
		{
				GPIO_SetBits(GPIOD,GPIO_Pin_6);
		}
		else
		{
				GPIO_ResetBits(GPIOD, GPIO_Pin_6);
		}
		
		if(LedState & 1<<7)
		{
				GPIO_SetBits(GPIOD,GPIO_Pin_7);
		}
		else
		{
				GPIO_ResetBits(GPIOD, GPIO_Pin_7);
		}
}

