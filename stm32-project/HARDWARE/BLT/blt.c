#include "blt.h"

void Blt_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PB端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;    		  //下拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 	
	
}











