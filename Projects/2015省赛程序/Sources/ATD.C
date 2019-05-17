
#include "main.h"

int mm,nn,jj;
volatile float ADValue1,ADValue2,ADValue3,ADValue4;
float AD1[20],AD2[20],AD3[20],AD4[20];
float AD1_MAX,AD1_MIN,AD2_MAX,AD2_MIN,AD2_MAX,AD2_MIN,AD3_MAX,AD3_MIN,AD4_MAX,AD4_MIN;
volatile float   Gyr_OFFSET=0,Gyr_OFFSET_DIR=0, Gyr_OFFSET0=0, Gyr_OFFSET1=0, Gyr_OFFSET2=0, Gyr_OFFSET3=0, Gyr_OFFSET4=0, Gyr_OFFSET5=0, Gyr_OFFSET6=0, Gyr_OFFSET7=0, Gyr_OFFSET8=0, Gyr_OFFSET9=0;
/*************************************************
函数名: void ATD0_Init (void)
功能:   配置ＡＤ模块位１２位精度，转换速度位１．７５Ｍ
参数:无
返回值:无
**************************************************/ 
void ATD0_Init (void)
 {//ATD0CTL0=0x02;        //2通道采样  0 1
 ATD0CTL1=0x40;        //分辨率12位，采样前内部采样电容放电
 ATD0CTL2=0x40;        //使能ATD启用快速清零方式 禁止外部触发，禁止中断
 ATD0CTL3=0xB0 ;        //右对齐  转换序列产度为2 90  //3  98// 4  A0 //5 A1 //6 B0
 ATD0CTL4=0x0f;        //4倍采样周期 PRS=15 AD时钟2MHz
 ATD0CTL5=0x30;        // 连续多通道转换 从通道0开始
 ATD0DIEN=0x00;        //禁止数字输入

}
/*************************************************
函数名: void ADtransform() 
功能:   读取加速度计陀螺仪的２０次ＡＤ值
参数:无
返回值:无
**************************************************/ 
void ADtransform() 
{
 AD1_MAX=AD1[0];           //对最大值复复幅值
 AD1_MIN=AD1[0];           //对最小值复复幅值
 AD2_MAX=AD2[0];           //对最大值复复幅值
 AD2_MIN=AD2[0];           //对最小值复复幅值

  for(mm=0;mm<20;mm++)     //采集20次AD值
    {  
 
     while(!ATD0STAT0_SCF);         //等待转换完成
      {
       AD1[mm]= ATD0DR1;            //加速度计
       AD2[mm]= ATD0DR2;            //陀螺仪
     
       if(AD1[mm]>AD1_MAX)          //求出最大值
         {
          AD1_MAX= AD1[mm];         //求出最大值
         }
       else if(AD1[mm]<=AD1_MIN)    //求出最小值
         { 
         AD1_MIN=AD1[mm] ;          //求出最小值
         }
       if(AD2[mm]>AD2_MAX)          //求出最大值
         {
         AD2_MAX=AD2[mm] ;          //求出最大值
         }
        else if(AD2[mm]<=AD2_MIN)   //求出最小值
         {
         AD2_MIN= AD2[mm];          //求出最小值
         }
  
 }
  }
}

 void ADtransform1() 
{
 AD3_MAX=AD3[0];           //对最大值复复幅值
 AD3_MIN=AD3[0];           //对最小值复复幅值
 AD4_MAX=AD4[0];           //对最大值复复幅值
 AD4_MIN=AD4[0];           //对最小值复复幅值

  for(mm=0;mm<20;mm++)     //采集20次AD值
    {  
 
     while(!ATD0STAT0_SCF);         //等待转换完成
      {
       AD3[mm]= ATD0DR3;            //加速度计
       AD4[mm]= ATD0DR4;            //陀螺仪
     
       if(AD3[mm]>AD3_MAX)          //求出最大值
         {
          AD3_MAX= AD3[mm];         //求出最大值
         }
       else if(AD3[mm]<=AD3_MIN)    //求出最小值
         { 
         AD3_MIN=AD3[mm] ;          //求出最小值
         }
       if(AD4[mm]>AD4_MAX)          //求出最大值
         {
         AD4_MAX=AD4[mm] ;          //求出最大值
         }
        else if(AD4[mm]<=AD4_MIN)   //求出最小值
         {
         AD4_MIN= AD4[mm];          //求出最小值
         }
  
 }
  }
}



