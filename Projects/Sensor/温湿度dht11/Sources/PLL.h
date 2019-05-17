#ifndef _PLL_H_
#define _PLL_H_
#include <hidef.h>     
#include "derivative.h"
void PLL_init(void)      //80M
{
    CLKSEL_PLLSEL =0;
    PLLCTL_PLLON  =1;
    SYNR    = 0XC0 | 0X09;
    REFDV   = 0X80 | 0X01;
    POSTDIV = 0X00;
    _asm(nop); //BUS CLOCK=80M
    _asm(nop);
    while(!(CRGFLG_LOCK==1)); //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;  
}
#endif
