#ifndef _TUOLUO_H_
#define _TUOLUO_H_
#include <hidef.h>     
#include "derivative.h"
//#include  <REG51.H>   
#include  <math.h>    //Keil library   
#include  <stdio.h>   //Keil library  
//#include  <INTRINS.H>  

#define   uchar unsigned char 
#define   uint unsigned int

#define SCL PORTA_PA1
#define SDA PORTA_PA0

#define	SlaveAddress   0xA6

typedef unsigned char  BYTE; 
typedef unsigned short WORD;

BYTE BUF[8];

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

/**************************************
延时5微秒(STC90C52RC---12MHz---12T)
不同的工作环境,需要调整此函数，注意时钟过快时需要修改
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5us()
{
   delay_1us(6);
}

/**************************************
延时5毫秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数
当改用1T的MCU时,请调整此延时函数
**************************************/
void Delay5ms()
{
    delay_1ms(6);
}

/**************************************
起始信号
**************************************/
void ADXL345_Start()
{    
    DDRA_DDRA0=1;
    DDRA_DDRA1=1;
    
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 0;                    //产生下降沿
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
}

/**************************************
停止信号
**************************************/
void ADXL345_Stop()
{    

    DDRA_DDRA0=1;
    DDRA_DDRA1=1;
    
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 1;                    //产生上升沿
    Delay5us();                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(uchar ack)
{    
    DDRA_DDRA0=1;
    DDRA_DDRA1=1;
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
}

/**************************************
接收应答信号
**************************************/
uchar ADXL345_RecvACK()
{   
    uchar CY;  
    
    DDRA_DDRA0=0;
    DDRA_DDRA1=1;
    
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时

    return CY;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void ADXL345_SendByte(BYTE dat)
{    BYTE i;
     DDRA_DDRA0=1;
     DDRA_DDRA1=1;
    
    //SCL = 0; 
    for (i=0; i<8; i++)         //8位计数器
    {
                    //移出数据的最高位
        SDA =((dat&0x80)==0X80?1:0) ;               //送数据口
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        SCL = 0;                //拉低时钟线
        Delay5us();  
        dat <<= 1;  
                   //延时
    }
    ADXL345_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
BYTE ADXL345_RecvByte()
{BYTE i;
    BYTE dat = 0;
     DDRA_DDRA0=1;
     DDRA_DDRA1=1;
    

     SDA = 1;  //使能内部上拉,准备读取数据,
   //  SCL =0; 
    DDRA_DDRA0=0;                  
    for (i=0; i<8; i++)         //8位计数器
    {
       dat <<= 1;  
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        Delay5us();            //延时
        
    }
    return dat;
}

//******单字节写入*******************************************

void Single_Write_ADXL345(uchar REG_Address,uchar REG_data)
{
    ADXL345_Start();                  //起始信号
    ADXL345_SendByte(SlaveAddress);   //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf22页 
    ADXL345_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf22页 
    ADXL345_Stop();                   //发送停止信号
}

//********单字节读取*****************************************
uchar Single_Read_ADXL345(uchar REG_Address)
{  uchar REG_data;
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);            //发送存储单元地址，从0开始	
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data=ADXL345_RecvByte();              //读出寄存器数据
	ADXL345_SendACK(1);   
	ADXL345_Stop();                           //停止信号
    return REG_data; 
}

//*********************************************************
//
//连续读出ADXL345内部加速度数据，地址范围0x32~0x37
//
//*********************************************************
void Multiple_read_ADXL345(void)
{   uchar i;
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_SendByte(0x32);                   //发送存储单元地址，从0x32开始	
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	 for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF[i] = ADXL345_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 5)
        {
           ADXL345_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
          ADXL345_SendACK(0);                //回应ACK
       }
   }
    ADXL345_Stop();                          //停止信号
    Delay5ms();
}


//*****************************************************************

//初始化ADXL345，根据需要请参考pdf进行修改************************
void Init_ADXL345()
{
   Single_Write_ADXL345(0x31,0x0B);   //测量范围,正负16g，13位模式
   Single_Write_ADXL345(0x2C,0x08);   //速率设定为12.5 参考pdf13页
   Single_Write_ADXL345(0x2D,0x08);   //选择电源模式   参考pdf24页
   Single_Write_ADXL345(0x2E,0x80);   //使能 DATA_READY 中断
   Single_Write_ADXL345(0x1E,0x00);   //X 偏移量 根据测试传感器的状态写入pdf29页
   Single_Write_ADXL345(0x1F,0x00);   //Y 偏移量 根据测试传感器的状态写入pdf29页
   Single_Write_ADXL345(0x20,0x05);   //Z 偏移量 根据测试传感器的状态写入pdf29页
}






#endif