#include "smg.h"

//数码管初始化函数
//
void Smg_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	Smg_Clear();
}


//数码管全部熄灭函数
//
void Smg_Clear(void)
{
	SMG1=1;
	SMG2=1;
	SMG3=1;
	SMG4=1;
	SMG5=1;
	SMG6=1;
	SMG7=1;
	SMG8=1;
	SMG14=1;
	SMG15=1;
}


//数码管显示函数
//参数：显示的数值，0~6
//无返回值
void Smg_Show(u8 num)
{
	//消隐
	Smg_Clear();
	switch(num)
	{
		case 0:
			SMG1=0;
			SMG2=0;
			SMG3=0;
			SMG4=0;
			SMG5=0;
			SMG6=0;
			SMG7=0;
			SMG8=0;
			SMG14=1;
			SMG15=1;
			break;
		case 1:
			SMG1=1;
			SMG2=1;
			SMG3=0;
			SMG4=0;
			SMG5=1;
			SMG6=1;
			SMG7=1;
			SMG8=1;
			SMG14=1;
			SMG15=1;
			break;
		case 2:
			SMG1=0;
			SMG2=0;
			SMG3=0;
			SMG4=1;
			SMG5=0;
			SMG6=0;
			SMG7=0;
			SMG8=1;
			SMG14=0;
			SMG15=0;
			break;
		case 3:
			SMG1=0;
			SMG2=0;
			SMG3=0;
			SMG4=0;
			SMG5=0;
			SMG6=0;
			SMG7=1;
			SMG8=1;
			SMG14=0;
			SMG15=0;
			break;
		case 4:
			SMG1=1;
			SMG2=1;
			SMG3=0;
			SMG4=0;
			SMG5=1;
			SMG6=1;
			SMG7=1;
			SMG8=0;
			SMG14=0;
			SMG15=0;
			break;
		case 5:
			SMG1=0;
			SMG2=0;
			SMG3=1;
			SMG4=0;
			SMG5=0;
			SMG6=0;
			SMG7=1;
			SMG8=0;
			SMG14=0;
			SMG15=0;
			break;
		case 6:
			SMG1=0;
			SMG2=0;
			SMG3=1;
			SMG4=0;
			SMG5=0;
			SMG6=0;
			SMG7=0;
			SMG8=0;
			SMG14=0;
			SMG15=0;
			break;
		default:
			SMG1=0;
			SMG2=0;
			SMG3=0;
			SMG4=0;
			SMG5=0;
			SMG6=0;
			SMG7=0;
			SMG8=0;
			SMG14=1;
			SMG15=1;
			break;
	}
}




