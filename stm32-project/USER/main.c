#include "sys.h"


// ������
int main(void)
{	
	u8 key;
	//��ʼ��
	init();
	//�ж����ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Clear_Buf();
	
	while(1)
	{	
		// �ж��Ƿ�����״̬
		if(BLT_STATE&&connect_flag)
		{			
			New_Round();
			Beep_Didi(120, 2);
			connect_flag=0;	
		}
		
		// ���Ͱ�����Ϣ
		if(BLT_STATE && hey_key.pointer!=0 && sys_ticks%2800==0 && sending_flag==0)
		{
			Send_Key_Buf();
		}
		
		key=Key_Scan();
		if(key)
		{	
			if(BLT_STATE)
			{
				Key_Buf_Save(key);
				if(smg_flag)
				{
					Smg_Show(key);
					smg_flag=0;
				}
			}
			else
			{
				Beep_Didi(70, 3);	
			}
		}
		
		//��Ϣ����
		if(USART2_RX_STA&0x8000)
		{
			Usart2_New_Rev();
			USART2_RX_STA=0;
		}
	}
}


