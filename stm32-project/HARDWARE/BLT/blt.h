#ifndef __BTL_H
#define __BTL_H

#include "sys.h"

/*读取蓝牙的状态输入，连接状态时为高电平，未连接时为低电平*/
#define BLT_STATE		PAin(4)

void Blt_Init(void);


#endif



