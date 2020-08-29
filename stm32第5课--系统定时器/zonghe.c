#include "stm32f4xx.h"


static  GPIO_InitTypeDef  GPIO_InitStructure;

void delay()
{
	uint32_t i = 0x1000000;
	
	while(i--);
}

void initLED()
{
	
	/* GPIOG Peripheral clock enable---使能端口F,E时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOE, ENABLE);

	/* Configure PG6 and PG8 in output pushpull mode----配置端口F,E功能 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_13 | GPIO_Pin_14; //第9,10,13,14号引脚
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽模式，增加驱动能力
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 控制IO引脚的最大速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 不需要上下拉电阻
	GPIO_Init(GPIOF, &GPIO_InitStructure);  //使能F端口
	GPIO_Init(GPIOE, &GPIO_InitStructure);  //使能E端口	
	
	// 将引脚设置为高电平,灭灯
    GPIO_SetBits(GPIOF, GPIO_Pin_9|GPIO_Pin_10);
    GPIO_SetBits(GPIOE, GPIO_Pin_13|GPIO_Pin_14);
	
}

int main(void)
{

    initLED();
	
    //初始化系统定时器，1S内核触发1000次中断，说白了定时1ms  （除以1000，就是定时1ms；如果除以1，就是定时1s）
	SysTick_Config(SystemCoreClock/1000);
	
	while(1)
	{

	}
	
}


//滴答定时器每隔1ms进入此中断服务函数
void SysTick_Handler(void)
{
	//static的作用是只初始化一次
	static uint32_t led1_cnt=0;
	static uint32_t led2_cnt=0;
	static uint32_t led3_cnt=0;
	static uint32_t led4_cnt=0;
	
	led1_cnt++;
	led2_cnt++;
	led3_cnt++;
	led4_cnt++;
	
	
	if(led1_cnt == 100) {
		//100ms交替亮灭led灯
		GPIO_ToggleBits(GPIOF,GPIO_Pin_9);
		led1_cnt = 0;
	}
	
	if(led2_cnt == 330) {
		//330ms交替亮灭led灯
		GPIO_ToggleBits(GPIOF,GPIO_Pin_10);
		led2_cnt = 0;
	}

	if(led3_cnt == 1500) {
		//1500ms交替亮灭led灯
		GPIO_ToggleBits(GPIOE,GPIO_Pin_13);
		led3_cnt = 0;
	}

	if(led4_cnt == 2200) {
		//2200ms交替亮灭led灯
		GPIO_ToggleBits(GPIOE,GPIO_Pin_14);
		led4_cnt = 0;
	}	
	
}











