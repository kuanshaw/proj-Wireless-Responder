#include "key.h"


// ������ʼ������
//
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	// ��������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��PB�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;    		  //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB 	
	
	// �����ж���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);
	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	// �����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�2�� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); 
}


//����ɨ�躯��
//��������
//����ֵ�����ذ�����ֵ���ް����򷵻�0
u8 Key_Scan(void)
{
	if(KEY_1==1||KEY_2==1||KEY_3==1||KEY_4==1||KEY_5==1||KEY_6==1||KEY_7==1)
	{
		delay_ms(10);										//��ֹ����

		if(flag1&&KEY_1==1){
			flag1=0;											//һ������һ���غ��У�ֻ�ܰ�һ�Σ�����֮�������
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


//�жϴ�����
//����PA6
void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY_RENEW==1)	 	 //WK_UP����
	{
		New_Round();
	}
	EXTI_ClearITPendingBit(EXTI_Line6); //���LINE0�ϵ��жϱ�־λ  
}



