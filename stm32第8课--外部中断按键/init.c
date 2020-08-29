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


//1.中断抢占演示
void EXTI0_Init(void)
{
	 EXTI_InitTypeDef   EXTI_InitStructure;
	 NVIC_InitTypeDef   NVIC_InitStructure;
   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	//选择对应的GPIO引脚连接到相应的中断控制线
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
	
	
	//根据 EXTI_InitTypeDef 结构体进行外部中断控制线 0 初始化
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode =EXTI_Mode_Interrupt; //中断请求
  EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	//根据 NVIC_InitTypeDef 结构体对中断向量进行配置
	NVIC_InitStructure.NVIC_IRQChannel =EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0x02;
  NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}



void EXTI2_Init(void)
{
	 EXTI_InitTypeDef   EXTI_InitStructure;
	 NVIC_InitTypeDef   NVIC_InitStructure;
   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	//选择对应的GPIO引脚连接到相应的中断控制线
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource2);
	
	
	//根据 EXTI_InitTypeDef 结构体进行外部中断控制线 2 初始化
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  EXTI_InitStructure.EXTI_Mode =EXTI_Mode_Interrupt; //中断请求
  EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	//根据 NVIC_InitTypeDef 结构体对中断向量进行配置
	NVIC_InitStructure.NVIC_IRQChannel =EXTI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0x02;
  NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

}

void EXTI3_Init(void)
{
	 EXTI_InitTypeDef   EXTI_InitStructure;
	 NVIC_InitTypeDef   NVIC_InitStructure;
   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	//选择对应的GPIO引脚连接到相应的中断控制线
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource3);
	
	
	//根据 EXTI_InitTypeDef 结构体进行外部中断控制线 3 初始化
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode =EXTI_Mode_Interrupt; //中断请求
  EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	//根据 NVIC_InitTypeDef 结构体对中断向量进行配置
	NVIC_InitStructure.NVIC_IRQChannel =EXTI3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0x02;
  NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}


void EXTI4_Init(void)
{
	 EXTI_InitTypeDef   EXTI_InitStructure;
	 NVIC_InitTypeDef   NVIC_InitStructure;
   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	//选择对应的GPIO引脚连接到相应的中断控制线
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);
	
	
	//根据 EXTI_InitTypeDef 结构体进行外部中断控制线 4 初始化
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode =EXTI_Mode_Interrupt; //中断请求
  EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	//根据 NVIC_InitTypeDef 结构体对中断向量进行配置
	NVIC_InitStructure.NVIC_IRQChannel =EXTI4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0x02;
  NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
}


void EXTI0_IRQHandler(void)
{
	//检查是否有触发中断
	if(EXTI_GetITStatus(EXTI_Line0) == SET) 
	{
		//添加用户代码		
    liushuideng1();
		
		//清空标志位，告诉CPU已经处理完中断请求，可以触发下一次中断
		EXTI_ClearITPendingBit(EXTI_Line0);		
	}
	
}


void EXTI2_IRQHandler(void)
{
	//检查是否有触发中断
	if(EXTI_GetITStatus(EXTI_Line2) == SET) 
	{
		//添加用户代码		
    liushuideng2();
		
		
		//清空标志位，告诉CPU已经处理完中断请求，可以触发下一次中断
		EXTI_ClearITPendingBit(EXTI_Line2);		
	}
	
}

void EXTI3_IRQHandler(void)
{
	//检查是否有触发中断
	if(EXTI_GetITStatus(EXTI_Line3) == SET) 
	{
		//添加用户代码		
    two_liangmie();
		
		
		//清空标志位，告诉CPU已经处理完中断请求，可以触发下一次中断
		EXTI_ClearITPendingBit(EXTI_Line3);		
	}
	
}


void EXTI4_IRQHandler(void)
{
	//检查是否有触发中断
	if(EXTI_GetITStatus(EXTI_Line4) == SET) 
	{
		//添加用户代码		
    all_liangmie();
		
		
		//清空标志位，告诉CPU已经处理完中断请求，可以触发下一次中断
		EXTI_ClearITPendingBit(EXTI_Line4);		
	}
	
}


