#ifndef __CONTROL_H
#define __CONTROL_H

#include "sys.h"

/*发送key缓存区数据的延时时间，太快上位机接收不到，不知道原因*/
#define SEND_DELAY_TIME 2800

//结构体定义
typedef struct 
{
	u8 pointer;
	u8 last_pointer;
	u8 key_buf[7];
	u16 key_time[7];
} key_t;

//外部声明
extern key_t hey_key;
extern u16 sys_ticks;
extern u8 smg_flag;
extern u8 sending_flag;
extern u8 connect_flag;
extern u8 flag1;
extern u8 flag2;
extern u8 flag3;
extern u8 flag4;
extern u8 flag5;
extern u8 flag6;
extern u8 flag7;

//函数声明
void init(void);
void Clear_Buf(void);
void New_Round(void);
void Send_Key_Buf(void);
void Usart2_New_Rev(void);
void Key_Buf_Save(u8 k);


#endif

