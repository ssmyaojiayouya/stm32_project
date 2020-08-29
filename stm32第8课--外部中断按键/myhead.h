#ifndef _MYHEAD_H
#define _MYHEAD_H


#include "stm32f4xx.h"
#include "stm32f4xx_exti.h"
#include "sys.h"



void delay_ms168(uint32_t n);

void delay_ms21(uint32_t n);

void delay_us21(uint32_t n);

void LedInit(void);
void KeyInit(void);


void EXTI0_Init(void);
/*
void EXTI2_Init(void);
void EXTI3_Init(void);
void EXTI4_Init(void);
*/

void EXTI0_IRQHandler(void);
/*
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
*/

void liushuideng1(void);

void liushuideng2(void);

void two_liangmie(void);

void all_liangmie(void);


#endif 









