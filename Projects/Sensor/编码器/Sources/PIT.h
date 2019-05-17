#ifndef _PIT_H_
#define _PIT_H_
#include <hidef.h>     
#include "derivative.h"  



void Init_PIT(void)//定时中断初始化函数 ，20ms
{
           
   PITCFLMT=0; //定时中断通道关,4 个通道均关闭

   PITCE_PCE0=1;//定时器通道0 使能

   PITMUX_PMUX0=0;//0:8 位定时器0 与16 位定时器共同作用，需设定PITMTLD0 初值
                  //1:8 位定时器1 与16 位定时器共同作用，需设定PITMTLD1 初值

   PITMTLD0=32-1;//8 位定时器0 初值设定，80MHzBusClock 下为1us，设定一次即可
                  //PITMTLD1=160-1;//8 位定时器1 初值设定，80MHzBusClock 下为2us，设定一次即可

   PITLD0=20000-1;//16 位定时器初值设定。time=PITTIME*0.001MS

   PITINTE_PINTE0=1;//1 定时器中断通道0 中断使能
              
   PITCFLMT_PITE=1;//定时器使能,初始化一次即可           
}

#endif