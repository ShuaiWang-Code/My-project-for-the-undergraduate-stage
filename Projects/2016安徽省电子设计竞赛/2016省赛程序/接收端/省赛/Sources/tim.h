#ifndef _TIM_H_
#define _TIM_H_
#include <hidef.h>     
#include "derivative.h"

void Init_ECT0(void)  //输入捕捉初始化  T7口接超声波echo
{     
      TSCR1_TFFCA = 1;  // 定时器标志位快速清除
      TSCR1_TEN = 1; 
      TSCR2=0x05;     //禁止溢出中断，分频系数32     周期 1us
      TIOS_IOS0=0;      //PT7为输入捕捉
      TIOS_IOS2=0;
      TCTL4=0x13;     //输入捕捉7上升沿和下降沿均有效               
      TIE_C0I=1;      //通道7输入捕捉中断允许 
      TIE_C2I=1;            
      TSCR1=0x80;     //使能定时器
      TFLG1 = 0xff;	    // 清除各IC/OC中断标志位 写1清除
      TFLG2 = 0xff;     // 清除定时器中断标志位  写1清除
}
void Init_ECT2(void)  //输入捕捉初始化  T7口接超声波echo
{     
      TSCR1_TFFCA = 1;  // 定时器标志位快速清除
      TSCR1_TEN = 1; 
      TSCR2=0x05;     //禁止溢出中断，分频系数32     周期 1us
      TIOS_IOS2=0;      //PT7为输入捕捉
      TCTL4=0x30;     //输入捕捉7上升沿和下降沿均有效               
      TIE_C2I=1;      //通道7输入捕捉中断允许             
      TSCR1=0x80;     //使能定时器
      TFLG1 = 0xff;	    // 清除各IC/OC中断标志位 写1清除
      TFLG2 = 0xff;     // 清除定时器中断标志位  写1清除
}

#endif