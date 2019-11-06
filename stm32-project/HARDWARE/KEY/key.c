#include "key.h"


// 按键初始化函数
//
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	// 配置引脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;    		  //下拉输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 	
	
	// 配置中断线
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);
	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	// 配置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键WK_UP所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级2， 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); 
}


//按键扫描函数
//参数：无
//返回值：返回按键的值，无按键则返回0
u8 Key_Scan(void)
{
	if(KEY_1==1||KEY_2==1||KEY_3==1||KEY_4==1||KEY_5==1||KEY_6==1||KEY_7==1)
	{
		delay_ms(10);										//防止抖动

		if(flag1&&KEY_1==1){
			flag1=0;											//一个按键一个回合中，只能按一次，按下之后就置零
			return KEY_1_PRES;
		}
		else if(flag2&&KEY_2==1){
			flag2=0;
			return KEY_2_PRES;
		}
		else if(flag3&&KEY_3==1){
			flag3=0;
			return KEY_3_PRES;
		}
		else if(flag4&&KEY_4==1){
			flag4=0;
			return KEY_4_PRES;
		}
		else if(flag5&&KEY_5==1){
			flag5=0;
			return KEY_5_PRES;
		}
		else if(flag6&&KEY_6==1){
			flag6=0;
			return KEY_6_PRES;
		}
		else if(flag7&&KEY_7==1){
			flag7=0;
			return KEY_7_PRES;
		}
	}
	return NO_KEY;
}


//中断处理函数
//按键PA6
void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY_RENEW==1)	 	 //WK_UP按键
	{
		New_Round();
	}
	EXTI_ClearITPendingBit(EXTI_Line6); //清除LINE0上的中断标志位  
}



