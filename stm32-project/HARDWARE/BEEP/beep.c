#include "beep.h"


//初始化函数
//
void Beep_Init(void)		//PA5
{
	GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	BEEP=0;
}


//蜂鸣器响函数
//参数1：延时时间，即频率
//参数2：响的次数
//无返回值
void Beep_Didi(int delaytime, int num)
{
	int i;
	
	for(i=0; i<num; i++)
	{
		BEEP=1;
		delay_ms(delaytime);
		BEEP=0;
		delay_ms(50);
	}
}

