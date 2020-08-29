#include "usart.h"

void usart1_init(uint32_t BaudRate)	//带波特率参数
{
	//使能GPIOA的时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 

	//GPIO初始化为输出推挽模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  		//功能复用模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10, GPIO_AF_USART1);	//此处不能用或操作合并
	
	//USART配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); 

	//GPIO初始化为输出推挽模式
	USART_InitStructure.USART_BaudRate = BaudRate;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  	//无硬件流
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;		//发送接收模式
	USART_InitStructure.USART_Parity = USART_Parity_No;				//无校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;   			//1bit停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 		//8bits数据位
	USART_Init(USART1, &USART_InitStructure); 
	
	
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

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;			// 第10号引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 		//功能复用模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		// 推挽模式，增加驱动能力
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	// 没有上下拉电阻（输入悬空）
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	// 引脚的最大工作速度
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	//选择具体的复用功能
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10 复用为 USART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11 复用为 USART3	
	
	
	// 2.USART配置
	//a.使能USART时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //使能 USART3 时钟
	
	//b.USART初始化	
	USART_InitStructure.USART_BaudRate = BaudRate; //波特率设置
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx; //收发模式	
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
	USART_Cmd(USART3, ENABLE); //使能串口3	
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

//返回求和校验值,串口2校验
u8 SUM_Check(u8 *dataBuf, u8 n)
{
	u8 data = 0, i;
	for(i = 0; i < n; i++)
	{
		data += dataBuf[i];
	}
	return data;
}

//返回求和校验值，按位取反+1校验.串口3校验
u8 BACK_SUM_Check(u8 *dataBuf, u8 n)
{
	u8 data = 0, i;
	for(i = 1; i < n-1; i++)
	{
		data += dataBuf[i];
	}
	return (~data)+1;
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
	static unsigned char MQ_dataBuf[9]={0},j=0;//定义静态局部变量		
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)//由来数据触发中断
	{
		MQ_dataBuf[j++] = USART_ReceiveData(USART2);//读取接收到的数据
		if(MQ_dataBuf[0] != 0xff)//每帧数据的开头必须是0xff
		{
			j=0;
		}
		if(j == 9)//数据接收成功
		{
			j=0;
			if(BACK_SUM_Check(MQ_dataBuf,9) == MQ_dataBuf[8])//检测校验是否正确
			{
				MQ_value = MQ_dataBuf[2]<<8 | MQ_dataBuf[3];
				sprintf((char *)MQ_SendBuf, "烟雾值:%-5.2f            ", MQ_value);
				USART_SendDatas(USART1,MQ_SendBuf,strlen((char *)MQ_SendBuf));
				/*
				//蜂鸣器和led报警
				if(MQ_value > 70.0)
				{
					USART_SendDatas(USART1,MQ_Warm,strlen((char *)MQ_Warm));
					PFout(8) = 1;
					Led_flash1();
				}
				else
				{
					PFout(8) = 0;
				}
				*/
			}		
		}
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);//清除中断标志位
	}
}

//串口3的中断处理函数
void USART3_IRQHandler(void)
{	
	static unsigned char GY_dataBuf[15]={0},i=0;//定义静态局部变量		
	if(USART_GetITStatus(USART3,USART_IT_RXNE)==SET)//由来数据触发中断
	{
		GY_dataBuf[i++] = USART_ReceiveData(USART3);//读取接收到的数据
		if(i == 2)
		{
			if(GY_dataBuf[0] != 0x5A || GY_dataBuf[1] != 0x5A)//每帧数据的开头必须是0xff
			{
				i=0;
			}
		}
		
		//光照强度
		if(i == 9 && GY_dataBuf[2] == 0x15)//数据接收成功
		{
			i=0;
			if(SUM_Check(GY_dataBuf,8) ==  GY_dataBuf[8])//检测校验是否正确
			{
				light_value = (GY_dataBuf[4]<<24)|(GY_dataBuf[5]<<16)|(GY_dataBuf[6]<<8)| GY_dataBuf[7];
				light_value /= 100.0;
				sprintf((char *)GY_SendBuf, "光照强度：%-5.2f lux\r\n", light_value);
				USART_SendDatas(USART1,GY_SendBuf,strlen((char *)GY_SendBuf));

			}
		}
		
		//温湿度、海拔、气压
		if(i == 15 && GY_dataBuf[2] == 0x45)
		{
			i=0;
			if(SUM_Check(GY_dataBuf,14) ==  GY_dataBuf[14])//检测校验是否正确
			{
				temp_value = (GY_dataBuf[4]<<8)|GY_dataBuf[5];
				temp_value /= 100.0;
				pres_value = (GY_dataBuf[6]<<24)|(GY_dataBuf[7]<<16)|(GY_dataBuf[8]<<8)| GY_dataBuf[9];
				pres_value /= 100.0;
				humi_value = (GY_dataBuf[10]<<8)|GY_dataBuf[11];
				humi_value /= 100.0;
				alti_value = (GY_dataBuf[12]<<8)|GY_dataBuf[13];
				sprintf((char *)GY_SendBuf, "温度：%-5.2f ℃             气压：%-5.2f pa\r\n湿度：%-5.2f %%             海拔：%-5.2f m\r\n\n", temp_value,pres_value,humi_value,alti_value);
				USART_SendDatas(USART1,GY_SendBuf,strlen((char *)GY_SendBuf));
			}
		}
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);//清除中断标志位
	}
}

void Warming()
{
	if(MQ_value>70)
	{
		USART_SendDatas(USART1,MQ_Warm,strlen((char *)MQ_Warm));
		PFout(8) = 1;
		Led_flash1();
	}
	if(light_value>120)
	{
		USART_SendDatas(USART1,LIGHT_Warm,strlen((char *)LIGHT_Warm));
		PFout(8) = 1;
		Led_flash2();
	}
	if(temp_value>35)
	{
		USART_SendDatas(USART1,TEMP_Warm,strlen((char *)TEMP_Warm));
		PFout(8) = 1;
		Led_flash3();
	}
	if(humi_value>80)
	{
		USART_SendDatas(USART1,HUMI_Warm,strlen((char *)HUMI_Warm));
		PFout(8) = 1;
		Led_flash4();
	}
	if(MQ_value<=70 && light_value<=120 && temp_value<=35 && humi_value<=80) 
	{
		PFout(8) = 0;
		PFout(9) = 1;
		PFout(10) = 1;
		PEout(13) = 1;
		PEout(14) = 1;
	}
}
