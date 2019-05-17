#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include <hidef.h>     
#include "derivative.h"
#include "nbctft.h"
extern unsigned int Device_code;
extern unsigned int sec;
void interface_init() 
{
       
	   Show_RGB(0,240,0,64,Yellow);//����ˢ����һ�п�������ִ��һ�δ���
	   Show_RGB(0,240,64,128,Green);
	   Show_RGB(0,240,128,192,Magenta);
	   Show_RGB(0,240,192,256,Red);
	   Show_RGB(0,240,256,320,Yellow);
	   Show_RGB(0,240,0,64,Blue);//��ִ�еĴ���
	   LCD_PutString(24,16,"������о�Ƽ��������޹�˾",White,Blue);
       LCD_PutString(24,40,"   ��о�Ƽ� ����ͬ�� ",White,Blue);

	   //�̨�2????����??��?ascii��?��??D��?��y��?o����?o?
	   LCD_PutString(80,72,"0123456789",Black,Green);
	   //LCD_PutString(16,96,")(`,./<>';:[]{}\|?-=+*&^%$",Black,Green);
	   LCD_PutString(16,96,")(`,./<>';:[]{}|?-=+*&^%$$",Black,Green);

	   //�̨�3????����??��?ascii��?��??D��???
	   LCD_PutString(16,136,"abcdefghijklmnopqrstuvwxyz",Blue,Magenta);
	   LCD_PutString(16,156,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",Blue,Magenta);

	   //�̨�4????����??��?TFT?????��ICD��o?
	   LCD_PutString(16,200,"The Device IC Of TFT Is:",Black,Red);
	   LCD_PutString(96,224,"ILI",Black,Red);
	   LCD_PutChar(120, 224, 0x30+(Device_code>>12), Black, Red);
	   LCD_PutChar(128, 224, 0x30+((Device_code>>8)&0x000f), Black, Red);
	   LCD_PutChar(136, 224, 0x30+((Device_code>>4)&0x000f), Black, Red);
	   LCD_PutChar(144, 224, 0x30+(Device_code&0x000f), Black, Red);
	   
	   
       
	   
	   delayms(30000);  //??��?��???����??
	   delayms(30000);
	   delayms(30000);
	   delayms(30000);
	   delayms(30000);
	   delayms(30000);
	   delayms(30000);
	   delayms(30000);
	   //CLR_Screen(Red); //��?��3?�㨦????��    
	   
}
#endif