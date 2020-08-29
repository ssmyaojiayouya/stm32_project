#ifndef __LED_H__
#define __LED_H__
#include "stm32f4xx.h"
//灯的编号的宏
enum LED_NUM{LED_D1,LED_D2,LED_D3,LED_D4,LED_D5,LED_D6,LED_D7,LED_D8};


//灯的操作
#define LED_ON  1  //开灯
#define LED_OFF 0  //关灯

/*
	led_init:初始化LED灯的引脚
	参数：
		无
	返回值：
		无
*/
void led_init(void);

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

void led_ctl(int LedN, int OnOff);


/*
	all_led_ctl:根据LedState的每一位控制对应的LED的状态
	@LedState: LedState的低4位表示D1、D2、D3、D4的状态
	返回值:
		无
*/
void all_led_ctl(u8 LedState);

#endif
