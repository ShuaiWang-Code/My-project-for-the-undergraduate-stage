#ifndef _AD_H_
#define _AD_H_
#include <hidef.h>     
#include "derivative.h" 
#define _10_bit_mode
#ifdef _8_bit_mode
unsigned char AD_value[8];
//unsigned int flag_ad0,flag_ad1,flag_ad2;
/*ATD ģ���ʼ��*/

void ATD_Init(void)//8bit ģʽ
{
//��ͨ��AD ѭ��������������
ATD0CTL1=0x00; //7:1-�ⲿ����,65:00-8 λ����01-10 λ���ȣ�4:�ŵ�,3210:ͨ��0
ATD0CTL2=0x40; //��ֹ�ⲿ����, �жϽ�ֹ
ATD0CTL3=0xc0; //7:1 �����Ҷ����޷���,ÿ��ת��8 ������, No FIFO, Freeze ģʽ�¼���ת

ATD0CTL4=0x07; //765: ����ʱ��Ϊ4 ��AD ʱ������,ATDClock=[BusClock*0.5]/[PRS+1]=1MHz(BusClock=80MHz)

ATD0CTL5=0x30; //6:0 ����ͨ����ֹ,5:1 ����ת��0 ����ת�� ,4:1 ��ͨ����������3210:��һͨ��ָ��

ATD0DIEN=0x00; //��ֹ��������
//ʹ��һ��ͨ���ɼ���������
/*
ATD0CTL1=0x20; //7:1-�ⲿ����,65:00-10 λ����,4:�ŵ�,3210:ch
ATD0CTL2=0x40; //��ֹ�ⲿ����, �жϽ�ֹ
ATD0CTL3=0x88; //�Ҷ����޷���,ÿ��ת��1 ������, No FIFO, Freeze ģʽ�¼���ת
// ATD0CTL3=0xc0; //�Ҷ����޷���,ÿ��ת��8 ������, No FIFO, Freeze ģʽ�¼���ת
ATD0CTL4=0x07; //765: ����ʱ��Ϊ4 ��AD ʱ������,ATDClock=[BusClock*0.5]/[PRS+1]=1MHz(BusClock=80MHz)

ATD0CTL5=0x30; //6:0 ����ͨ����ֹ,5:1 ����ת�� ,4:1 ��ͨ����������
ATD0DIEN=0x00; //��ֹ��������
*/
}
void AD_Getvalue(unsigned char *AD_value)//8 λ����
{
//while(!ATD0STAT0_SCF);//ȫͨ��ת�����ǰ�ȴ�
while(!ATD0STAT2_CCF0);//0 ͨ��ת�����ǰ�ȴ�

//flag_ad0=1;    
*AD_value=ATD0DR0L;
AD_value++;


while(!ATD0STAT2_CCF1);//0 ͨ��ת�����ǰ�ȴ�

//flag_ad1=1;
*AD_value=ATD0DR1L;
AD_value++;
while(!ATD0STAT2_CCF2);//0 ͨ��ת�����ǰ�ȴ�

//flag_ad2=1;
*AD_value=ATD0DR2L;
AD_value++;
while(!ATD0STAT2_CCF3);//0 ͨ��ת�����ǰ�ȴ�
*AD_value=ATD0DR3L;
AD_value++;
while(!ATD0STAT2_CCF4);//0 ͨ��ת�����ǰ�ȴ�
*AD_value=ATD0DR4L;
AD_value++;
while(!ATD0STAT2_CCF5);//0 ͨ��ת�����ǰ�ȴ�
*AD_value=ATD0DR5L;
AD_value++;
while(!ATD0STAT2_CCF6);//0 ͨ��ת�����ǰ�ȴ�
*AD_value=ATD0DR6L;
AD_value++;
while(!ATD0STAT2_CCF7);//0 ͨ��ת�����ǰ�ȴ�
*AD_value=ATD0DR7L;
}
#else
unsigned int AD_val[8];
int ad_value1,ad_value2,ad_value3,ad_value4,ad_value5;
/*ATD ģ���ʼ��*/
void ATD_Init(void)
{
//��ͨ��AD ѭ��������������
ATD0CTL1=0x50; //7:1-�ⲿ����,65:00-8 λ����01-10 λ����,4:�ŵ�,3210:��ʼת��ͨ��

ATD0CTL2=0x42; //��ֹ�ⲿ����, �жϽ�ֹ
ATD0CTL3=0xc0; //7:1 �����Ҷ����޷���,ÿ��ת��8 ������, No FIFO, Freeze ģʽ�¼���ת

ATD0CTL4=0xff; //765: ����ʱ��Ϊ4 ��AD ʱ������,ATDClock=[BusClock*0.5]/[PRS+1]=1MHz(BusClock=80MHz)
            //07
ATD0CTL5=0x30; //6:0 ����ͨ����ֹ,5:1 ����ת��0 ����ת�� ,4:1 ��ͨ����������3210:��һͨ��ָ��
             
ATD0DIEN=0x00; //��ֹ��������
//ʹ��һ��ͨ���ɼ���������
/*
ATD0CTL1=0x20; //7:1-�ⲿ����,65:00-10 λ����,4:�ŵ�,3210:ch
ATD0CTL2=0x40; //��ֹ�ⲿ����, �жϽ�ֹ
ATD0CTL3=0x88; //�Ҷ����޷���,ÿ��ת��1 ������, No FIFO, Freeze ģʽ�¼���ת
// ATD0CTL3=0xc0; //�Ҷ����޷���,ÿ��ת��8 ������, No FIFO, Freeze ģʽ�¼���ת
ATD0CTL4=0x17; //765: ����ʱ��Ϊ4 ��AD ʱ������,ATDClock=[BusClock*0.5]/[PRS+1]=1MHz(BusClock=80MHz)

ATD0CTL5=0x30; //6:0 ����ͨ����ֹ,5:1 ����ת�� ,4:1 ��ͨ����������
ATD0DIEN=0x00; //��ֹ��������
*/
}
/*��ȡad ת�����*/
void AD_Getvalue(unsigned int *AD_val)//10 λ����
{
//while(!ATD0STAT0_SCF);//ȫͨ��ת�����ǰ�ȴ�
while(!ATD0STAT2_CCF0);//0 ͨ��ת�����ǰ�ȴ�
*AD_val=ATD0DR0;
AD_val++;
while(!ATD0STAT2_CCF1);//0 ͨ��ת�����ǰ�ȴ�
*AD_val=ATD0DR1;
AD_val++;
while(!ATD0STAT2_CCF2);//0 ͨ��ת�����ǰ�ȴ�
*AD_val=ATD0DR2;
AD_val++;
while(!ATD0STAT2_CCF3);//0 ͨ��ת�����ǰ�ȴ�
*AD_val=ATD0DR3;
AD_val++;
while(!ATD0STAT2_CCF4);//0 ͨ��ת�����ǰ�ȴ�
*AD_val=ATD0DR4;
AD_val++;
while(!ATD0STAT2_CCF5);//0 ͨ��ת�����ǰ�ȴ�
*AD_val=ATD0DR5;
AD_val++;
while(!ATD0STAT2_CCF6);//0 ͨ��ת�����ǰ�ȴ�
*AD_val=ATD0DR6;
AD_val++;
while(!ATD0STAT2_CCF7);//0 ͨ��ת�����ǰ�ȴ�
*AD_val=ATD0DR7;
}

///

void ad_interrupt()
{
        while(!ATD0STAT2_CCF0);//0 ͨ��ת�����ǰ�ȴ�
        ad_value1=ATD0DR0;
        
        while(!ATD0STAT2_CCF1);//0 ͨ��ת�����ǰ�ȴ�
        ad_value2=ATD0DR1;
        
        while(!ATD0STAT2_CCF2);//0 ͨ��ת�����ǰ�ȴ�
        ad_value3=ATD0DR2;
        
        while(!ATD0STAT2_CCF3);//0 ͨ��ת�����ǰ�ȴ�
        ad_value4=ATD0DR3;
        
        while(!ATD0STAT2_CCF4);//0 ͨ��ת�����ǰ�ȴ�
        ad_value5=ATD0DR4;
}



#endif
#endif