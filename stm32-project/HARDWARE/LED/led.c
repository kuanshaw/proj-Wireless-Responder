#include "led.h"


//��ʼ������
//
void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}


//LED��˸����
//��������ʱʱ�䵥λms
//�޷���ֵ
void Led_Flash(int time)
{
	static int count=0;
	count++;
	if(count==time)
	{
		count=0;
		LED=~LED;
	}
}


