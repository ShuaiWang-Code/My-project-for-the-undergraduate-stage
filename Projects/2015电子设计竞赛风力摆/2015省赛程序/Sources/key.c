#include "main.h"
#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>     /* derivative information */


 
#define  KB_P       PTH              //键盘接在PTH口上，从左到右依次为PTH_PTH0-PTH_PTH7
#define  KB_D       DDRH             //相应的方向寄存器
#define  KB_PE      PERH             //相应的上拉下拉电阻允许寄存器
#define  KB_PS      PPSH             //相应的极性选择寄存器
#define  KB_IE      PIEH             //相应的中断允许寄存器
#define  KB_IF      PIFH 

extern unsigned int i,j;

volatile char m,k,p;
int jisuan[3]={0,0,0};

 volatile unsigned int  result=0,result1=0;
unsigned char n=0;
unsigned char flag=0,flag1=0,flag2=0,flag3=0;



/*************************************************************************************************
** 函数名称: Calc
** 功能描述:4*4键盘扫描函数
** 说明:    矩阵键盘设置
 1(1,1)     2(1,2)    3(1,3)    A (1,4):10
 
 4(2,1)     5(2,2)    6(2,3)    A (2,4):11
                                  
 7(3,1)     8(3,2)    9(3,3)    A (3,4) :12
   
 *(1,1):14  0(1,2)    #(1,3):15 A (1,4) :13

************************************************************************************************/

void KB_Init(void)
{
    KB_P  = 0x00;     //复位KB_P
    KB_D  = 0x0F;     //定义7-4为输入,3-0为输出
    KB_PE = 0xF0;     //定义KB_P.7-4允许上拉或下拉
    KB_PS = 0xF0;     //定义KB_P.7-4上拉电阻,并且下降沿产生中断
    KB_IE = 0x00;     //定义KB_P.7-4输入引脚禁止中断
    KB_IF = 0xFF;     //清除键盘中断标志位(写1清)
}
int keyscan(void)       //键盘扫描函数
{
  int data;
  byte line ;
   PTH=0x01;
      delay_us(200); //4
      
  n  = KB_P;     //通过观察4根列线中是否出现低电平来判断当前行有无按键

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
   

 n  = KB_P;       //通过观察4根列线中是否出现低电平来判断当前行有无按键

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
 KB_P = n & line; //读取键盘口数据寄存器
    delay_us(200);
   
 n  = KB_P;       //通过观察4根列线中是否出现低电平来判断当前行有无按键
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
 KB_P = n & line; //读取键盘口数据寄存器
   delay_us(200);
   
 n  = KB_P;       //通过观察4根列线中是否出现低电平来判断当前行有无按键

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
** 函数名称: Calc
** 功能描述:计算函数
** 说明:    通过矩阵键盘设置的一个两位数
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
** 函数名称: Calc_3
** 功能描述:计算函数
** 说明:    通过矩阵键盘设置的一个三位数
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
** 函数名称: set_data
** 功能描述:设置数值
** 说明:  操作方法：按一下A（一行四列）输入十位，再按一下B（二行四列） 输入各位
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
        jisuan[0]=m;  //百位
        flag1=0;
       }    
      }
    
  p=keyscan(); 
    if(flag2==1)      
    
     {
      if(m>=0 && m<=9) 
      {
        jisuan[1]=m;  //十位
        flag2=0;
      } 
     }
  p=keyscan(); 
    if(flag3==1)      
    
     {
      if(m>=0 && m<=9) 
      {
        jisuan[2]=m;  //个位
        flag2=0;
      } 
     }  
     
  p=keyscan();  
    if(m==15)
     {
       if(jisuan[0]==0)
     
       Calc(jisuan[1],jisuan[2]);   //计算
       
       
       if(jisuan[0]!=0)
       
        Calc_3(jisuan[0],jisuan[1],jisuan[2]);   //计算
        
        
        flag=1;
        m=0;
      
     }
  
      
       
              
       
    
 }























#pragma CODE_SEG __NEAR_SEG NON_BANKED