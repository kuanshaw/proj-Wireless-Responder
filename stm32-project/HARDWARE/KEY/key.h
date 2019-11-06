#ifndef __KEY_H
#define __KEY_H

#include "sys.h"

//7个按键输入的读取
#define KEY_1		PBin(3)
#define KEY_2		PBin(4)
#define KEY_3		PBin(5)
#define KEY_4		PBin(6)
#define KEY_5		PBin(7)
#define KEY_6		PBin(8)
#define KEY_7		PBin(9)

//新一回合按键
#define KEY_RENEW PAin(6)

//按键状态宏定义
#define NO_KEY				0
#define KEY_1_PRES		1
#define KEY_2_PRES		2
#define KEY_3_PRES		3
#define KEY_4_PRES		4
#define KEY_5_PRES		5
#define KEY_6_PRES		6
#define KEY_7_PRES		7
#define KEY_RENEW_PRES	8

//函数声明
void Key_Init(void);
u8 Key_Scan(void);
void EXTI9_5_IRQHandler(void);
void Clear_Buf(void);

#endif


