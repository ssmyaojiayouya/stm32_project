#include "stm32f4xx.h"


static GPIO_InitTypeDef  GPIO_InitStructure;

//通过库函数直接读取IO的电平
#define S0 	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) //PA0 --- KEY0
#define S1 	GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) //PE2 --- KEY1
#define S2 	GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) //PE3 --- KEY2
#define S3 	GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) //PE4 --- KEY3

u8 flag1=0,flag2=0,flag3=0,flag4=0;


void delay_ms(uint32_t n)
{
  while(n--) {
		SysTick->CTRL = 0; // 关闭定时器
		SysTick->LOAD = 168000; // 设置定时器时间1ms		
		SysTick->VAL = 0; // 清除标志位
		SysTick->CTRL = 5; // 使能定时器工作，开始计数，同时使用时钟源为系统时钟（168M）
		
		while ((SysTick->CTRL & 0x00010000)==0);// 等待定时器计数完毕
		SysTick->CTRL = 0; // 关闭定时器				
	}
	
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


void KeyScan()
{
   if(S0 == 0 && S1 == 1 && S2 == 1 && S3 == 1) { //key0按下
	    delay_ms(5);//延时消抖
	    if(S0 == 0 && S1 == 1 && S2 == 1 && S3 == 1)
			flag1 = 1;
   }
   
   if(S0 == 1 && S1 == 0 && S2 == 1 && S3 == 1) { //key1按下
	    delay_ms(5); //延时消抖
	    if(S0 == 1 && S1 == 0 && S2 == 1 && S3 == 1)
			flag2 = 1;
   }


   if(S0 == 1 && S1 == 1 && S2 == 0 && S3 == 1) { //key2按下
	    delay_ms(5); //延时消抖
	    if(S0 == 1 && S1 == 1 && S2 == 0 && S3 == 1)
			flag3 = 1;
   }


   if(S0 == 1 && S1 == 1 && S2 == 1 && S3 == 0) { //key3按下
	    delay_ms(5); //延时消抖
	    if(S0 == 1 && S1 == 1 && S2 == 1 && S3 == 0)
			flag4 = 1;
   }   
  
}

void liushuideng1()
{
		//将引脚设置为低电平，亮灯
		GPIO_ResetBits(GPIOF,GPIO_Pin_9); 
		delay_ms(200);
		//将引脚设置为高电平，灭灯
		GPIO_SetBits(GPIOF,GPIO_Pin_9); 	
		delay_ms(200);
		
		GPIO_ResetBits(GPIOF,GPIO_Pin_10); 
		delay_ms(200);
		GPIO_SetBits(GPIOF,GPIO_Pin_10); 	
		delay_ms(200);
		
		GPIO_ResetBits(GPIOE,GPIO_Pin_13);
		delay_ms(200);
		GPIO_SetBits(GPIOE,GPIO_Pin_13); 	
		delay_ms(200);
		
		GPIO_ResetBits(GPIOE,GPIO_Pin_14);
		delay_ms(200);
		GPIO_SetBits(GPIOE,GPIO_Pin_14); 	
		delay_ms(200);
}

void liushuideng2()
{
		//将引脚设置为高电平，灭灯
		GPIO_SetBits(GPIOF,GPIO_Pin_9); 	
		delay_ms(200);
		//将引脚设置为低电平，亮灯
		GPIO_ResetBits(GPIOF,GPIO_Pin_9); 
		delay_ms(200);
	

		GPIO_SetBits(GPIOF,GPIO_Pin_10); 	
		delay_ms(200);
		GPIO_ResetBits(GPIOF,GPIO_Pin_10); 
		delay_ms(200);

		GPIO_SetBits(GPIOE,GPIO_Pin_13); 	
		delay_ms(200);
		GPIO_ResetBits(GPIOE,GPIO_Pin_13);
		delay_ms(200);

		GPIO_SetBits(GPIOE,GPIO_Pin_14); 	
		delay_ms(200);
		GPIO_ResetBits(GPIOE,GPIO_Pin_14);
		delay_ms(200);
	
}

void two_liangmie()
{
		//将引脚设置为低电平，亮灯
		GPIO_ResetBits(GPIOF,GPIO_Pin_9); 
		GPIO_ResetBits(GPIOF,GPIO_Pin_10);
	  delay_ms(200);
	
		//将引脚设置为高电平，灭灯
		GPIO_SetBits(GPIOF,GPIO_Pin_9); 			
		GPIO_SetBits(GPIOF,GPIO_Pin_10);
	  delay_ms(200);
	
	  GPIO_ResetBits(GPIOE,GPIO_Pin_13);
	  GPIO_ResetBits(GPIOE,GPIO_Pin_14);
	  delay_ms(200);

		GPIO_SetBits(GPIOE,GPIO_Pin_13); 			
		GPIO_SetBits(GPIOE,GPIO_Pin_14); 	
		delay_ms(200);
	
	
}

void all_liangmie()
{
		//将引脚设置为低电平，亮灯
		GPIO_ResetBits(GPIOF,GPIO_Pin_9); 
		GPIO_ResetBits(GPIOF,GPIO_Pin_10); 
	  GPIO_ResetBits(GPIOE,GPIO_Pin_13);
	  GPIO_ResetBits(GPIOE,GPIO_Pin_14);
	  delay_ms(200);
	
		//将引脚设置为高电平，灭灯
		GPIO_SetBits(GPIOF,GPIO_Pin_9); 			
		GPIO_SetBits(GPIOF,GPIO_Pin_10); 					
		GPIO_SetBits(GPIOE,GPIO_Pin_13); 			
		GPIO_SetBits(GPIOE,GPIO_Pin_14); 	
		delay_ms(200);
}

void pattern()
{
	KeyScan();
	if(flag1) {
		
		while(flag1)  //key0  (流水灯1)
		{
			liushuideng1();
			
			KeyScan();
			if(flag2 || flag3 || flag4) { flag1=0; return;}
		}				
	}

	if(flag2) {
		//将引脚设置为低电平，亮灯
		GPIO_ResetBits(GPIOF,GPIO_Pin_9); 
		GPIO_ResetBits(GPIOF,GPIO_Pin_10); 
	  GPIO_ResetBits(GPIOE,GPIO_Pin_13);
	  GPIO_ResetBits(GPIOE,GPIO_Pin_14);
		
		while(flag2)  //key1  (流水灯2)
		{
			liushuideng2();

			
			KeyScan();
			if(flag1 || flag3 || flag4) { flag2=0;}
		}				
	}	
	
	if(flag3) {
		//将引脚设置为高电平，灭灯
		GPIO_SetBits(GPIOF,GPIO_Pin_9); 			
		GPIO_SetBits(GPIOF,GPIO_Pin_10); 					
		GPIO_SetBits(GPIOE,GPIO_Pin_13); 			
		GPIO_SetBits(GPIOE,GPIO_Pin_14); 
		
		while(flag3)  //key2  (2灯亮灭)
		{

			two_liangmie();
			
			KeyScan();
			if(flag1 || flag2 || flag4) { flag3=0;} 
		}				
	}	

	if(flag4) {
		//将引脚设置为高电平，灭灯
		GPIO_SetBits(GPIOF,GPIO_Pin_9); 			
		GPIO_SetBits(GPIOF,GPIO_Pin_10); 					
		GPIO_SetBits(GPIOE,GPIO_Pin_13); 			
		GPIO_SetBits(GPIOE,GPIO_Pin_14); 
		
		while(flag4)  //key3  (所有灯亮灭)
		{

			all_liangmie();
			
			KeyScan();
			if(flag1 || flag2 || flag3) { flag4=0;}
		}				
	}
	
}


int main(void)
{

	
  LedInit();
	KeyInit();
	
	//灭灯状态
	GPIO_SetBits(GPIOF,GPIO_Pin_9); 
	GPIO_SetBits(GPIOF,GPIO_Pin_10); 
	GPIO_SetBits(GPIOE,GPIO_Pin_13); 
	GPIO_SetBits(GPIOE,GPIO_Pin_14); 
	delay_ms(5);
	
	while(1)
	{	
     pattern(); 
	}
	
}
