#ifndef __CONTROL_H
#define __CONTROL_H

#include "sys.h"

/*����key���������ݵ���ʱʱ�䣬̫����λ�����ղ�������֪��ԭ��*/
#define SEND_DELAY_TIME 2800

//�ṹ�嶨��
typedef struct 
{
	u8 pointer;
	u8 last_pointer;
	u8 key_buf[7];
	u16 key_time[7];
} key_t;

//�ⲿ����
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

//��������
void init(void);
void Clear_Buf(void);
void New_Round(void);
void Send_Key_Buf(void);
void Usart2_New_Rev(void);
void Key_Buf_Save(u8 k);


#endif

