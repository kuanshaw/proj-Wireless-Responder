#ifndef __BEEP_H
#define __BEEP_H

#include "sys.h"

//º¯ÊıÉùÃ÷
void Beep_Init(void);
void Beep_Didi(int delaytime, int num);

#define BEEP  PAout(5)

#endif


