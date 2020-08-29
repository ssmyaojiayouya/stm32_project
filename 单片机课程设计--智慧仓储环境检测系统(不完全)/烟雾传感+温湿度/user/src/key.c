#include "key.h"

void Key_Init()
{
	// 使能端口F时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	// 配置端口功能
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;			// 输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	// 控制IO引脚的最大速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;		// 不需要上下拉电阻
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void Extern_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//EXTI0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;				//指定使用第几个中断
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//选择模式
	EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Falling;	//选择触发方式
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//使能中断
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//启用外部中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//指定抢占优先级0-15
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		//指定子优先级0-15
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能
	NVIC_Init(&NVIC_InitStructure);//中断优先级得配置，中断使能
		
	//EXTI2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;				//指定使用第几个中断
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//选择模式
	EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Falling;	//选择触发方式
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//使能中断
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//启用外部中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//指定抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		//指定子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能
	NVIC_Init(&NVIC_InitStructure);//中断优先级得配置，中断使能
	
	/*
	//EXTI3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;				//指定使用第几个中断
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//选择模式
	EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Falling;	//选择触发方式
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//使能中断
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//启用外部中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//指定抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;		//指定子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能
	NVIC_Init(&NVIC_InitStructure);//中断优先级得配置，中断使能


	//EXTI4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;				//指定使用第几个中断
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//选择模式
	EXTI_InitStructure.EXTI_Trigger= EXTI_Trigger_Falling;	//选择触发方式
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//使能中断
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//启用外部中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//指定抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;		//指定子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能
	NVIC_Init(&NVIC_InitStructure);//中断优先级得配置，中断使能
	*/
}
