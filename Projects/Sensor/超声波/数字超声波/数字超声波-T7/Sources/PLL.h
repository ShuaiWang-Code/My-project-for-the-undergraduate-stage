#ifndef _PLL_H_
#define _PLL_H_
#include <hidef.h>     
#include "derivative.h"

void Init_PLL(void) 
{
    CLKSEL_PLLSEL=0;          //��ʹ�����໷ʱ��
    PLLCTL_PLLON=1;           //�������໷
    SYNR=0x40|0x03;           //voc_clock=2*osc_clock*(1+SYNR)/(1+REFDV)=2*16*(1+4)/(1+1)=80MHz                                   
    REFDV=0x80|0x01;          //ref_clock=osc_clock/(REDFDV+1)=16/(1+1)=8MHz 

        
    POSTDIV=0x00;             //pll_clock=voc_clock
    _asm(nop);                //������ʱ���ȴ�ʱ��Ƶ���ȶ�
    _asm(nop);
    while(!(CRGFLG_LOCK==1))  //Ƶ����������Χ�ڣ������ѭ�����ȴ��ȶ������໷Ƶ������
    {
      ;
    }
    CLKSEL_PLLSEL=1;          //ʹ�����໷

}




#endif