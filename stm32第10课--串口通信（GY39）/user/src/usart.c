#include "usart.h"
#include "bitband.h"
#include "led.h"

void usart1_init(uint32_t BaudRate)	//带波特率参数
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	//使能GPIOA的时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 

	//GPIO初始化为输出推挽模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;  		//功能复用模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;		//推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOA, &GPIO_InitStruct); 
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10, GPIO_AF_USART1);	//此处不能用或操作合并
	
	//USART配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); 

	//GPIO初始化为输出推挽模式
	USART_InitStruct.USART_BaudRate = BaudRate;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  	//无硬件流
	USART_InitStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;		//发送接收模式
	USART_InitStruct.USART_Parity = USART_Parity_No;				//无校验位
	USART_InitStruct.USART_StopBits = USART_StopBits_1;   			//1bit停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; 		//8bits数据位
	USART_Init(USART1, &USART_InitStruct); 
	
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);		//设置来数据可以引发中断
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			//设置外部中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//指定抢占优先级0-15
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;		//指定子优先级即响应优先级0-15
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能
	NVIC_Init(&NVIC_InitStructure);	//中断优先级得配置，中断使能
	
	USART_Cmd(USART1, ENABLE);		//打开串口
}


void usart2_init(uint32_t BaudRate)//PA2，PA3
{
	GPIO_InitTypeDef    GPIO_InitStructure;
	USART_InitTypeDef   USART_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	//1.GPIO口配置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能 GPIOA 时钟

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //功能复用模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽模式，增加驱动能力
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; // 第2，3号引脚
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 没有上下拉电阻（输入悬空）
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;// 引脚的最大工作速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//选择具体的复用功能
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2 复用为 USART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3 复用为 USART2	
	
	
	// 2.USART配置
	//a.使能USART时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //使能 USART2 时钟
	
	//b.USART初始化	
	USART_InitStructure.USART_BaudRate = BaudRate; //波特率设置
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式	
	USART_InitStructure.USART_Parity = USART_Parity_No; //无奇偶校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //一个停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //字长为 8 位数据格式
	USART_Init(USART2, &USART_InitStructure);	
	

	//3.中断配置	
	//a.配置可以由哪些事件引起中断
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //开启相关中断(设置来数据可以引发中断)
	
	//b.Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //设置串口 2 中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //中断通道使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; //抢占优先级 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //子（响应）优先级 
	NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化 VIC 寄存器


	//4.打开串口
	USART_Cmd(USART2, ENABLE); //使能串口 2	
	
}

void usart3_init(uint32_t BaudRate)//PB10，PB11
{
	GPIO_InitTypeDef    GPIO_InitStructure;
	USART_InitTypeDef   USART_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	//1.GPIO口配置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能 GPIOB 时钟

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //功能复用模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽模式，增加驱动能力
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; // 第2，3号引脚
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 上拉电阻
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;// 引脚的最大工作速度
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//选择具体的复用功能
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource2,GPIO_AF_USART3); //GPIOB10 复用为 USART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_USART3); //GPIOB11 复用为 USART3	
	
	
	// 2.USART配置
	//a.使能USART时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //使能 USART3 时钟
	
	//b.USART初始化	
	USART_InitStructure.USART_BaudRate = BaudRate; //波特率设置
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式	
	USART_InitStructure.USART_Parity = USART_Parity_No; //无奇偶校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //一个停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //字长为 8 位数据格式
	USART_Init(USART3, &USART_InitStructure);	
	

	//3.中断配置	
	//a.配置可以由哪些事件引起中断
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); //开启相关中断(设置来数据可以引发中断)
	
	//b.Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; //设置串口 3 中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //中断通道使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; //抢占优先级 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //子（响应）优先级 
	NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化 VIC 寄存器


	//4.打开串口
	USART_Cmd(USART3, ENABLE); //使能串口 3	
	
}


//发送数据
void USART_SendDatas(USART_TypeDef * USARTx,uint8_t *SendBuf,uint16_t len)
{
	uint16_t i;
	for(i=0;i<len;i++)
	{
		USART_SendData( USARTx,SendBuf[i]);
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);//等待发送完成
	}
}

//返回求和校验值，校验
u8 SUM_Check(u8 *dataBuf, u8 n)
{
	u8 data = 0, i;

	while(i<n)
	{
		if( i< (n-1) )
		data += dataBuf[i];//累加Length-1前的数据		
	}
	return data;
}




//接收数据
void USART1_IRQHandler(void)
{
	static unsigned char data;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)//由来数据触发中断
	{
		data = USART_ReceiveData(USART1);//读取接收到的数据
		//...数据处理
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);//清除中断标志位
	}
	
}

//串口2的中断处理函数
void USART2_IRQHandler(void)
{
	static unsigned char dataBuf[9]={0},i=0;//定义静态局部变量		
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)//由来数据触发中断
	{
		GPIO_ResetBits(GPIOF, GPIO_Pin_9);
		dataBuf[i++] = USART_ReceiveData(USART2);//读取接收到的数据
		if(dataBuf[0] != 0xff)//每帧数据的开头必须是0xff
		{
			i=0;
		}
		if(i == 9)//数据接收成功
		{
			i=0;
			if(SUM_Check(dataBuf,9) == dataBuf[8])//检测校验是否正确
			{
				values = dataBuf[2]<<8 | dataBuf[3];
			}
			sprintf((char *)SendBuf, "the value is %d\r\n", values);
			USART_SendDatas(USART1,SendBuf,strlen((char *)SendBuf));
		}
		//...数据处理	
		

		USART_ClearITPendingBit(USART2,USART_IT_RXNE);//清除中断标志位
	}
}






//串口3的中断处理函数
void USART3_IRQHandler(void)
{
	static unsigned char dataBuf[30]={0},i=0,k=0;//定义静态局部变量	
  static unsigned char data,length;	
	if(USART_GetITStatus(USART3,USART_IT_RXNE)==SET)//由来数据触发中断
	{
		GPIO_ResetBits(GPIOF, GPIO_Pin_9);
		dataBuf[i++] = USART_ReceiveData(USART3);//读取接收到的数据
		if(dataBuf[0] != 0x5A || dataBuf[1] != 0x5A)//每帧数据的开头必须是0x5A
		{
			i=0;
		}
		length = dataBuf[3];
		if(i == length+5)//数据接收成功
		{
			i=0;
			if(SUM_Check(dataBuf,length+4) == dataBuf[length+4])//检测校验是否正确
			{
				data = dataBuf[2];
				if(data == 0x82) //持续输出光照强度
				{
					temp = dataBuf[4]<<24 | dataBuf[5]<<16 | dataBuf[6]<<8 | dataBuf[7];
					sprintf((char *)SendBuf, "the temp is %d\r\n", temp);
			    USART_SendDatas(USART1,SendBuf,strlen((char *)SendBuf));
				}
				
			}

		}
	
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);//清除中断标志位
	}
}

