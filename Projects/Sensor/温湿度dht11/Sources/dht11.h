#ifndef _DHT11_H_
#define _DHT11_H_
#include <hidef.h>     
#include "derivative.h"

unsigned char  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
  
unsigned char a;  
  



/**********************************************************************************************
 函数名称:void delay_1us(uint n) 
 功能介绍：约1us延时
 说明：总线时钟：80MHz,若总线频率修改，需修改相关参数
 
**********************************************************************************************/
void delay_1us(uint n) 
{
  uint loop_i,loop_j;
  for(loop_i=0;loop_i<n;loop_i++) 
    for(loop_j=0;loop_j<10;loop_j++);
}

/*********************************************************************************************
 函数名称:void delay_1ms(uint n) 
 功能介绍：约1ms延时
 说明：总线时钟：80MHz,若总线频率修改，需修改相关参数
 
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
		//表示 读取的高电位延时大于20多us 则读取的是1 否则读取的是0
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
  unsigned int F16T,F16RH;       //用于最终读取的温湿度数据
        DDRB_DDRB3=1; 
	 
   GO1:    PORTB_PB3=0;
	   delay_1ms(18); //延时18ms
	   PORTB_PB3=1;
	 //总线由上拉电阻拉高 主机延时20us
	   delay_1us(20);
	   
	 //主机设为输入 判断从机响应信号 
	  PORTB_PB3=1;
	 //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行
	 	   DDRB_DDRB3=0; 
	   if(!PORTB_PB3)		 	  
	   {
	  
	   while(!PORTB_PB3);		//wait DHT goto high
	   
	   while(PORTB_PB3);
	 //数据接收状态		 
	   
	   U8RH_data_H=COM();
	   
	   U8RH_data_L=COM();
	   
	   a=U8RH_data_L;
	   U8T_data_H=COM();
	   
	   U8T_data_L=COM();
	  
	   U8checkdata=COM();
	  
	 //数据校验 
	 
	   
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
         th=getDHT11();//获取温湿度
         t=th/100;//温度
         h=th%100;//湿度
          delay_1ms(200);
    
    
    }
}*/

#endif