#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "beep.h"
#include "key.h"

/**********************************
*程序功能: 烟雾传感器
*		通过串口2把命令发送到传感器，
*		通过串口1读取烟雾浓度值发送到PC端显示
**********************************/

unsigned char MQcmd[] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
unsigned char LIGHTcmd[] = {0xA5,0x51,0xF6};
unsigned char OTHERcmd[] = {0xA5,0x52,0xF7};
unsigned char MANU_mode[] = {"===================手动模式==================\r\n"};
unsigned char AUTO_mode[] = {"===================自动模式==================\r\n"};
	
unsigned char flag = 0;
unsigned char mode = 0;		//0：自动模式，1：手动模式
//unsigned char CLEARcmd[]  = {"\n\n\n\n\n\n\n\n\n"};

int main()
{
	Led_Init();
	Beep_Init();
	Key_Init();
	Extern_Init();
	usart1_init(9600);
	usart2_init(9600);
	usart3_init(9600);
	
	while(1)
	{	
		USART_SendDatas(USART2,MQcmd,sizeof(MQcmd));
		delay_ms(200);
		
		USART_SendDatas(USART3,LIGHTcmd,sizeof(LIGHTcmd));
		delay_ms(200);
		
		USART_SendDatas(USART3,OTHERcmd,sizeof(OTHERcmd));
		delay_ms(200);
		if(mode == 0)
		{
			Warming();
			USART_SendDatas(USART1,AUTO_mode,strlen((char *)AUTO_mode));
		}
		else
		{
			USART_SendDatas(USART1,MANU_mode,strlen((char *)MANU_mode));
		}

		delay_ms(2000);
		//USART_SendDatas(USART1,CLEARcmd,strlen((char *)CLEARcmd));
		//delay_ms(100);
	}
}

//按键1:模式选择
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		mode ^= 1;
		//清空标志位，告诉CPU我已经处理完中断请求，可以触发下一次中断
		delay_ms(500);
		EXTI_ClearITPendingBit(EXTI_Line0);
		
	}
}

//按键2：手动模式报警器开关
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) == SET)
	{
		if(mode == 1)
		{		
			//如果警报是关闭的
			if(PFout(8) == 0)
			{
				//flag = 1;		//灯闪烁信号
				PFout(8) = 1;	//打开警报
				PFout(9) = 0;	
				PFout(10) = 0;
				PEout(13) = 0;
				PEout(14) = 0;
			}
			else
			{
				//flag = 0;		//灯闪烁信号置0
				PFout(8) = 0;	//关闭警报
				PFout(9) = 1;	
				PFout(10) = 1;
				PEout(13) = 1;
				PEout(14) = 1;
			}
		}
		delay_ms(500);
		//清空标志位，告诉CPU我已经处理完中断请求，可以触发下一次中断
		EXTI_ClearITPendingBit(EXTI_Line2);
		
	}
}
