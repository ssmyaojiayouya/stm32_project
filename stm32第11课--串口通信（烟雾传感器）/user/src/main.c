#include "stm32f4xx.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "key.h"
#include "bitband.h"
#include "stdio.h"
#include "string.h"

/**********************************
*程序功能: 烟雾传感器
*		通过串口2把命令发送到传感器，
*		通过串口1读取烟雾浓度值发送到PC端显示
**********************************/

unsigned char ATcmd[] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
int main()
{
	led_init();//在led.c文件里
	GPIO_SetBits(GPIOF, GPIO_Pin_9);
	GPIO_SetBits(GPIOF, GPIO_Pin_10);
	usart1_init(9600);
	usart2_init(9600);

	while(1)
	{	
		USART_SendDatas(USART2,ATcmd,sizeof(ATcmd));
		delay_ms(1000);

	}
}


