#ifndef _PLL_H_
#define _PLL_H_
#include <hidef.h>     
#include "derivative.h"

void init_pll()
{
    CLKSEL_PLLSEL=0;
    PLLCTL_PLLON=1;
    SYNR=0X40|0X03;
    REFDV=0X80|0x01;
    
    POSTDIV=0X00;
    _asm(nop);
    while(!(CRGFLG_LOCK==1));  //频率误差不在允许范围内，则进入循环，等待稳定后锁相环频率锁定

    CLKSEL_PLLSEL=1; 
}
#endif