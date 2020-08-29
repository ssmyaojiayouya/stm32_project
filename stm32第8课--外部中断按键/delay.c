#include "myhead.h"

void delay_ms168(uint32_t n)
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


void delay_ms21(uint32_t n)
{
  while(n--) {
		SysTick->CTRL = 0; // 关闭定时器		
		SysTick->LOAD = (21000000/1000); //1ms
		SysTick->VAL = 0; // 清除标志位
		SysTick->CTRL = 1; // 使能定时器工作，开始计数，寄存器（21M）
		
		while ((SysTick->CTRL & 0x00010000)==0);// 等待定时器计数完毕
		SysTick->CTRL = 0; // 关闭定时器				
	}
	

}


//微妙延时
void delay_us21(uint32_t n)
{
  while(n--) {
		SysTick->CTRL = 0; // 关闭定时器		
		SysTick->LOAD = (21); //1ms
		SysTick->VAL = 0; // 清除标志位
		SysTick->CTRL = 1; // 使能定时器工作，开始计数，寄存器（21M）
		
		while ((SysTick->CTRL & 0x00010000)==0);// 等待定时器计数完毕
		SysTick->CTRL = 0; // 关闭定时器				
	}
	

}


