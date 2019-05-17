#ifndef _PIT_H_
#define _PIT_H_
#include <hidef.h>     
#include "derivative.h"  
#define PITTIME0 1000//设定为1ms 定时
#define PITTIME1 2000//设定为2ms 定时
#define PITTIME2 10000//设定为10ms 定时
#define PITTIME3 40000//设定为40ms 定时
volatile uint count0=0,count1=0,count2=0,count3=0;
//定时器初始化
void PIT_Init(void)//定时中断初始化函数
{
//通道0 初始化,20ms 定时中断设置
PITCFLMT=0; //定时中断通道关,4 个通道均关闭
PITCE_PCE0=1;//定时器通道0 使能
PITMUX_PMUX0=0;//0:8 位定时器0 与16 位定时器共同作用，需设定PITMTLD0 初值
//1:8 位定时器1 与16 位定时器共同作用，需设定PITMTLD1 初值
PITMTLD0=80-1;//8 位定时器0 初值设定，80MHzBusClock 下为1us，设定一次即可
//PITMTLD1=160-1;//8 位定时器1 初值设定，80MHzBusClock 下为2us，设定一次即可
PITLD0=PITTIME0-1;//16 位定时器初值设定。time=PITTIME*0.001MS
PITINTE_PINTE0=1;//1 定时器中断通道0 中断使能
//PITCFLMT_PITE=1;//定时器使能,初始化一次即可
//通道1 初始化,40ms 定时中断设置
//PITCFLMT_PITE=0; //定时中断通道关，4 个通道均关闭
PITCE_PCE1=0;//定时器通道2 使能
PITMUX_PMUX1=0;//0:8 位定时器0 与16 位定时器共同作用，需设定PITMTLD0 初值
//1:8 位定时器1 与16 位定时器共同作用，需设定PITMTLD1 初值
//PITMTLD0=160-1;//8 位定时器初值设定，80MHzBusClock 下，为2us
PITLD1=PITTIME1-1;//16 位定时器初值设定。PITTIME*0.001MS
PITINTE_PINTE1=0;//1 定时器中断通道1 中断使能
//PITCFLMT_PITE=1;//定时器使能,初始化一次即可
//通道2 初始化,60ms 定时中断设置
//PITCFLMT_PITE=0; //定时中断通道关，4 个通道均关闭
PITCE_PCE2=0;//定时器通道2 使能
PITMUX_PMUX2=0;//0:8 位定时器0 与16 位定时器共同作用，需设定PITMTLD0 初值
//1:8 位定时器1 与16 位定时器共同作用，需设定PITMTLD1 初值
//PITMTLD0=160-1;//8 位定时器初值设定，80MHzBusClock 下，为2us
PITLD2=PITTIME2-1;//16 位定时器初值设定。PITTIME*0.001ms
PITINTE_PINTE2=0;//1 定时器中断通道2 中断使能
//PITCFLMT_PITE=1;//定时器使能,初始化一次即可
//通道3 初始化,80ms 定时中断设置
//PITCFLMT_PITE=0; //定时中断通道关，4 个通道均关闭
PITCE_PCE3=0;//定时器通道3 使能
PITMUX_PMUX3=0;//0:8 位定时器0 与16 位定时器共同作用，需设定PITMTLD0 初值
//1:8 位定时器1 与16 位定时器共同作用，需设定PITMTLD1 初值
//PITMTLD0=160-1;//8 位定时器初值设定，80MHzBusClock 下，为2us
PITLD3=PITTIME3-1;//16 位定时器初值设定。PITTIME*0.001ms
PITINTE_PINTE3=0;//1 定时器中断通道3 中断使能
PITCFLMT_PITE=1;//定时器使能,初始化一次即可
}
/*
#pragma CODE_SEG __NEAR_SEG NON_BANKED //指示该程序在不分页区
void interrupt 66 PIT0(void)//定时器0 中断服务函数
{
count0++;
if(count0==50)
{
PORTA_PA0=~PORTA_PA0;//A0 LED 翻转，T=1S
count0=0;
}
PITTF_PTF0=1;//清中断标志位
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED //指示该程序在不分页区
void interrupt 67 PIT1(void)//定时器1 中断服务函数
{
count1++;
if(count1==50)
{
PORTA_PA0=~PORTA_PA0;//A0 LED 翻转,T=2S
count1=0;
}
PITTF_PTF1=1;//清中断标志位
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED //指示该程序在不分页区
void interrupt 68 PIT2(void)//定时器2 中断服务函数
{
count2++;
if(count2==50)
{
PORTA_PA0=~PORTA_PA0;//A0 LED 翻转,T=3S
count2=0;
}
PITTF_PTF2=1;//清中断标志位
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED //指示该程序在不分页区
void interrupt 69 PIT3(void)//定时器3 中断服务函数
{
count3++;
if(count3==50)
{
PORTA_PA0=~PORTA_PA0;//A0 LED 翻转,T=4S
count3=0;
}
PITTF_PTF3=1;//清中断标志位
} 
*/
#endif