#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library
#include "mpu6050.h"

void SetBusCLK_80M(void)
{
CLKSEL_PLLSEL=0; //disengage PLL to system
PLLCTL_PLLON=1; //turn on PLL
SYNR =0xC0 | 0x09;
REFDV=0x80 | 0x01;
POSTDIV=0x00; //pllclock=2*osc*(1+SYNR)/(1+REFDV)=160MHz;
_asm(nop); //BUS CLOCK=80M
_asm(nop);
while(!(CRGFLG_LOCK==1)); //when pll is steady ,then use it;
CLKSEL_PLLSEL =1; //engage PLL to system;
}



int xv,yv,zv;
uchar devid;
float Roll,Pitch,Q,T,K;
void main(void) {
  /* put your own code here */
 
    SetBusCLK_80M();
    DDRA=0XFF;
 
	EnableInterrupts;
    delay_1ms(8);
    InitMPU6050();  
  
  for(;;) {
  
		  xv=GetData(ACCEL_XOUT_H);
          yv=GetData(ACCEL_YOUT_H);
          zv=GetData(ACCEL_ZOUT_H);
          
		
     
         Q=(float)xv*3.9;
         T=(float)yv*3.9;
         K=(float)zv*3.9;
         Q=-Q;

         Roll=(float)(((atan2(K,Q)*180)/3.14159265)+180);    //X?ив???ии?ж╠
         Pitch=(float)(((atan2(K,T)*180)/3.14159265)+180);  //Y?ив???ии?ж╠
   		
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
