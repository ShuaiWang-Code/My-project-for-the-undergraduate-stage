
#include "main.h"
#include "ATD.h"
 #include "UART.h"
volatile float real_angleY ;
volatile float AccY;  //   ���ٶ�
volatile float GyrY;    //������
volatile float Gyr_jiaoY;   //�����ǵĽ��ٶ�
volatile float Acc_jiaoY;   //���ٶȵĽǶ�
volatile float Acc_GyrY;  //����������ٶȼƵĲ�
volatile float Gyr_repairY; //�����ǵĲ���ֵ

volatile float real_angleX ;
volatile float AccX;  //   ���ٶ�
volatile float GyrX;    //������
volatile float Gyr_jiaoX;   //�����ǵĽ��ٶ�
volatile float Acc_jiaoX;   //���ٶȵĽǶ�
volatile float Acc_GyrX;  //����������ٶȼƵĲ�
volatile float Gyr_repairX; //�����ǵĲ���ֵ
volatile float GyrAccCraY ; //�ں�֮��ĽǶ� 
volatile float GyrAccCraX ; //�ں�֮��ĽǶ� 
#define  Gyr_time  0.05 ;  //����ʱ��
#define  Rep_time  0.25;    //�ǶȲ���ʱ�䳣��
extern volatile float Gyr_OFFSET,ADValue1,ADValue2,ADValue3,ADValue4,Gyr_OFFSET1,Gyr_OFFSET5;

/*************************************************
������: void Datehandle()  
����:   �����˲�����
����:��
����ֵ:��
**************************************************/ 
void DatehandleY() 
{
   float Q =0.99,R = 0.01;         //���ٶȼ�������Ȩ��   q+r=1 0.98 0.02

    
    
  AccY=ADValue1-1665;             //-90z��1Ϊ��ֱ������  ������ֱʱ�Ĳ�ȷ��
            
       

  GyrY=Gyr_OFFSET1-ADValue2;       // �����ǵ�ֵ

  Acc_jiaoY=AccY*0.138;             //z��ת���ĽǶ� 0.134
  
  Gyr_jiaoY=GyrY*0.043;            //�����ǵĽǶ� 
  real_angleY = Q*(real_angleY+ Gyr_jiaoY*0.05) + R*(Acc_jiaoY);    // 0.01 ��������
    
  GyrAccCraY=real_angleY;
      
      

      //  OutData[0]=Acc_jiaoY;  //���ٶȼ�
//OutData[1]=Gyr_jiaoY;  //������
  //OutData[2]=GyrAccCraY;  //������

   // OutPut_Data(OutData) ;
  //���ٶȼ�

}


void DatehandleX() 
{
   float Q =0.99,R = 0.01;         //���ٶȼ�������Ȩ��   q+r=1 0.98 0.02

     
    
    
  AccX=ADValue3-1660;             //-90z��1Ϊ��ֱ������  ������ֱʱ�Ĳ�ȷ��
            
       

  GyrX=Gyr_OFFSET5-ADValue4;       // �����ǵ�ֵ

  Acc_jiaoX=AccX*0.138;             //z��ת���ĽǶ� 0.134
  
  Gyr_jiaoX=GyrX*0.040;            //�����ǵĽǶ� 
  real_angleX= Q*(real_angleX + Gyr_jiaoX*0.05) + R*(Acc_jiaoX);    // 0.01 ��������
    
  GyrAccCraX=real_angleX;
     

  //���ٶȼ�

}