/*************************************************
函数名: void Get_ADresult() 
功能:   读取加速度计陀螺仪的２０次ＡＤ值，对其求平均
参数:无
返回值:无
**************************************************/ 
void Get_ADresultY() 
{
 ADtransform();
 ADValue1=(AD1[0]+AD1[1]+AD1[2]+AD1[3]+AD1[4]+AD1[5]+AD1[6]+AD1[7]+AD1[8]+AD1[9]+AD1[10]+AD1[11]+AD1[12]+AD1[13]+AD1[14]+AD1[15]+AD1[16]+AD1[17]+AD1[18]+AD1[19]-AD1_MAX-AD1_MIN)/18;//去掉最大值和最小值求其平均值  
 ADValue2=(AD2[0]+AD2[1]+AD2[2]+AD2[3]+AD2[4]+AD2[5]+AD2[6]+AD2[7]+AD2[8]+AD2[9]+AD2[10]+AD2[11]+AD2[12]+AD2[13]+AD2[14]+AD2[15]+AD2[16]+AD2[17]+AD2[18]+AD2[19]-AD2_MAX-AD2_MIN)/18;//去掉最大值和最小值求其平均值
 //OutData[0]=ADValue0;  //加速度计
 //OutData[1]=ADValue1;  //陀螺仪
}
 
void Get_ADresultX() 
{
 ADtransform1();
 ADValue3=(AD3[0]+AD3[1]+AD3[2]+AD3[3]+AD3[4]+AD3[5]+AD3[6]+AD3[7]+AD3[8]+AD3[9]+AD3[10]+AD3[11]+AD3[12]+AD3[13]+AD3[14]+AD3[15]+AD3[16]+AD3[17]+AD3[18]+AD3[19]-AD3_MAX-AD3_MIN)/18;//去掉最大值和最小值求其平均值  
 ADValue4=(AD4[0]+AD4[1]+AD4[2]+AD4[3]+AD4[4]+AD4[5]+AD4[6]+AD4[7]+AD4[8]+AD4[9]+AD4[10]+AD4[11]+AD4[12]+AD4[13]+AD4[14]+AD4[15]+AD4[16]+AD4[17]+AD4[18]+AD4[19]-AD4_MAX-AD4_MIN)/18;//去掉最大值和最小值求其平均值

 
}
   
/*************************************************
函数名: void Get_Gyr_OFFSET(void) 
功能:   开机自动采集陀螺仪的零偏置
参数:无
返回值:无
**************************************************/ 
void Get_Gyr_OFFSET(void) 
{
     Gyr_OFFSET=0;
     Gyr_OFFSET3=0;
                //对最小值复复幅值
   for(nn=0;nn<2000;nn++)           //采集20次AD值
    {  
     while(!ATD0STAT0_SCF);       //等待转换完成
      {                           
       Gyr_OFFSET0=ATD0DR2;        //陀螺仪
       Gyr_OFFSET+= Gyr_OFFSET0;
      
     }
 }
 
 for(nn=0;nn<2000;nn++)           //采集20次AD值
    {  
     while(!ATD0STAT0_SCF);       //等待转换完成
      {                           
       Gyr_OFFSET4=ATD0DR4;        //陀螺仪
       Gyr_OFFSET3+= Gyr_OFFSET4;
      
     }
 }
 
Gyr_OFFSET=Gyr_OFFSET/2000.0; 
  Gyr_OFFSET3=Gyr_OFFSET3/2000.0; 
     Gyr_OFFSET1=Gyr_OFFSET;
     Gyr_OFFSET5=Gyr_OFFSET3;
}

