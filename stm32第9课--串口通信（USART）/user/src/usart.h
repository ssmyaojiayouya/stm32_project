#ifndef __USART_H__
#define __USART_H__

#include "stm32f4xx.h"
#include "sys.h"

void usart_init(uint32_t BaudRate);

void USART_SendDatas(USART_TypeDef * USARTx,uint8_t *SendBuf,uint16_t len);

#endif







