#ifndef __LED_H
#define __LED_H
#include "sys.h"

//LED
#define LED PCout(13)

void Led_Init(void);
void Led_Flash(int time);
#endif




