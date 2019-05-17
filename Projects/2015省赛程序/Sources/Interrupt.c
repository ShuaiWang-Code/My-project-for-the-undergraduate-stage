#include "main.h"


 #define bee PORTK_PK4 
 #define LED PORTK_PK5 
unsigned int bee_count=0,bee_count1=0,bee_flag=1,num=0,num1=0,timer=0,time_35_=0;
 

 
 void bee_didi(void)
 
 { 
 
   
 
  if(bee_count1<=12)
    
   {
    if(bee_count>=70) 
    {
    LED=~LED;  
    bee=~bee;
    bee_count=0;
    bee_count1++;
    }
   
     
   }
   
   if(bee_count1>=13)
   
   {
     bee_flag=1;;
    bee_count1=0;
    bee_count=0;
      bee=0;
      LED=0;
   }
 }


       
#pragma CODE_SEG __NEAR_SEG NON_BANKED


/*************************************************
函数名: interrupt VectorNumber_Vpit0 void PIT_ISR (void) 
功能:   1ms中断处理函数
参数:无
返回值:无
**************************************************/ 
interrupt VectorNumber_Vpit0 void PIT_ISR (void) 
 {
     num++;
     num1++;
     bee_count++;
     time_35_++; 
       
   if(bee_flag==0)
    bee_didi();
   
    
    
   
   
   
   
/*      
   timer=600;   
      
  if(num1<timer) 
  
  {
    
    PWMDTY01=400;
    PWMDTY23=0;
	  PWMDTY45=400;
    PWMDTY67=0;
  }
 if(num1>=timer&&num1<2*timer) 
  
  {   
	  PWMDTY01=0;
    PWMDTY23=400;
	  PWMDTY45=400;
    PWMDTY67=0;
    
  }
  if(num1>=2*timer&&num1<3*timer) 
  
  { 
   
	  PWMDTY01=0;
    PWMDTY23=400;
	  PWMDTY45=0;
    PWMDTY67=400;
  }
   if(num1>=3*timer&&num1<4*timer) 
  
  { 
	  PWMDTY01=400;
    PWMDTY23=0;
	  PWMDTY45=0;
    PWMDTY67=400;
    
    
  }
  if(num1==4*timer)   num1=0;
  
           
      */
     PITTF_PTF0=1; //清除中断ADtransform();
 
 

 }
 
#pragma CODE_SEG DEFAULT     

