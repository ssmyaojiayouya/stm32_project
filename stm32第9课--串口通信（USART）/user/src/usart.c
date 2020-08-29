#include "usart.h"


void usart1_init(uint32_t BaudRate)
{
	GPIO_InitTypeDef    GPIO_InitStructure;
	USART_InitTypeDef   USART_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
	
   /**  1.GPIO口配置	   **/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能 GPIOA 时钟

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //功能复用模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽模式，增加驱动能力
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10; // 第9，10号引脚
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 没有上下拉电阻（输入悬空）
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;// 引脚的最大工作速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//选择具体的复用功能
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9 复用为 USART1
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10 复用为 USART1	
	
	
	/**  2.USART配置	   **/
	//a.使能USART时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); //使能 USART1 时钟
	
	//b.USART初始化	
	USART_InitStructure.USART_BaudRate = BaudRate; //波特率设置
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式	
	USART_InitStructure.USART_Parity = USART_Parity_No; //无奇偶校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //一个停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //字长为 8 位数据格式
	USART_Init(USART1, &USART_InitStructure);	
	

	/**  3.中断配置	   **/
	//a.配置可以由哪些事件引起中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开启相关中断(设置来数据可以引发中断)
	
	//b.Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //设置串口 1 中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //中断通道使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; //抢占优先级 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //子（响应）优先级 
  NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化 VIC 寄存器


  /**  4.打开串口	   **/
	USART_Cmd(USART1, ENABLE); //使能串口 1	
	
}

void USART_SendDatas(USART_TypeDef * USARTx,uint8_t *SendBuf,uint16_t len)
{
	uint16_t i;
	for(i=0;i<len;i++)
	{
		USART_SendData( USARTx,SendBuf[i]);
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);//等待发送完成
	}
}


//串口1的中断处理函数
void USART1_IRQHandler(void)
{
	unsigned int data;		
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)//由来数据触发中断
	{
		data = USART_ReceiveData(USART1);//读取接收到的数据
		//...数据处理
/*		
		if(data == 'A')
		{
			 PFout(9) = 0;
			 PFout(10) = 0; 
			 PEout(13) = 0; 
			 PEout(14) = 0; 
		}
		
		if(data == 'B')
		{
			 PFout(9) = 1;
			 PFout(10) = 1; 
			 PEout(13) = 1; 
			 PEout(14) = 1; 
		}		
*/		
		if(data == 0x00) PFout(9) = 0; 
		if(data == 0xF0) PFout(9) = 1;
		
		if(data == 0x01) PFout(10) = 0; 
		if(data == 0xF1) PFout(10) = 1;
		
		if(data == 0x02) PEout(13) = 0; 
		if(data == 0xF2) PEout(13) = 1;
		
		if(data == 0x03) PEout(14) = 0; 
		if(data == 0xF3) PEout(14) = 1;

		USART_ClearITPendingBit(USART1,USART_IT_RXNE);//清除中断标志位
	}
}

