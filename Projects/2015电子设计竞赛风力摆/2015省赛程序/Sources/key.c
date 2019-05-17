#include "main.h"
#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>     /* derivative information */


 
#define  KB_P       PTH              //���̽���PTH���ϣ�����������ΪPTH_PTH0-PTH_PTH7
#define  KB_D       DDRH             //��Ӧ�ķ���Ĵ���
#define  KB_PE      PERH             //��Ӧ������������������Ĵ���
#define  KB_PS      PPSH             //��Ӧ�ļ���ѡ��Ĵ���
#define  KB_IE      PIEH             //��Ӧ���ж�����Ĵ���
#define  KB_IF      PIFH 

extern unsigned int i,j;

volatile char m,k,p;
int jisuan[3]={0,0,0};

 volatile unsigned int  result=0,result1=0;
unsigned char n=0;
unsigned char flag=0,flag1=0,flag2=0,flag3=0;



/*************************************************************************************************
** ��������: Calc
** ��������:4*4����ɨ�躯��
** ˵��:    �����������
 1(1,1)     2(1,2)    3(1,3)    A (1,4):10
 
 4(2,1)     5(2,2)    6(2,3)    A (2,4):11
                                  
 7(3,1)     8(3,2)    9(3,3)    A (3,4) :12
   
 *(1,1):14  0(1,2)    #(1,3):15 A (1,4) :13

************************************************************************************************/

void KB_Init(void)
{
    KB_P  = 0x00;     //��λKB_P
    KB_D  = 0x0F;     //����7-4Ϊ����,3-0Ϊ���
    KB_PE = 0xF0;     //����KB_P.7-4��������������
    KB_PS = 0xF0;     //����KB_P.7-4��������,�����½��ز����ж�
    KB_IE = 0x00;     //����KB_P.7-4�������Ž�ֹ�ж�
    KB_IF = 0xFF;     //��������жϱ�־λ(д1��)
}
int keyscan(void)       //����ɨ�躯��
{
  int data;
  byte line ;
   PTH=0x01;
      delay_us(200); //4
      
  n  = KB_P;     //ͨ���۲�4���������Ƿ���ֵ͵�ƽ���жϵ�ǰ�����ް���

    if(n!=0x01)
    {
      switch(n)
      {
      case(0x11):m=1;break;
      case(0x21):m=2;break;
      case(0x41):m=3;break;
      case(0x81):m=10;break;
      }   
       n  = KB_P; 
    n&=0xf0;
      while(n!=0x00){
         delay_us(100);
         n  = KB_P; 
    n&=0xf0;
      }
      k++;
      if(k==1) 
     data=m;
     if(k>=2)
      data=data*10+m;
   }

 PTH=0x02;
   delay_us(200);
   

 n  = KB_P;       //ͨ���۲�4���������Ƿ���ֵ͵�ƽ���жϵ�ǰ�����ް���

   if(n!=0x02)
   {
      switch(n)
      {
      case(0x12):m=4;break;
      case(0x22):m=5;break;
      case(0x42):m=6;break;
      case(0x82):m=11;break;
      }
      n  = KB_P; 
    n&=0xf0;
      while(n!=0x00){
         delay_us(100);
         n  = KB_P; 
    n&=0xf0; 
      }
      k++;
      if(k==1) 
     data=m;
     if(k>=2)
      data=data*10+m; 
   }

line=0xf4;
 n  = KB_P;
 n |= 0X0F;
 KB_P = n & line; //��ȡ���̿����ݼĴ���
    delay_us(200);
   
 n  = KB_P;       //ͨ���۲�4���������Ƿ���ֵ͵�ƽ���жϵ�ǰ�����ް���
 if(n!=0x04)      
 {
   delay_us(100);

   if(n!=0x04)
   {
    switch(n)
    {
    case(0x14):m=7;break;
    case(0x24):m=8;break;
    case(0x44):m=9;break;
    case(0x84):m=12;break;
    }
      n  = KB_P; 
    n&=0xf0;
      while(n!=0x00){
         delay_us(100);
         n  = KB_P; 
    n&=0xf0; }
      k++;
    if(k==1) 
     data=m;
     if(k>=2)
      data=data*10+m;
 } 
 }
 line=0xf8;
 n  = KB_P;
 n |= 0X0F;
 KB_P = n & line; //��ȡ���̿����ݼĴ���
   delay_us(200);
   
 n  = KB_P;       //ͨ���۲�4���������Ƿ���ֵ͵�ƽ���жϵ�ǰ�����ް���

 if(n!=0x08)
 {
   delay_us(100);

   if(n!=0x08)
   {
    switch(n)
    {
     case(0x18):m=14;break;
     case(0x28):m=0;break;
     case(0x48):m=15;break;
     case(0x88):m=13;break;
    }
     n  = KB_P; 
    n&=0xf0;
      while(n!=0x00){
          delay_us(100);
         n  = KB_P; 
    n&=0xf0;}
      k++;
    if(k==1) 
     data=m;
     if(k>=2)
      data=data*10+m;
     
 } 
} 
return data; 
}

  /*************************************************************************************************
** ��������: Calc
** ��������:���㺯��
** ˵��:    ͨ������������õ�һ����λ��
************************************************************************************************/
float Calc(int shuzi1,int shuzi2)
{
  
  
    if(flag==1) 
    {
      
    result=shuzi1*10+shuzi2;
    flag=0;
    }                                    
    
    
  
 
 
  return result;
}
  /*************************************************************************************************
** ��������: Calc_3
** ��������:���㺯��
** ˵��:    ͨ������������õ�һ����λ��
************************************************************************************************/
float Calc_3(int shuzi0,int shuzi1,int shuzi2)
{
  
  
    if(flag==1)//&&jisuan[0]!=0) 
    {
      
    result1=shuzi0*100+shuzi1*10+shuzi2;
    flag=0;
    }
    
    
  
 
 
  return result1;
}

  /*************************************************************************************************
** ��������: set_data
** ��������:������ֵ
** ˵��:  ������������һ��A��һ�����У�����ʮλ���ٰ�һ��B���������У� �����λ
************************************************************************************************/

 void set_data(void)
 
 {
 
     if(m==10) flag1=1;
     if(m==11) flag2=1; 
     if(m==12) flag3=1;
   p=keyscan();
      if(flag1==1)
      
      {
        
      if(m>=0 && m<=9)
       {
        jisuan[0]=m;  //��λ
        flag1=0;
       }    
      }
    
  p=keyscan(); 
    if(flag2==1)      
    
     {
      if(m>=0 && m<=9) 
      {
        jisuan[1]=m;  //ʮλ
        flag2=0;
      } 
     }
  p=keyscan(); 
    if(flag3==1)      
    
     {
      if(m>=0 && m<=9) 
      {
        jisuan[2]=m;  //��λ
        flag2=0;
      } 
     }  
     
  p=keyscan();  
    if(m==15)
     {
       if(jisuan[0]==0)
     
       Calc(jisuan[1],jisuan[2]);   //����
       
       
       if(jisuan[0]!=0)
       
        Calc_3(jisuan[0],jisuan[1],jisuan[2]);   //����
        
        
        flag=1;
        m=0;
      
     }
  
      
       
              
       
    
 }























#pragma CODE_SEG __NEAR_SEG NON_BANKED