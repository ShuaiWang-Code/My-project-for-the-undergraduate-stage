#ifndef _PAC_H_
#define _PAC_H_
#include <hidef.h>     
#include "derivative.h"

void Init_PAC(void)
{
 PACTL=0X40;
 PACNT=0X00;
}

#endif 