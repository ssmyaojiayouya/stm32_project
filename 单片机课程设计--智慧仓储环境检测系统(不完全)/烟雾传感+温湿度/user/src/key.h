#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f4xx.h"
//结构体初始化
static GPIO_InitTypeDef GPIO_InitStructure;
static EXTI_InitTypeDef EXTI_InitStructure;
static NVIC_InitTypeDef NVIC_InitStructure;

void Key_Init(void);
void Extern_Init(void);

#endif /*__KEY_H__*/
