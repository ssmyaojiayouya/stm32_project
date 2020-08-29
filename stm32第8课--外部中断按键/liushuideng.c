#include "myhead.h"

void liushuideng1(void)
{
	
	//获取GPIO的ODR寄存器地址  
	uint32_t PF_ODR = GPIOF_BASE + 0x14;
	
	uint32_t PE_ODR = GPIOE_BASE + 0x14;
	
	//转换位别名地址，用于方便操作PF9引脚
	uint32_t *PF9_BitBand = (uint32_t *)(0x42000000+(PF_ODR - 0x40000000)*8*4 + 9*4);
	uint32_t *PF10_BitBand = (uint32_t *)(0x42000000+(PF_ODR - 0x40000000)*8*4 + 10*4);
	uint32_t *PE13_BitBand = (uint32_t *)(0x42000000+(PE_ODR - 0x40000000)*8*4 + 13*4);
	uint32_t *PE14_BitBand = (uint32_t *)(0x42000000+(PE_ODR - 0x40000000)*8*4 + 14*4);
	
	   *PF9_BitBand ^= 1; //位或实现翻转亮灭
		 delay_ms21(100);
		 *PF9_BitBand ^= 1; //位或实现翻转亮灭
		 delay_ms21(100);
		
		 *PF10_BitBand ^= 1; //位或实现翻转亮灭
		 delay_ms21(100);
		 *PF10_BitBand ^= 1; //位或实现翻转亮灭
		 delay_ms21(100);
		
		 *PE13_BitBand ^= 1; //位或实现翻转亮灭
		 delay_ms21(100);
		 *PE13_BitBand ^= 1; //位或实现翻转亮灭
		 delay_ms21(100);		
		
		 *PE14_BitBand ^= 1; //位或实现翻转亮灭
		 delay_ms21(100);
		 *PE14_BitBand ^= 1; //位或实现翻转亮灭
		 delay_ms21(100);
}



void liushuideng2(void)
{

		//led灯交替亮灭

	   PFout(9) = 0; 
		 delay_ms21(100);
		 PFout(9) = 1; 
		 
		
	   PFout(10) = 0; 
		 delay_ms21(100);
		 PFout(10) = 1; 
		 
		
	   PEout(13) = 0; 
		 delay_ms21(100);
		 PEout(13) = 1; 
		 
		
	   PEout(14) = 0; 
		 delay_ms21(100);
		 PEout(14) = 1; 
		 
}

void two_liangmie(void)
{
		//将引脚设置为低电平，亮灯
		GPIO_ResetBits(GPIOF,GPIO_Pin_9); 
		GPIO_ResetBits(GPIOF,GPIO_Pin_10);
	  delay_ms21(100);
	
		//将引脚设置为高电平，灭灯
		GPIO_SetBits(GPIOF,GPIO_Pin_9); 			
		GPIO_SetBits(GPIOF,GPIO_Pin_10);
	  delay_ms21(100);
	
		GPIO_ResetBits(GPIOE,GPIO_Pin_13);
		GPIO_ResetBits(GPIOE,GPIO_Pin_14);
	  delay_ms21(100);

		GPIO_SetBits(GPIOE,GPIO_Pin_13); 			
		GPIO_SetBits(GPIOE,GPIO_Pin_14); 	
		delay_ms21(100);
	
	
}

void all_liangmie(void)
{
		//将引脚设置为低电平，亮灯
		GPIO_ResetBits(GPIOF,GPIO_Pin_9); 
		GPIO_ResetBits(GPIOF,GPIO_Pin_10); 
	  GPIO_ResetBits(GPIOE,GPIO_Pin_13);
	  GPIO_ResetBits(GPIOE,GPIO_Pin_14);
	  delay_ms21(100);
	
		//将引脚设置为高电平，灭灯
		GPIO_SetBits(GPIOF,GPIO_Pin_9); 			
		GPIO_SetBits(GPIOF,GPIO_Pin_10); 					
		GPIO_SetBits(GPIOE,GPIO_Pin_13); 			
		GPIO_SetBits(GPIOE,GPIO_Pin_14); 	
		delay_ms21(100);
}


