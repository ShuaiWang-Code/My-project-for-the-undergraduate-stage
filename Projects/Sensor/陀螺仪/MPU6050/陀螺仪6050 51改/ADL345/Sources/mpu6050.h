#ifndef _ADXL345_H_
#define  _ADXL345_H_
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned char  BYTE;
typedef unsigned short WORD;
#define SCL PORTA_PA1
#define SDA PORTA_PA0
//****************************************
// 定义MPU6050内部地址
//****************************************

#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I			0x75	//IIC地址寄存器(默认数值0x68，只读)
#define	SlaveAddress	0xD0	//IIC写入时的地址字节数据，+1为读取
//****************************************
//定义类型及变量
//****************************************
uchar dis[6];							//显示数字(-511至512)的字符数组
int	dis_data;						//变量
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
void I2C_Start()
{    DDRA_DDRA0=1;
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
void I2C_Stop()
{    DDRA_DDRA0=1;
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
void I2C_SendACK(uchar ack)
{    DDRA_DDRA0=1;
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
uchar I2C_RecvACK()
{  uchar CY;  
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
void I2C_SendByte(uchar dat)
{    uchar i;
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
    I2C_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
uchar I2C_RecvByte()
{uchar i;
    char dat = 0;
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

void Single_WriteI2C(uchar REG_Address,uchar REG_data)
{    
    I2C_Start();                  //起始信号
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号
    I2C_SendByte(REG_Address);    //内部寄存器地址，
    I2C_SendByte(REG_data);       //内部寄存器数据，
    I2C_Stop();                   //发送停止信号
                  
}

//********单字节读取*****************************************
uchar Single_ReadI2C(uchar REG_Address)
{
	uchar REG_data;
	I2C_Start();                   //起始信号
	I2C_SendByte(SlaveAddress);    //发送设备地址+写信号
	I2C_SendByte(REG_Address);     //发送存储单元地址，从0开始	
	I2C_Start();                   //起始信号
	I2C_SendByte(SlaveAddress+1);  //发送设备地址+读信号
	REG_data=I2C_RecvByte();       //读出寄存器数据
	I2C_SendACK(1);                //接收应答信号
	I2C_Stop();                    //停止信号
	return REG_data;
}
//*********************************************************
//
//连续读出ReadI2C内部加速度数据，地址范围0x32~0x37
//
//*********************************************************
void Multiple_read_I2C(void)
{   uchar i;
    I2C_Start();                          //起始信号
    I2C_SendByte(SlaveAddress);           //发送设备地址+写信号
    I2C_SendByte(0x32);                   //发送存储单元地址，从0x32开始	
   I2C_Start();                          //起始信号
    I2C_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	 for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF[i] = I2C_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 5)
        {
           I2C_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
          I2C_SendACK(0);                //回应ACK
       }
   }
    I2C_Stop();                          //停止信号
    Delay5ms();
}


//**************************************
//初始化MPU6050
//**************************************
void InitMPU6050()
{
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_WriteI2C(SMPLRT_DIV, 0x07);
	Single_WriteI2C(CONFIG, 0x06);
	Single_WriteI2C(GYRO_CONFIG, 0x18);
	Single_WriteI2C(ACCEL_CONFIG, 0x01);
}
//**************************************
//合成数据
//**************************************
int GetData(uchar REG_Address)
{
	uchar H,L;
	H=Single_ReadI2C(REG_Address);
	L=Single_ReadI2C(REG_Address+1);
	return (H<<8)+L;   //合成数据
}
#endif