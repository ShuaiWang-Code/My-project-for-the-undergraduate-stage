#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "PLL.h"
#include "PIT.h"
#include "TIM.h"
//#include "xianfulvbo.h"


unsigned int n=0;
 unsigned int cn0,cn1,shicha,zhenshizhi;
int Distance;  //juli2为障碍物到传感器距离



  
void DELAY(unsigned int loop_times)                 //延时10us程序
{ 
  unsigned int loop_i,loop_j;
  for(loop_i=0;loop_i<loop_times;loop_i++) 
  {
   for(loop_j=0;loop_j<12;loop_j++);
  } 
}


void Chufa(void) 
   { 
     PORTB_PB0=1;//PA1输出高电平
     DELAY(1);      //延时10us
     PORTB_PB0=0;//PA1输出低电平
   } 

void main(void) 
{
  /* put your own code here */
  
     DDRB = 0xFF;
     
     Init_PLL();
     Init_Pit();
     Init_ECT0();


	EnableInterrupts;


  for(;;) 
  {
   
  } /* loop forever */
  /* please make sure that you never leave main */
}



#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt 66 void PIT0(void)
   {
      PITTF_PTF0 = 1;
      Chufa();
      
   }

void interrupt 15 Timer0_Onput(void)
    {
                
     TFLG1_C7F=1;
     
     n++;
     
     if(!(n%2)==0)
        {
         cn1=TCNT;
        
        } 
     if(n%2==0)
        {
        cn0=TCNT;
        
        }
      if(n==3)
      {  
      n=1;
      }
      if(cn0>cn1)
      {
      shicha=cn0-cn1;
      }
      Distance=(int)(shicha*0.017);   //单位cm
    
      //lvbo_1(Distance);
     
         
     }  
