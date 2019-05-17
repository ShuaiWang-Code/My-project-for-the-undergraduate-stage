#ifndef _PLL_H_
#define _PLL_H_
#include <hidef.h>     
#include "derivative.h"

void Init_PLL(void) 
{
    CLKSEL_PLLSEL=0;          //不使能锁相环时钟
    PLLCTL_PLLON=1;           //启动锁相环
    SYNR=0x40|0x03;           //voc_clock=2*osc_clock*(1+SYNR)/(1+REFDV)=2*16*(1+4)/(1+1)=80MHz                                   
    REFDV=0x80|0x01;          //ref_clock=osc_clock/(REDFDV+1)=16/(1+1)=8MHz 

        
    POSTDIV=0x00;             //pll_clock=voc_clock
    _asm(nop);                //短暂延时，等待时钟频率稳定
    _asm(nop);
    while(!(CRGFLG_LOCK==1))  //频率误差不在允许范围内，则进入循环，等待稳定后锁相环频率锁定
    {
      ;
    }
    CLKSEL_PLLSEL=1;          //使能锁相环

}




#endif