#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "PIT.h"
#include "PLL.h"
#include "PAC.h"


unsigned int n;
unsigned char N;
float speed;



void main(void) {
  /* put your own code here */
  
      N=500;
      
      Init_PLL();
      Init_PIT();
      
      Init_PAC();

	EnableInterrupts;


  for(;;) 
  {
   
     
  
  } /* loop forever */
  /* please make sure that you never leave main */
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt 66 PIT0(void)//定时器0 中断服务函数   //加入AD中断1ms变为5ms
{ 

   PITTF_PTF0=1;  //清零中断标志
   n=PACNT;
   PACNT=0;
   speed=n*10/N;  //计算有问题
}
   
   
#pragma CODE_SEG DEFAULT   
