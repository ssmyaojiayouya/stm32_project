#ifndef __USART_H__
#define __USART_H__

#include "stm32f4xx.h"
#include "bitband.h"
#include "led.h"

static uint32_t values = 0;
static uint8_t SendBuf[32] = {0};

extern void usart1_init(uint32_t BaudRate);
extern void usart2_init(uint32_t BaudRate);//PA2£¬PA3
extern void usart3_init(uint32_t BaudRate);

extern void USART_SendDatas(USART_TypeDef * USARTx,uint8_t *SendBuf,uint16_t len);
extern void USART1_IRQHandler(void);
extern void USART2_IRQHandler(void);
extern void USART3_IRQHandler(void);

u8 SUM_Check(u8 *dataBuf, u8 n);

#endif /*__USART_H__*/
