#include "delay.h"

void delay_ms(uint16_t nms)
{
	uint32_t tmp;
	int n,m,i,k=500;
	n = nms/500;
	m = nms%500;
	n = (m?n:n-1);
	
	for(i=0;i<n+1;i++)
	{
		if(m && i == n)
		{
			k = m;
		}
		SysTick->LOAD = SystemCoreClock/8/1000*k;//时间加载(SysTick->LOAD为24bits)
		SysTick->VAL = 0x00;
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;//嘀嗒定时器开始倒数使能
		do
		{
			tmp = SysTick->CTRL;
		}while((tmp&0x01) && !(tmp&(1<<16)));//等待时间到达
		SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;//关闭计数器
		SysTick->VAL = 0x00;
	}
}

void delay_us(uint16_t nus)
{
	uint32_t tmp;
	SysTick->LOAD = SystemCoreClock/8/1000000*nus;//时间加载(SysTick->LOAD为24bits)
	SysTick->VAL = 0x00;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;//嘀嗒定时器开始倒数使能
	do
	{
		tmp = SysTick->CTRL;
	}while((tmp&0x01) && !(tmp&(1<<16)));//等待时间到达
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;//关闭计数器
	SysTick->VAL = 0x00;
}
