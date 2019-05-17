#include"main.h"   
   
#define SPEED_CONTROL_PERIOD 100 
   
int rightMotor=0,leftMotor=0; 
uint speed=500;
int right_dianji_sudu,left_dianji_sudu ;
volatile float g_fCarspeed,g_fSpeedControlOutNew,g_fSpeedControlOutOld,g_fSpeedControlOut=0;
volatile uint CAR_SPEED_SETfDelta=130;
volatile int g_nSpeedControlPeriod;
volatile float g_fSpeedControlIntegral; 
 volatile float carspeed,carspeed1;
   int speed_pluse_filter;
float SPEED_CONTROL_P,SPEED_CONTROL_D;
   float fDelta_old; 
 extern volatile uchar Time_flag,Time_flag1;
 extern volatile uchar conter,conter1;







/*******************************************************************************
函数名: void speed_read(void)
功能:  读取编码器返回的脉冲
参数:   无
返回值: 无
*******************************************************************************/ 
void average_speed(void)
{
    // float fDelta;
   //  float fP,fI;
 
 
// g_fCarspeed=(rightMotor+leftMotor)/2;  //求得车模的实际速度
      carspeed=rightMotor;
      carspeed1=leftMotor;
      
     rightMotor=0;  //清零
     leftMotor=0;
     
 
 
}       


/*******************************************************************************
函数名: void speed_read(void)
功能:  读取编码器返回的脉冲
参数:   无
返回值: 无
*******************************************************************************/ 
void speed_control(void)
{
    float fDelta;
    float fP,fI,fD;
 
 SPEED_CONTROL_P=1.5;//2;//     速度控制P   0.85
 //SPEED_CONTROL_I=0.0055;//.10;//0.0025;//0.03;//0.01;
 SPEED_CONTROL_D=0.5;
 
  g_fCarspeed=(rightMotor+leftMotor)/2;  //求得车模的实际速度
    speed_pluse_filter*=0.8;		//车轮速度滤波    ////////////////
     speed_pluse_filter+=g_fCarspeed*0.2;
    
 
    rightMotor=0;                            //清零
    leftMotor=0;
  
    
   
fDelta=CAR_SPEED_SETfDelta-speed_pluse_filter;
 //fDelta=speed-speed_pluse_filter;
 fP=fDelta*SPEED_CONTROL_P;
 //fI=fDelta*SPEED_CONTROL_I;
 fD=(fDelta-fDelta_old)*SPEED_CONTROL_D;
 fDelta_old=fDelta;
 
 
 g_fSpeedControlIntegral=fP+fD;
 
 g_fSpeedControlOutOld=g_fSpeedControlOutNew;
 
 g_fSpeedControlOutNew=g_fSpeedControlIntegral;
 
}



/*************************************************
函数名: void SpeeedControlOutput(void) 
功能:  速度控制输出
参数:   无
返回值: 无
**************************************************/ 
void SpeeedControlOutput(void) 
{
float fValue;
fValue=g_fSpeedControlOutNew-g_fSpeedControlOutOld;
g_fSpeedControlOut=fValue*(g_nSpeedControlPeriod*10)/SPEED_CONTROL_PERIOD+g_fSpeedControlOutOld;
} 

         








