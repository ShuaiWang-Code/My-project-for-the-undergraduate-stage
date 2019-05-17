#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include <hidef.h>     
#include "derivative.h"
#include "nbctft.h"
extern unsigned int Device_code;
extern unsigned int sec;
unsigned int x_zuobiao,y_zuobiao,geshu;


void information_led()
{
       //LCD_PutString(58,304,"LED1:   ",Black,Green);
	   //LCD_PutString(122,304,"LED2:   ",Black,Green);
	   //LCD_PutString(186,304,"LED3:   ",Black,Green); 
}
void zone_zuobiao()
{
       LCD_PutString(0,272,"x:   cm",Black,Green);//64
	   LCD_PutString(0,288,"y:   cm",Black,Green);
	   //LCD_PutString(0,304,"����:A",Black,Green);
	   	   
	   LCD_PutString(96,272,"����������:��",Black,Green);
	   LCD_PutString(96,288,"����������:��",Black,Green); 
}
void xy_zuobiao_kuangkuang()
{
//subtitle           
       Show_RGB(0,240,0,320,Green);//��ִ�еĴ���
	   LCD_PutString(48,16,"�ɼ������ڶ�λװ��",Black,Green);    
           
//y
       LCD_PutString(112,34,"��",Black,Green);
	   LCD_PutString(128,34,"y",Black,Green);
       Put_Line(120,48,120,256,Black);   //����
       
       for(x_zuobiao = 24;x_zuobiao <= 216;x_zuobiao=x_zuobiao+12)
       {
            Put_Line(x_zuobiao,148,x_zuobiao,152,Black);
       }
      
//x              
       LCD_PutString(222,145,"��",Black,Green);
       LCD_PutString(222,153,"x",Black,Green);
	   Put_Line(16,152,224,152,Black); //����
	   	   
	   for(y_zuobiao = 56;y_zuobiao <= 248;y_zuobiao=y_zuobiao+12)
       {
            Put_Line(120,y_zuobiao,124,y_zuobiao,Black);
       }
       
       
//�����
	   Put_rectange(72,104,168,200,Red);
	   Put_rectange(24,56,216,248,Black);
	   Put_Line(24,56,72,104,Red);
	   Put_Line(168,200,216,248,Red);
	   Put_Line(72,200,24,248,Red);
	   Put_Line(216,56,168,104,Red);
}
//ˢ�½���
void frash_monitor()
{
       Show_RGB(0,240,0,64,Yellow);//����ˢ����һ�п�������ִ��һ�δ���
	   Show_RGB(0,240,64,128,Green);
	   Show_RGB(0,240,128,192,Magenta);
	   Show_RGB(0,240,192,256,Red);
	   Show_RGB(0,240,0,320,Yellow); 
}
void interface_init() 
{
       
	   
	   frash_monitor(); //ˢ��
      
       xy_zuobiao_kuangkuang();//�����ꡢ���
       
       zone_zuobiao();//��ʾ����
       
       information_led();	  //led��Ϣ 	   
	   
	   delayms(30000);  	   
	   delayms(30000);
	   
	   
	   //for (geshu = 1;geshu<5;geshu++)
	   //{
	   //draw_circle(120,152,geshu,Black);
	   //}	   
}
void xiaodian()
{
        Put_Line(120,48,120,256,Black);   //����
       
       for(x_zuobiao = 24;x_zuobiao <= 216;x_zuobiao=x_zuobiao+12)
       {
            Put_Line(x_zuobiao,148,x_zuobiao,152,Black);
       }
       Put_Line(16,152,224,152,Black); //����
	   	   
	   for(y_zuobiao = 56;y_zuobiao <= 248;y_zuobiao=y_zuobiao+12)
       {
            Put_Line(120,y_zuobiao,124,y_zuobiao,Black);
       }
       Put_rectange(72,104,168,200,Red);
	   Put_rectange(24,56,216,248,Black);
	   Put_Line(24,56,72,104,Red);
	   Put_Line(168,200,216,248,Red);
	   Put_Line(72,200,24,248,Red);
	   Put_Line(216,56,168,104,Red);
}
#endif