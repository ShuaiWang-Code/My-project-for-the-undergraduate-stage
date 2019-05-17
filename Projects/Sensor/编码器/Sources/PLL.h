#ifndef _PLL_H_
#define _PLL_H_
#include <hidef.h>     
#include "derivative.h"

void Init_PLL(void)   //BUS CLOCK=32M
{
    CLKSEL_PLLSEL =0;
    PLLCTL_PLLON  =1;
    SYNR    = 0X40 | 0X03;
    REFDV   = 0X80 | 0X01;
    POSTDIV = 0X00;
    _asm(nop); 
    _asm(nop);
    while(!(CRGFLG_LOCK==1)) ;
    CLKSEL_PLLSEL =1; 


}




#endif