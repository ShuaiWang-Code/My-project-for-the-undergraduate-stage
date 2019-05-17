#ifndef _AD_H_
#define _AD_H_
#include <hidef.h>     
#include "derivative.h" 
#define _10_bit_mode
#ifdef _8_bit_mode
unsigned char AD_value[8];
//unsigned int flag_ad0,flag_ad1,flag_ad2;
/*ATD 模块初始化*/

void ATD_Init(void)//8bit 模式
{
//八通道AD 循环采样配置如下
ATD0CTL1=0x00; //7:1-外部触发,65:00-8 位精度01-10 位精度，4:放电,3210:通道0
ATD0CTL2=0x40; //禁止外部触发, 中断禁止
ATD0CTL3=0xc0; //7:1 数据右对齐无符号,每次转换8 个序列, No FIFO, Freeze 模式下继续转

ATD0CTL4=0x07; //765: 采样时间为4 个AD 时钟周期,ATDClock=[BusClock*0.5]/[PRS+1]=1MHz(BusClock=80MHz)

ATD0CTL5=0x30; //6:0 特殊通道禁止,5:1 连续转换0 单次转换 ,4:1 多通道轮流采样3210:第一通道指定

ATD0DIEN=0x00; //禁止数字输入
//使用一个通道采集配置如下
/*
ATD0CTL1=0x20; //7:1-外部触发,65:00-10 位精度,4:放电,3210:ch
ATD0CTL2=0x40; //禁止外部触发, 中断禁止
ATD0CTL3=0x88; //右对齐无符号,每次转换1 个序列, No FIFO, Freeze 模式下继续转
// ATD0CTL3=0xc0; //右对齐无符号,每次转换8 个序列, No FIFO, Freeze 模式下继续转
ATD0CTL4=0x07; //765: 采样时间为4 个AD 时钟周期,ATDClock=[BusClock*0.5]/[PRS+1]=1MHz(BusClock=80MHz)

ATD0CTL5=0x30; //6:0 特殊通道禁止,5:1 连续转换 ,4:1 多通道轮流采样
ATD0DIEN=0x00; //禁止数字输入
*/
}
void AD_Getvalue(unsigned char *AD_value)//8 位精度
{
//while(!ATD0STAT0_SCF);//全通道转换完成前等待
while(!ATD0STAT2_CCF0);//0 通道转换完成前等待

//flag_ad0=1;    
*AD_value=ATD0DR0L;
AD_value++;


while(!ATD0STAT2_CCF1);//0 通道转换完成前等待

//flag_ad1=1;
*AD_value=ATD0DR1L;
AD_value++;
while(!ATD0STAT2_CCF2);//0 通道转换完成前等待

//flag_ad2=1;
*AD_value=ATD0DR2L;
AD_value++;
while(!ATD0STAT2_CCF3);//0 通道转换完成前等待
*AD_value=ATD0DR3L;
AD_value++;
while(!ATD0STAT2_CCF4);//0 通道转换完成前等待
*AD_value=ATD0DR4L;
AD_value++;
while(!ATD0STAT2_CCF5);//0 通道转换完成前等待
*AD_value=ATD0DR5L;
AD_value++;
while(!ATD0STAT2_CCF6);//0 通道转换完成前等待
*AD_value=ATD0DR6L;
AD_value++;
while(!ATD0STAT2_CCF7);//0 通道转换完成前等待
*AD_value=ATD0DR7L;
}
#else
unsigned int AD_val[8];
int ad_value1,ad_value2,ad_value3,ad_value4,ad_value5;
/*ATD 模块初始化*/
void ATD_Init(void)
{
//八通道AD 循环采样配置如下
ATD0CTL1=0x50; //7:1-外部触发,65:00-8 位精度01-10 位精度,4:放电,3210:开始转换通道

ATD0CTL2=0x42; //禁止外部触发, 中断禁止
ATD0CTL3=0xc0; //7:1 数据右对齐无符号,每次转换8 个序列, No FIFO, Freeze 模式下继续转

ATD0CTL4=0xff; //765: 采样时间为4 个AD 时钟周期,ATDClock=[BusClock*0.5]/[PRS+1]=1MHz(BusClock=80MHz)
            //07
ATD0CTL5=0x30; //6:0 特殊通道禁止,5:1 连续转换0 单次转换 ,4:1 多通道轮流采样3210:第一通道指定
             
ATD0DIEN=0x00; //禁止数字输入
//使用一个通道采集配置如下
/*
ATD0CTL1=0x20; //7:1-外部触发,65:00-10 位精度,4:放电,3210:ch
ATD0CTL2=0x40; //禁止外部触发, 中断禁止
ATD0CTL3=0x88; //右对齐无符号,每次转换1 个序列, No FIFO, Freeze 模式下继续转
// ATD0CTL3=0xc0; //右对齐无符号,每次转换8 个序列, No FIFO, Freeze 模式下继续转
ATD0CTL4=0x17; //765: 采样时间为4 个AD 时钟周期,ATDClock=[BusClock*0.5]/[PRS+1]=1MHz(BusClock=80MHz)

ATD0CTL5=0x30; //6:0 特殊通道禁止,5:1 连续转换 ,4:1 多通道轮流采样
ATD0DIEN=0x00; //禁止数字输入
*/
}
/*读取ad 转换结果*/
void AD_Getvalue(unsigned int *AD_val)//10 位精度
{
//while(!ATD0STAT0_SCF);//全通道转换完成前等待
while(!ATD0STAT2_CCF0);//0 通道转换完成前等待
*AD_val=ATD0DR0;
AD_val++;
while(!ATD0STAT2_CCF1);//0 通道转换完成前等待
*AD_val=ATD0DR1;
AD_val++;
while(!ATD0STAT2_CCF2);//0 通道转换完成前等待
*AD_val=ATD0DR2;
AD_val++;
while(!ATD0STAT2_CCF3);//0 通道转换完成前等待
*AD_val=ATD0DR3;
AD_val++;
while(!ATD0STAT2_CCF4);//0 通道转换完成前等待
*AD_val=ATD0DR4;
AD_val++;
while(!ATD0STAT2_CCF5);//0 通道转换完成前等待
*AD_val=ATD0DR5;
AD_val++;
while(!ATD0STAT2_CCF6);//0 通道转换完成前等待
*AD_val=ATD0DR6;
AD_val++;
while(!ATD0STAT2_CCF7);//0 通道转换完成前等待
*AD_val=ATD0DR7;
}

///

void ad_interrupt()
{
        while(!ATD0STAT2_CCF0);//0 通道转换完成前等待
        ad_value1=ATD0DR0;
        
        while(!ATD0STAT2_CCF1);//0 通道转换完成前等待
        ad_value2=ATD0DR1;
        
        while(!ATD0STAT2_CCF2);//0 通道转换完成前等待
        ad_value3=ATD0DR2;
        
        while(!ATD0STAT2_CCF3);//0 通道转换完成前等待
        ad_value4=ATD0DR3;
        
        while(!ATD0STAT2_CCF4);//0 通道转换完成前等待
        ad_value5=ATD0DR4;
}



#endif
#endif