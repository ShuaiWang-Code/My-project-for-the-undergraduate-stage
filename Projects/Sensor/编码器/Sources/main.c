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
void interrupt 66 PIT0(void)//��ʱ��0 �жϷ�����   //����AD�ж�1ms��Ϊ5ms
{ 

   PITTF_PTF0=1;  //�����жϱ�־
   n=PACNT;
   PACNT=0;
   speed=n*10/N;  //����������
}
   
   
#pragma CODE_SEG DEFAULT   
