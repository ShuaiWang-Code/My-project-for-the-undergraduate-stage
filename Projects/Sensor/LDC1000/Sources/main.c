#include "main.h"
#define PITTIME        200  
extern int LDC_val;

//*********时钟初始化******//  
void PLL_Init(void) //PLLCLK=2*OSCCLK*(SYNR+1)/(REFDV+1)
{                   //锁相环时钟=2×16×(3+1）/（1+1）=64MHz
  CLKSEL=0;        
  PLLCTL_PLLON=1;
  REFDV=0x81;       //REFDV=1//BUS CLOCK=32MHz
  SYNR=0x43;       //SYNDIV=3
  _asm(nop);
  _asm(nop);
  while(CRGFLG_LOCK!=1)
  //POSTDIV=0;
  CLKSEL_PLLSEL=1;       //选定锁相环时钟
}

/**********************************************/
//  @brief      main函数
//  @since      v1.2
//  @note       浮点科技LDC1000模块驱动程序
//  @淘宝官方店铺 https://floats.taobao.com/
 /*********************************************/ 
void main(void) 
{
  
  PLL_Init();
  FLOAT_LDC_init();
  //FLOAT_SPI_init();
  OLED_Init();
	EnableInterrupts;
	
	Dis_String(0,35,"LDC1000");
	Dis_String(2,48,"test:");
	
while(1) 
{

  LDC_val=filter()/10;//采样滤波
 	Dis_String(0,0,"Float Technology");
	Dis_String(3,0,"LDC_val:");
  Dis_Num(3,9,(uint)LDC_val,4);  

    
}
}

 

