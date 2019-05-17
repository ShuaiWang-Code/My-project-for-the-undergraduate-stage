#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>
#pragma LINK_INFO DERIVATIVE "mc9s12xs128"

///////////////////////////×ÜÏßÊ±ÖÓ////////////////////////////////////////
void SetBusCLK_64M(void) 
{ 
    CLKSEL=0X00;                   //disengage PLL to system 
    PLLCTL_PLLON=1;                //turn on PLL 
    SYNR =0xc0 | 0x07; 
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;          //pllclock=2*osc*(1+SYNR)/(1+REFDV)=128MHz; 
    _asm(nop);             //BUS CLOCK=64M 
    _asm(nop); 
    while(!(CRGFLG_LOCK==1));           //when pll is steady ,then use it; 
    CLKSEL_PLLSEL =1;                    //engage PLL to system; 
}                     