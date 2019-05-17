#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>
#pragma LINK_INFO DERIVATIVE "mc9s12xs128"

float AD_result[8];//存放AD转换结果

////////////////////////五路AD初始化///////////////////////////////////////////
void AD_init(void) 
{
 //  ATD0CTL0=0;        //AD转换起始通道为AN0
   ATD0CTL1=0x00;     //允许指定AD口做外部触发输入口8位结果，采样前采样电容不放电 1
   ATD0CTL2=0x40;     //启动AD 标志寄存器快速清零
   ATD0CTL3=0xc0;     //结果右对齐，非FIFO模式，冻结模式继续转换 转换长度8
   ATD0CTL4=0x03;     //0000 0011 -采样时间为 4 个 AD 时钟周期 ,PRS=1,ATDClock=BUSClock/(2*(PRS+1))=8MHz
   ATD0CTL5=0x30;     //通道0  连续转换起始通道为AN0
   ATD0DIEN=0x00;     //禁用数字输入缓冲  
} 
///////////////////读取AD值///////////////////////
void get_ad(void) 
{
  AD_result[0]=ATD0DR0L;
  AD_result[1]=ATD0DR1L;
  AD_result[2]=ATD0DR2L;
  AD_result[3]=ATD0DR3L;
  AD_result[4]=ATD0DR4L;
  AD_result[5]=ATD0DR5L;
  AD_result[6]=ATD0DR6L;
  AD_result[7]=ATD0DR7L;
}