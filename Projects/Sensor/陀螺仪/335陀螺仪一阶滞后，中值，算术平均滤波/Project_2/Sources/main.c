//头文件
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "PLL.H"
#include "ad.h"
#include "math.h"
#include "filter.h"


//变量

int x,y,z,i;
float Q,T,K,Roll,Pitch,roll,pitch;

//函数声明
void angle() 
{
     x=ATD0DR0;
     y=ATD0DR1;
     z=ATD0DR2;

     x-=0X0152; 
   	 y-=0X0152;
	 z-=0X0152;
	 
	 Q=x;
     T=y;
     K=z;
     Q=-Q;
     Roll=(float)(((atan2(K,Q)*180)/3.14159265)+180);
	 Pitch=(float)(((atan2(K,T)*180)/3.14159265)+180);
}



void main(void) {
  /* put your own code here */
  

    PLL_init();
    ATD_Init();
	EnableInterrupts;


  for(;;) 
  {
     	
  
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt 22 AD(void) 
{   
       angle(); 
}

