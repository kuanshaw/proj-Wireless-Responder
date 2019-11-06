#include "control.h"


// 变量定义
/*系统时钟标准，每隔1ms加一；在第一个按键按下时清零；在新一轮回 *
 *合开始后如此重复；16位，最大为65535，若按键buf中上一个按键的时*
 *间值比现在检测到的按键时间值大，则加上65535。									*/
u16 sys_ticks=0;

/*数码管显示标志位；当第一个按键按下后，给数码管上锁，使其显示第一位
	按键值，在新一回合开始时清零																	*/
u8 smg_flag=1;

/*定义一个按键缓存结构体																				*/
key_t hey_key;

/*数据发送中标志，避免其他中断冲突数据的发送										*/
u8 sending_flag=0;

/*上位机连接标志																								*/
u8 connect_flag=1;

/*7个按键（实际只用6个）的按下标志位，作用是让每个按键每一个回合只能
	按下一次																											*/
u8 flag1=1;
u8 flag2=1;
u8 flag3=1;
u8 flag4=1;
u8 flag5=1;
u8 flag6=1;
u8 flag7=1;


//初始化函数
void init(void)
{
	Led_Init();
	delay_init();
	Key_Init();
	uart_init(38400);
	Beep_Init();
	usart2_init(38400);
	TIM3_Init(9, 7199);		//1ms中断一次
	Blt_Init();
	Beep_Init();
	Smg_Init();
	Smg_Show(0);
}


// 新一轮准备函数
// 
void New_Round(void)
{
	if(KEY_1==1||KEY_2==1||KEY_3==1||KEY_4==1||KEY_5==1||KEY_6==1||KEY_7==1)
	{
		Beep_Didi(70, 3);
	}
	else
	{
		flag1=1;
		flag2=1;
		flag3=1;
		flag4=1;
		flag5=1;
		flag6=1;
		flag7=1;
		
		sys_ticks=0;
		Clear_Buf();
		Beep_Didi(20, 2);
		Smg_Show(0);
		smg_flag=1;
	}
}


//清空Key缓存区
//
void Clear_Buf(void)
{
	int i;
	hey_key.pointer=0;
	hey_key.last_pointer=0;
	for(i=0; i<7; i++)
	{
		hey_key.key_buf[i]=0;
		hey_key.key_time[i]=0;
	}
}


//发送按键的存储结构体
//无参数
//无返回值
void Send_Key_Buf(void)
{
	u8 i;
	sending_flag=1;
	
	USART2_TX_BUF[0] = 0xA5;
	USART2_TX_BUF[1] = 0x5A;
	
	for(i=0; i<7; i++)
	{
		USART2_TX_BUF[2+3*i] = hey_key.key_buf[i];
		USART2_TX_BUF[3+3*i] = hey_key.key_time[i]>>8;
		USART2_TX_BUF[4+3*i] = hey_key.key_time[i];
	}
	
	USART2_TX_BUF[23] = 0xAA;

	for(i=0; i<24; i++)
	{
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(USART2, USART2_TX_BUF[i]); 
	}
	
	sending_flag=0;
}


//串口2新消息接收处理函数
//
void Usart2_New_Rev(void)
{
	if(USART2_RX_BUF[0]==0xA5 && USART2_RX_BUF[1]==0x5A && USART2_RX_BUF[3]==0xAA)	//数据对齐
	{
		//新一轮指令
		if(USART2_RX_BUF[2]==0x55)
		{
			New_Round();
		}
		//测试指令
		if(USART2_RX_BUF[2]==0x44)		//Test
		{
			Beep_Didi(800, 1);
		}
		//蓝牙串口连接成功指令
		if(USART2_RX_BUF[2]==0x77)
		{
			connect_flag=1;
		}
	}
}


//按键数据保存函数
//参数：按键值
//无返回值
void Key_Buf_Save(u8 k)
{
	if(hey_key.pointer==0)
		sys_ticks=0;
	hey_key.key_buf[hey_key.pointer] = k;
	hey_key.key_time[hey_key.pointer] = sys_ticks;
	hey_key.last_pointer = hey_key.pointer;
	hey_key.pointer++;
}




