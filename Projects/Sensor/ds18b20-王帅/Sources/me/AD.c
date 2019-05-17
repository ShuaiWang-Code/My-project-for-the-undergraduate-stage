#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>
#pragma LINK_INFO DERIVATIVE "mc9s12xs128"

float AD_result[8];//���ADת�����

////////////////////////��·AD��ʼ��///////////////////////////////////////////
void AD_init(void) 
{
 //  ATD0CTL0=0;        //ADת����ʼͨ��ΪAN0
   ATD0CTL1=0x00;     //����ָ��AD�����ⲿ���������8λ���������ǰ�������ݲ��ŵ� 1
   ATD0CTL2=0x40;     //����AD ��־�Ĵ�����������
   ATD0CTL3=0xc0;     //����Ҷ��룬��FIFOģʽ������ģʽ����ת�� ת������8
   ATD0CTL4=0x03;     //0000 0011 -����ʱ��Ϊ 4 �� AD ʱ������ ,PRS=1,ATDClock=BUSClock/(2*(PRS+1))=8MHz
   ATD0CTL5=0x30;     //ͨ��0  ����ת����ʼͨ��ΪAN0
   ATD0DIEN=0x00;     //�����������뻺��  
} 
///////////////////��ȡADֵ///////////////////////
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