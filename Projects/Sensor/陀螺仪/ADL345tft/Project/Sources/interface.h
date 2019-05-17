#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include <hidef.h>     
#include "derivative.h"
#include "nbctft.h"
extern unsigned int Device_code;
extern unsigned int sec;
void interface_init() 
{
       
	   Show_RGB(0,240,0,64,Yellow);//遇到刷屏第一行卡屏，多执行一次代码
	   Show_RGB(0,240,64,128,Green);
	   Show_RGB(0,240,128,192,Magenta);
	   Show_RGB(0,240,192,256,Red);
	   Show_RGB(0,240,256,320,Yellow);
	   Show_RGB(0,240,0,64,Blue);//多执行的代码
	   LCD_PutString(24,16,"北方蓝芯科技开发有限公司",White,Blue);
       LCD_PutString(24,40,"   蓝芯科技 与您同行 ",White,Blue);

	   //μú2????óò??ê?ascii×?·??Dμ?êy×?oí·?o?
	   LCD_PutString(80,72,"0123456789",Black,Green);
	   //LCD_PutString(16,96,")(`,./<>';:[]{}\|?-=+*&^%$",Black,Green);
	   LCD_PutString(16,96,")(`,./<>';:[]{}|?-=+*&^%$$",Black,Green);

	   //μú3????óò??ê?ascii×?·??D×???
	   LCD_PutString(16,136,"abcdefghijklmnopqrstuvwxyz",Blue,Magenta);
	   LCD_PutString(16,156,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",Blue,Magenta);

	   //μú4????óò??ê?TFT?????÷ICDío?
	   LCD_PutString(16,200,"The Device IC Of TFT Is:",Black,Red);
	   LCD_PutString(96,224,"ILI",Black,Red);
	   LCD_PutChar(120, 224, 0x30+(Device_code>>12), Black, Red);
	   LCD_PutChar(128, 224, 0x30+((Device_code>>8)&0x000f), Black, Red);
	   LCD_PutChar(136, 224, 0x30+((Device_code>>4)&0x000f), Black, Red);
	   LCD_PutChar(144, 224, 0x30+(Device_code&0x000f), Black, Red);
	   
	   
       
	   
	   delayms(30000);  //??ê?ò???ê±??
	   delayms(30000);
	   delayms(30000);
	   delayms(30000);
	   delayms(30000);
	   delayms(30000);
	   delayms(30000);
	   delayms(30000);
	   //CLR_Screen(Red); //ó?±3?°é????á    
	   
}
#endif