#ifndef __DELAY_H_
#define __DELAY_H_

#include "stm32f10x.h"
#include "misc.h"

void Delay_init(void);
void Delay_ms(u16 nms);
void Delay_us(u32 nus);

#endif
