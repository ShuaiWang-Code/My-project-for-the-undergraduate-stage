#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "pll.h"
#include "pit.h"
#include "tim.h"

unsigned int n,Distance,shicha,cn0,cn1;

void port()
{
    DDRA=0XFF;
    PORTA_PA0=1;
}

void DELAY(unsigned int loop_times)                 //��ʱ10us����
{ 
  unsigned int loop_i,loop_j;
  for(loop_i=0;loop_i<loop_times;loop_i++) 
  {
   for(loop_j=0;loop_j<12;loop_j++);
  } 
}


void Chufa(void) 
{ 
     PORTA_PA0=1;//PA1����ߵ�ƽ
     DELAY(1);      //��ʱ10us
     PORTA_PA0=0;//PA1����͵�ƽ
} 

void main(void) {
  /* put your own code here */
  

    init_pll();
    Init_Pit();
    Init_ECT0();
    port();
	EnableInterrupts;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt 66 void PIT0(void)
{
      PITTF_PTF0 = 1;
      Chufa();
      
}

void interrupt 8 Timer0_Onput(void)
{
                
     TFLG1_C0F=1;
     
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
      Distance=(int)(shicha*0.017);   //��λcm
    
     
}  
