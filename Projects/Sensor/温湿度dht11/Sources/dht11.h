#ifndef _DHT11_H_
#define _DHT11_H_
#include <hidef.h>     
#include "derivative.h"

unsigned char  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
  
unsigned char a;  
  



/**********************************************************************************************
 ��������:void delay_1us(uint n) 
 ���ܽ��ܣ�Լ1us��ʱ
 ˵��������ʱ�ӣ�80MHz,������Ƶ���޸ģ����޸���ز���
 
**********************************************************************************************/
void delay_1us(uint n) 
{
  uint loop_i,loop_j;
  for(loop_i=0;loop_i<n;loop_i++) 
    for(loop_j=0;loop_j<10;loop_j++);
}

/*********************************************************************************************
 ��������:void delay_1ms(uint n) 
 ���ܽ��ܣ�Լ1ms��ʱ
 ˵��������ʱ�ӣ�80MHz,������Ƶ���޸ģ����޸���ز���
 
*********************************************************************************************/
void delay_1ms(uint n) 
{
  uint loop_i;
  for(loop_i=0;loop_i<n;loop_i++) 
  {
    delay_1us(1000);
  }

}



 char COM(void)
{
      
  uchar i,U8temp,U8comdata;
  DDRB_DDRB3=0; 
  for(i=0;i<8;i++)	   
   {
	while(!PORTB_PB3);
		//��ʾ ��ȡ�ĸߵ�λ��ʱ����20��us ���ȡ����1 �����ȡ����0
	delay_1us(30);		
	U8temp=0;
	 
	if(PORTB_PB3)
	   U8temp=1;
	while(PORTB_PB3);	   	 
		U8comdata=U8comdata<<1;
	   	U8comdata|=U8temp;        
	}
  return 	U8comdata;
}
 




unsigned int getDHT11(void)
{
  unsigned int F16T,F16RH;       //�������ն�ȡ����ʪ������
        DDRB_DDRB3=1; 
	 
   GO1:    PORTB_PB3=0;
	   delay_1ms(18); //��ʱ18ms
	   PORTB_PB3=1;
	 //������������������ ������ʱ20us
	   delay_1us(20);
	   
	 //������Ϊ���� �жϴӻ���Ӧ�ź� 
	  PORTB_PB3=1;
	 //�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������
	 	   DDRB_DDRB3=0; 
	   if(!PORTB_PB3)		 	  
	   {
	  
	   while(!PORTB_PB3);		//wait DHT goto high
	   
	   while(PORTB_PB3);
	 //���ݽ���״̬		 
	   
	   U8RH_data_H=COM();
	   
	   U8RH_data_L=COM();
	   
	   a=U8RH_data_L;
	   U8T_data_H=COM();
	   
	   U8T_data_L=COM();
	  
	   U8checkdata=COM();
	  
	 //����У�� 
	 
	   
	   if((U8T_data_H+U8T_data_L+U8RH_data_H+U8RH_data_L)!=U8checkdata)	 //if check wrong,read again
	   goto  GO1;
	   }//fi
	
	F16T=(0X30+U8T_data_H/10-'0')*10+(0X30+U8T_data_H%10-'0'); 
	F16RH=(0X30+U8RH_data_H/10-'0')*10+(0X30+U8RH_data_H%10-'0'); 

       return F16T*100+F16RH;
	}

/*
void main(void)
{
  
         DisableInterrupts ;
          
          SetBusCLK_80M();

         	EnableInterrupts;


  while(1)
  
    {
         th=getDHT11();//��ȡ��ʪ��
         t=th/100;//�¶�
         h=th%100;//ʪ��
          delay_1ms(200);
    
    
    }
}*/

#endif