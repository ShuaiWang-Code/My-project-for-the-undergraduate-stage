#ifndef _TIM_H_
#define _TIM_H_
#include <hidef.h>     
#include "derivative.h"

void Init_ECT0(void)  //���벶׽��ʼ��  T7�ڽӳ�����echo
{     
      TSCR1_TFFCA = 1;  // ��ʱ����־λ�������
      TSCR1_TEN = 1; 
      TSCR2=0x05;     //��ֹ����жϣ���Ƶϵ��32     ���� 1us
      TIOS_IOS0=0;      //PT7Ϊ���벶׽
      TIOS_IOS2=0;
      TCTL4=0x13;     //���벶׽7�����غ��½��ؾ���Ч               
      TIE_C0I=1;      //ͨ��7���벶׽�ж����� 
      TIE_C2I=1;            
      TSCR1=0x80;     //ʹ�ܶ�ʱ��
      TFLG1 = 0xff;	    // �����IC/OC�жϱ�־λ д1���
      TFLG2 = 0xff;     // �����ʱ���жϱ�־λ  д1���
}
void Init_ECT2(void)  //���벶׽��ʼ��  T7�ڽӳ�����echo
{     
      TSCR1_TFFCA = 1;  // ��ʱ����־λ�������
      TSCR1_TEN = 1; 
      TSCR2=0x05;     //��ֹ����жϣ���Ƶϵ��32     ���� 1us
      TIOS_IOS2=0;      //PT7Ϊ���벶׽
      TCTL4=0x30;     //���벶׽7�����غ��½��ؾ���Ч               
      TIE_C2I=1;      //ͨ��7���벶׽�ж�����             
      TSCR1=0x80;     //ʹ�ܶ�ʱ��
      TFLG1 = 0xff;	    // �����IC/OC�жϱ�־λ д1���
      TFLG2 = 0xff;     // �����ʱ���жϱ�־λ  д1���
}

#endif