#ifndef _PIT_H_
#define _PIT_H_
#include <hidef.h>     
#include "derivative.h"  



void Init_PIT(void)//��ʱ�жϳ�ʼ������ ��20ms
{
           
   PITCFLMT=0; //��ʱ�ж�ͨ����,4 ��ͨ�����ر�

   PITCE_PCE0=1;//��ʱ��ͨ��0 ʹ��

   PITMUX_PMUX0=0;//0:8 λ��ʱ��0 ��16 λ��ʱ����ͬ���ã����趨PITMTLD0 ��ֵ
                  //1:8 λ��ʱ��1 ��16 λ��ʱ����ͬ���ã����趨PITMTLD1 ��ֵ

   PITMTLD0=32-1;//8 λ��ʱ��0 ��ֵ�趨��80MHzBusClock ��Ϊ1us���趨һ�μ���
                  //PITMTLD1=160-1;//8 λ��ʱ��1 ��ֵ�趨��80MHzBusClock ��Ϊ2us���趨һ�μ���

   PITLD0=20000-1;//16 λ��ʱ����ֵ�趨��time=PITTIME*0.001MS

   PITINTE_PINTE0=1;//1 ��ʱ���ж�ͨ��0 �ж�ʹ��
              
   PITCFLMT_PITE=1;//��ʱ��ʹ��,��ʼ��һ�μ���           
}

#endif