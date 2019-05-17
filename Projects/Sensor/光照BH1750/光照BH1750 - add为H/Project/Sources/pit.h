#ifndef _PIT_H_
#define _PIT_H_
#include <hidef.h>     
#include "derivative.h"  
#define PITTIME0 1000//�趨Ϊ1ms ��ʱ
#define PITTIME1 2000//�趨Ϊ2ms ��ʱ
#define PITTIME2 10000//�趨Ϊ10ms ��ʱ
#define PITTIME3 40000//�趨Ϊ40ms ��ʱ
volatile uint count0=0,count1=0,count2=0,count3=0;
//��ʱ����ʼ��
void PIT_Init(void)//��ʱ�жϳ�ʼ������
{
//ͨ��0 ��ʼ��,20ms ��ʱ�ж�����
PITCFLMT=0; //��ʱ�ж�ͨ����,4 ��ͨ�����ر�
PITCE_PCE0=1;//��ʱ��ͨ��0 ʹ��
PITMUX_PMUX0=0;//0:8 λ��ʱ��0 ��16 λ��ʱ����ͬ���ã����趨PITMTLD0 ��ֵ
//1:8 λ��ʱ��1 ��16 λ��ʱ����ͬ���ã����趨PITMTLD1 ��ֵ
PITMTLD0=80-1;//8 λ��ʱ��0 ��ֵ�趨��80MHzBusClock ��Ϊ1us���趨һ�μ���
//PITMTLD1=160-1;//8 λ��ʱ��1 ��ֵ�趨��80MHzBusClock ��Ϊ2us���趨һ�μ���
PITLD0=PITTIME0-1;//16 λ��ʱ����ֵ�趨��time=PITTIME*0.001MS
PITINTE_PINTE0=1;//1 ��ʱ���ж�ͨ��0 �ж�ʹ��
//PITCFLMT_PITE=1;//��ʱ��ʹ��,��ʼ��һ�μ���
//ͨ��1 ��ʼ��,40ms ��ʱ�ж�����
//PITCFLMT_PITE=0; //��ʱ�ж�ͨ���أ�4 ��ͨ�����ر�
PITCE_PCE1=0;//��ʱ��ͨ��2 ʹ��
PITMUX_PMUX1=0;//0:8 λ��ʱ��0 ��16 λ��ʱ����ͬ���ã����趨PITMTLD0 ��ֵ
//1:8 λ��ʱ��1 ��16 λ��ʱ����ͬ���ã����趨PITMTLD1 ��ֵ
//PITMTLD0=160-1;//8 λ��ʱ����ֵ�趨��80MHzBusClock �£�Ϊ2us
PITLD1=PITTIME1-1;//16 λ��ʱ����ֵ�趨��PITTIME*0.001MS
PITINTE_PINTE1=0;//1 ��ʱ���ж�ͨ��1 �ж�ʹ��
//PITCFLMT_PITE=1;//��ʱ��ʹ��,��ʼ��һ�μ���
//ͨ��2 ��ʼ��,60ms ��ʱ�ж�����
//PITCFLMT_PITE=0; //��ʱ�ж�ͨ���أ�4 ��ͨ�����ر�
PITCE_PCE2=0;//��ʱ��ͨ��2 ʹ��
PITMUX_PMUX2=0;//0:8 λ��ʱ��0 ��16 λ��ʱ����ͬ���ã����趨PITMTLD0 ��ֵ
//1:8 λ��ʱ��1 ��16 λ��ʱ����ͬ���ã����趨PITMTLD1 ��ֵ
//PITMTLD0=160-1;//8 λ��ʱ����ֵ�趨��80MHzBusClock �£�Ϊ2us
PITLD2=PITTIME2-1;//16 λ��ʱ����ֵ�趨��PITTIME*0.001ms
PITINTE_PINTE2=0;//1 ��ʱ���ж�ͨ��2 �ж�ʹ��
//PITCFLMT_PITE=1;//��ʱ��ʹ��,��ʼ��һ�μ���
//ͨ��3 ��ʼ��,80ms ��ʱ�ж�����
//PITCFLMT_PITE=0; //��ʱ�ж�ͨ���أ�4 ��ͨ�����ر�
PITCE_PCE3=0;//��ʱ��ͨ��3 ʹ��
PITMUX_PMUX3=0;//0:8 λ��ʱ��0 ��16 λ��ʱ����ͬ���ã����趨PITMTLD0 ��ֵ
//1:8 λ��ʱ��1 ��16 λ��ʱ����ͬ���ã����趨PITMTLD1 ��ֵ
//PITMTLD0=160-1;//8 λ��ʱ����ֵ�趨��80MHzBusClock �£�Ϊ2us
PITLD3=PITTIME3-1;//16 λ��ʱ����ֵ�趨��PITTIME*0.001ms
PITINTE_PINTE3=0;//1 ��ʱ���ж�ͨ��3 �ж�ʹ��
PITCFLMT_PITE=1;//��ʱ��ʹ��,��ʼ��һ�μ���
}
/*
#pragma CODE_SEG __NEAR_SEG NON_BANKED //ָʾ�ó����ڲ���ҳ��
void interrupt 66 PIT0(void)//��ʱ��0 �жϷ�����
{
count0++;
if(count0==50)
{
PORTA_PA0=~PORTA_PA0;//A0 LED ��ת��T=1S
count0=0;
}
PITTF_PTF0=1;//���жϱ�־λ
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED //ָʾ�ó����ڲ���ҳ��
void interrupt 67 PIT1(void)//��ʱ��1 �жϷ�����
{
count1++;
if(count1==50)
{
PORTA_PA0=~PORTA_PA0;//A0 LED ��ת,T=2S
count1=0;
}
PITTF_PTF1=1;//���жϱ�־λ
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED //ָʾ�ó����ڲ���ҳ��
void interrupt 68 PIT2(void)//��ʱ��2 �жϷ�����
{
count2++;
if(count2==50)
{
PORTA_PA0=~PORTA_PA0;//A0 LED ��ת,T=3S
count2=0;
}
PITTF_PTF2=1;//���жϱ�־λ
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED //ָʾ�ó����ڲ���ҳ��
void interrupt 69 PIT3(void)//��ʱ��3 �жϷ�����
{
count3++;
if(count3==50)
{
PORTA_PA0=~PORTA_PA0;//A0 LED ��ת,T=4S
count3=0;
}
PITTF_PTF3=1;//���жϱ�־λ
} 
*/
#endif