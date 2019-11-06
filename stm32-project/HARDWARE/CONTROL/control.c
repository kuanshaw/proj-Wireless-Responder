#include "control.h"


// ��������
/*ϵͳʱ�ӱ�׼��ÿ��1ms��һ���ڵ�һ����������ʱ���㣻����һ�ֻ� *
 *�Ͽ�ʼ������ظ���16λ�����Ϊ65535��������buf����һ��������ʱ*
 *��ֵ�����ڼ�⵽�İ���ʱ��ֵ�������65535��									*/
u16 sys_ticks=0;

/*�������ʾ��־λ������һ���������º󣬸������������ʹ����ʾ��һλ
	����ֵ������һ�غϿ�ʼʱ����																	*/
u8 smg_flag=1;

/*����һ����������ṹ��																				*/
key_t hey_key;

/*���ݷ����б�־�����������жϳ�ͻ���ݵķ���										*/
u8 sending_flag=0;

/*��λ�����ӱ�־																								*/
u8 connect_flag=1;

/*7��������ʵ��ֻ��6�����İ��±�־λ����������ÿ������ÿһ���غ�ֻ��
	����һ��																											*/
u8 flag1=1;
u8 flag2=1;
u8 flag3=1;
u8 flag4=1;
u8 flag5=1;
u8 flag6=1;
u8 flag7=1;


//��ʼ������
void init(void)
{
	Led_Init();
	delay_init();
	Key_Init();
	uart_init(38400);
	Beep_Init();
	usart2_init(38400);
	TIM3_Init(9, 7199);		//1ms�ж�һ��
	Blt_Init();
	Beep_Init();
	Smg_Init();
	Smg_Show(0);
}


// ��һ��׼������
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


//���Key������
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


//���Ͱ����Ĵ洢�ṹ��
//�޲���
//�޷���ֵ
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
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART2, USART2_TX_BUF[i]); 
	}
	
	sending_flag=0;
}


//����2����Ϣ���մ�����
//
void Usart2_New_Rev(void)
{
	if(USART2_RX_BUF[0]==0xA5 && USART2_RX_BUF[1]==0x5A && USART2_RX_BUF[3]==0xAA)	//���ݶ���
	{
		//��һ��ָ��
		if(USART2_RX_BUF[2]==0x55)
		{
			New_Round();
		}
		//����ָ��
		if(USART2_RX_BUF[2]==0x44)		//Test
		{
			Beep_Didi(800, 1);
		}
		//�����������ӳɹ�ָ��
		if(USART2_RX_BUF[2]==0x77)
		{
			connect_flag=1;
		}
	}
}


//�������ݱ��溯��
//����������ֵ
//�޷���ֵ
void Key_Buf_Save(u8 k)
{
	if(hey_key.pointer==0)
		sys_ticks=0;
	hey_key.key_buf[hey_key.pointer] = k;
	hey_key.key_time[hey_key.pointer] = sys_ticks;
	hey_key.last_pointer = hey_key.pointer;
	hey_key.pointer++;
}




