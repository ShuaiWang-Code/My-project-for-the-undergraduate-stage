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
// ����MPU6050�ڲ���ַ
//****************************************

#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG			0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
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
#define	PWR_MGMT_1		0x6B	//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I			0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define	SlaveAddress	0xD0	//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ
//****************************************
//�������ͼ�����
//****************************************
uchar dis[6];							//��ʾ����(-511��512)���ַ�����
int	dis_data;						//����
 BYTE BUF[8];
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



/**************************************
��ʱ5΢��(STC90C52RC---12MHz---12T)
��ͬ�Ĺ�������,��Ҫ�����˺�����ע��ʱ�ӹ���ʱ��Ҫ�޸�
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5us()
{
   delay_1us(6);
}

/**************************************
��ʱ5����(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺���
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5ms()
{
    delay_1ms(6);
}


/**************************************
��ʼ�ź�
**************************************/
void I2C_Start()
{    DDRA_DDRA0=1;
     DDRA_DDRA1=1;
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 0;                    //�����½���
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
}
/**************************************
ֹͣ�ź�
**************************************/
void I2C_Stop()
{    DDRA_DDRA0=1;
     DDRA_DDRA1=1;
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 1;                    //����������
    Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void I2C_SendACK(uchar ack)
{    DDRA_DDRA0=1;
     DDRA_DDRA1=1;
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
uchar I2C_RecvACK()
{  uchar CY;  
     DDRA_DDRA0=0;
     DDRA_DDRA1=1;
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    CY = SDA;                   //��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ

    return CY;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void I2C_SendByte(uchar dat)
{    uchar i;
     DDRA_DDRA0=1;
     DDRA_DDRA1=1;
    
    //SCL = 0; 
    for (i=0; i<8; i++)         //8λ������
    {
                    //�Ƴ����ݵ����λ
        SDA =((dat&0x80)==0X80?1:0) ;               //�����ݿ�
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        SCL = 0;                //����ʱ����
        Delay5us();  
        dat <<= 1;  
                   //��ʱ
    }
    I2C_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
uchar I2C_RecvByte()
{uchar i;
    char dat = 0;
     DDRA_DDRA0=1;
     DDRA_DDRA1=1;
    

     SDA = 1;  //ʹ���ڲ�����,׼����ȡ����,
   //  SCL =0; 
    DDRA_DDRA0=0;                  
    for (i=0; i<8; i++)         //8λ������
    {
       dat <<= 1;  
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        dat |= SDA;             //������               
        SCL = 0;                //����ʱ����
        Delay5us();            //��ʱ
        
    }
    return dat;
}

//******���ֽ�д��*******************************************

void Single_WriteI2C(uchar REG_Address,uchar REG_data)
{    
    I2C_Start();                  //��ʼ�ź�
    I2C_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    I2C_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ��
    I2C_SendByte(REG_data);       //�ڲ��Ĵ������ݣ�
    I2C_Stop();                   //����ֹͣ�ź�
                  
}

//********���ֽڶ�ȡ*****************************************
uchar Single_ReadI2C(uchar REG_Address)
{
	uchar REG_data;
	I2C_Start();                   //��ʼ�ź�
	I2C_SendByte(SlaveAddress);    //�����豸��ַ+д�ź�
	I2C_SendByte(REG_Address);     //���ʹ洢��Ԫ��ַ����0��ʼ	
	I2C_Start();                   //��ʼ�ź�
	I2C_SendByte(SlaveAddress+1);  //�����豸��ַ+���ź�
	REG_data=I2C_RecvByte();       //�����Ĵ�������
	I2C_SendACK(1);                //����Ӧ���ź�
	I2C_Stop();                    //ֹͣ�ź�
	return REG_data;
}
//*********************************************************
//
//��������ReadI2C�ڲ����ٶ����ݣ���ַ��Χ0x32~0x37
//
//*********************************************************
void Multiple_read_I2C(void)
{   uchar i;
    I2C_Start();                          //��ʼ�ź�
    I2C_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    I2C_SendByte(0x32);                   //���ʹ洢��Ԫ��ַ����0x32��ʼ	
   I2C_Start();                          //��ʼ�ź�
    I2C_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
	 for (i=0; i<6; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = I2C_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 5)
        {
           I2C_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
          I2C_SendACK(0);                //��ӦACK
       }
   }
    I2C_Stop();                          //ֹͣ�ź�
    Delay5ms();
}


//**************************************
//��ʼ��MPU6050
//**************************************
void InitMPU6050()
{
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//�������״̬
	Single_WriteI2C(SMPLRT_DIV, 0x07);
	Single_WriteI2C(CONFIG, 0x06);
	Single_WriteI2C(GYRO_CONFIG, 0x18);
	Single_WriteI2C(ACCEL_CONFIG, 0x01);
}
//**************************************
//�ϳ�����
//**************************************
int GetData(uchar REG_Address)
{
	uchar H,L;
	H=Single_ReadI2C(REG_Address);
	L=Single_ReadI2C(REG_Address+1);
	return (H<<8)+L;   //�ϳ�����
}
#endif