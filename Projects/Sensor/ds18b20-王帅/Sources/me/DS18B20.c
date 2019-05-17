#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>
#pragma LINK_INFO DERIVATIVE "mc9s12xs128"
#include "DS18B20.h"
#include "DELAY.h"

unsigned char  temp1;                        //采集到的温度高8位
unsigned char  temp2;                         //采集到的温度低8位
unsigned char a;

//名称: 复位DS18B20函数

unsigned char reset(void)
{
  	unsigned char outbit;
	  DQ_HIGH(); 
	  delayus(1);
  	DQ_LOW() ;                                //主机拉至低电平
    delayus(8000);                              //延时503us
    DQ_HIGH();                                //释放总线等电阻拉高总线,并保持15~60us
    delayus(1000);                               //延时70us
    if(DQ==1) outbit=0;                     //没有接收到应答信号，继续复位
    else  outbit=1;
    //接收到应答信号
    delayus(600);                              //延时430us 
    return outbit;  	
}

//名称: 写字节函数

void write_byte(unsigned char  val)
{
 unsigned char i;
 unsigned char temp;
 for(i=8;i>0;i--)
 {
   temp=val&0x01;                            //最低位移出
   DQ_LOW();
   delayus(125);
   if(temp==1)  DQ_HIGH();                   //如果写1,拉高电平
   delayus(410);                               //延时63us
   DQ_HIGH();
   _asm(nop); 
   _asm(nop); 
   val=val>>1;                               //右移一位
  }
}
//名称: 读字节函数

unsigned char read_byte(void)
{
 unsigned char i;
 unsigned char value=0;                                //读出温度
 unsigned char j;
 for(i=8;i>0;i--)
 {
   value>>=1;
 
   DQ_LOW();
   delayus(50);
   DQ_HIGH();
   delayus(30);
   j=DQ;
   if(j) value|=0x80;
   delayus(500);                        //63us
  }
  return(value);
}

//名称: 启动读温度函数

void convert_T(void) 
{ 
  if(reset()==1) 
	{  
        write_byte(0xcc);     // 跳过多器件识别 
        write_byte(0x44);     // 启动温度转换 
  } 
} 

//名称: 读温度函数

void read_T(void) 
{ 
    unsigned char Lsb,Msb;            
    if(reset()==1) 
	{ a=0; 
        write_byte(0xcc);      // 跳过多器件识别 
        write_byte(0xbe);      // 读暂存器 
        Lsb=read_byte();       // 低字节 
        Msb=read_byte();  	   // 高字节 
		temp2=Lsb&0x0f;
		temp1=(Lsb>>4)|(Msb<<4);
  } else a=1; 
} 

void receive_temp(void)
{
                convert_T();
            	delay(100);
            	read_T();
}