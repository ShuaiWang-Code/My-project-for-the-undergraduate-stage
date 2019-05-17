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
	   //LCD_PutString(0,304,"区域:A",Black,Green);
	   	   
	   LCD_PutString(96,272,"横坐标区域:上",Black,Green);
	   LCD_PutString(96,288,"纵坐标区域:左",Black,Green); 
}
void xy_zuobiao_kuangkuang()
{
//subtitle           
       Show_RGB(0,240,0,320,Green);//多执行的代码
	   LCD_PutString(48,16,"可见光室内定位装置",Black,Green);    
           
//y
       LCD_PutString(112,34,"↑",Black,Green);
	   LCD_PutString(128,34,"y",Black,Green);
       Put_Line(120,48,120,256,Black);   //纵线
       
       for(x_zuobiao = 24;x_zuobiao <= 216;x_zuobiao=x_zuobiao+12)
       {
            Put_Line(x_zuobiao,148,x_zuobiao,152,Black);
       }
      
//x              
       LCD_PutString(222,145,"→",Black,Green);
       LCD_PutString(222,153,"x",Black,Green);
	   Put_Line(16,152,224,152,Black); //横线
	   	   
	   for(y_zuobiao = 56;y_zuobiao <= 248;y_zuobiao=y_zuobiao+12)
       {
            Put_Line(120,y_zuobiao,124,y_zuobiao,Black);
       }
       
       
//画框框
	   Put_rectange(72,104,168,200,Red);
	   Put_rectange(24,56,216,248,Black);
	   Put_Line(24,56,72,104,Red);
	   Put_Line(168,200,216,248,Red);
	   Put_Line(72,200,24,248,Red);
	   Put_Line(216,56,168,104,Red);
}
//刷新界面
void frash_monitor()
{
       Show_RGB(0,240,0,64,Yellow);//遇到刷屏第一行卡屏，多执行一次代码
	   Show_RGB(0,240,64,128,Green);
	   Show_RGB(0,240,128,192,Magenta);
	   Show_RGB(0,240,192,256,Red);
	   Show_RGB(0,240,0,320,Yellow); 
}
void interface_init() 
{
       
	   
	   frash_monitor(); //刷屏
      
       xy_zuobiao_kuangkuang();//画坐标、框框
       
       zone_zuobiao();//显示坐标
       
       information_led();	  //led信息 	   
	   
	   delayms(30000);  	   
	   delayms(30000);
	   
	   
	   //for (geshu = 1;geshu<5;geshu++)
	   //{
	   //draw_circle(120,152,geshu,Black);
	   //}	   
}
void xiaodian()
{
        Put_Line(120,48,120,256,Black);   //纵线
       
       for(x_zuobiao = 24;x_zuobiao <= 216;x_zuobiao=x_zuobiao+12)
       {
            Put_Line(x_zuobiao,148,x_zuobiao,152,Black);
       }
       Put_Line(16,152,224,152,Black); //横线
	   	   
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