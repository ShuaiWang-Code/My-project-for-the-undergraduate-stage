
#include "main.h"
#include "ATD.h"
 #include "UART.h"
volatile float real_angleY ;
volatile float AccY;  //   加速度
volatile float GyrY;    //陀螺仪
volatile float Gyr_jiaoY;   //陀螺仪的角速度
volatile float Acc_jiaoY;   //加速度的角度
volatile float Acc_GyrY;  //陀螺仪与加速度计的差
volatile float Gyr_repairY; //陀螺仪的补偿值

volatile float real_angleX ;
volatile float AccX;  //   加速度
volatile float GyrX;    //陀螺仪
volatile float Gyr_jiaoX;   //陀螺仪的角速度
volatile float Acc_jiaoX;   //加速度的角度
volatile float Acc_GyrX;  //陀螺仪与加速度计的差
volatile float Gyr_repairX; //陀螺仪的补偿值
volatile float GyrAccCraY ; //融合之后的角度 
volatile float GyrAccCraX ; //融合之后的角度 
#define  Gyr_time  0.05 ;  //积分时间
#define  Rep_time  0.25;    //角度补偿时间常数
extern volatile float Gyr_OFFSET,ADValue1,ADValue2,ADValue3,ADValue4,Gyr_OFFSET1,Gyr_OFFSET5;

/*************************************************
函数名: void Datehandle()  
功能:   互补滤波函数
参数:无
返回值:无
**************************************************/ 
void DatehandleY() 
{
   float Q =0.99,R = 0.01;         //加速度计陀螺仪权重   q+r=1 0.98 0.02

    
    
  AccY=ADValue1-1665;             //-90z轴1为垂直修正量  纠正垂直时的不确定
            
       

  GyrY=Gyr_OFFSET1-ADValue2;       // 陀螺仪的值

  Acc_jiaoY=AccY*0.138;             //z轴转过的角度 0.134
  
  Gyr_jiaoY=GyrY*0.043;            //陀螺仪的角度 
  real_angleY = Q*(real_angleY+ Gyr_jiaoY*0.05) + R*(Acc_jiaoY);    // 0.01 采样周期
    
  GyrAccCraY=real_angleY;
      
      

      //  OutData[0]=Acc_jiaoY;  //加速度计
//OutData[1]=Gyr_jiaoY;  //陀螺仪
  //OutData[2]=GyrAccCraY;  //陀螺仪

   // OutPut_Data(OutData) ;
  //加速度计

}


void DatehandleX() 
{
   float Q =0.99,R = 0.01;         //加速度计陀螺仪权重   q+r=1 0.98 0.02

     
    
    
  AccX=ADValue3-1660;             //-90z轴1为垂直修正量  纠正垂直时的不确定
            
       

  GyrX=Gyr_OFFSET5-ADValue4;       // 陀螺仪的值

  Acc_jiaoX=AccX*0.138;             //z轴转过的角度 0.134
  
  Gyr_jiaoX=GyrX*0.040;            //陀螺仪的角度 
  real_angleX= Q*(real_angleX + Gyr_jiaoX*0.05) + R*(Acc_jiaoX);    // 0.01 采样周期
    
  GyrAccCraX=real_angleX;
     

  //加速度计

}
