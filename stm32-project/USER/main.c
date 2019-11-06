#include "sys.h"


// 主函数
int main(void)
{	
	u8 key;
	//初始化
	init();
	//中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Clear_Buf();
	
	while(1)
	{	
		// 判断是否连接状态
		if(BLT_STATE&&connect_flag)
		{			
			New_Round();
			Beep_Didi(120, 2);
			connect_flag=0;	
		}
		
		// 发送按键信息
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
		
		//消息接收
		if(USART2_RX_STA&0x8000)
		{
			Usart2_New_Rev();
			USART2_RX_STA=0;
		}
	}
}


