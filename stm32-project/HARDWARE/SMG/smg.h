#ifndef __SMG_H
#define __SMG_H

#include "sys.h"

//�ƹ�λ����
#define SMG1 PBout(0)
#define SMG2 PBout(1)
#define SMG3 PBout(10)
#define SMG4 PBout(11)
#define SMG5 PBout(12)
#define SMG6 PBout(13)
#define SMG7 PBout(14)
#define SMG8 PBout(15)
#define SMG14 PCout(14)
#define SMG15 PCout(15)

//��������
void Smg_Init(void);
void Smg_Clear(void);
void Smg_Show(u8 num);


#endif


