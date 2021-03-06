#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>
#pragma LINK_INFO DERIVATIVE "mc9s12xs128"
#include "LCD.h"
#include "DELAY.h"

const char shuzi[]={
	0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
	0x00, 0x00, 0x42, 0x7F, 0x40, 0x00,// 1
	0x00, 0x42, 0x61, 0x51, 0x49, 0x46,// 2
	0x00, 0x21, 0x41, 0x45, 0x4B, 0x31,// 3
	0x00, 0x18, 0x14, 0x12, 0x7F, 0x10,// 4
	0x00, 0x27, 0x45, 0x45, 0x45, 0x39,// 5
	0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
	0x00, 0x01, 0x71, 0x09, 0x05, 0x03,// 7
	0x00, 0x36, 0x49, 0x49, 0x49, 0x36,// 8
	0x00, 0x06, 0x49, 0x49, 0x29, 0x1E,// 9
	0x00, 0x00, 0x60, 0x60, 0x00, 0x00,// .  10
};
const char zimu[]={
 0x00, 0x20, 0x54, 0x54, 0x54, 0x78,// a  0
 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38,// b  1
 0x00, 0x38, 0x44, 0x44, 0x44, 0x20,// c  2
 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F,// d  3
 0x00, 0x38, 0x54, 0x54, 0x54, 0x18,// e  4
 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02,// f  5
 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C,// g  6
 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78,// h  7
 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00,// i  8
 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00,// j  9
 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,// k  10
 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00,// l  11
 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78,// m  12
 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78,// n  13
 0x00, 0x38, 0x44, 0x44, 0x44, 0x38,// o  14
 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18,// p  15
 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC,// q  16
 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08,// r  17
 0x00, 0x48, 0x54, 0x54, 0x54, 0x20,// s  18
 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20,// t  19
 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C,// u  20
 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C,// v  21
 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C,// w  22
 0x00, 0x44, 0x28, 0x10, 0x28, 0x44,// x  23
 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C,// y  24
 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44,// z  25
 0x00, 0x40, 0x40, 0x40, 0x40, 0x40,// _  26
} ;
const char hanzi[][24]={
//当
	{0x00,0x12,0x94,0x90,0x90,0x9F,0x90,0x90,0x94,0xF2,0x00,0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x0F,0x00,0x00},
//前
	{0x04,0xF4,0x55,0x56,0x54,0xF4,0x04,0xE6,0x05,0xF4,0x04,0x00,0x00,0x0F,0x01,0x01,0x09,0x0F,0x00,0x03,0x08,0x0F,0x00,0x00},
//温
	{0x22,0x44,0x00,0xC0,0x5F,0xD5,0x55,0xD5,0x5F,0xC0,0x00,0x00,0x04,0x02,0x09,0x0F,0x08,0x0F,0x08,0x0F,0x08,0x0F,0x08,0x00},
//度
	{0x00,0xFE,0x0A,0x8A,0xBE,0xAA,0xAB,0xAA,0xBE,0x8A,0x0A,0x00,0x08,0x07,0x00,0x08,0x09,0x0A,0x04,0x04,0x0A,0x09,0x08,0x00},

};
/////////////////////////////向液晶写命令和数据///////////////////////////////
void send_comordata(unsigned char Data,unsigned char Com)
{
	unsigned char a;
	LCD_SCE=0;
	LCD_DC=Com;
	for(a=0;a<8;a++)
	{
		if(Data&0x80)
			LCD_SDIN=1;
		else
			LCD_SDIN=0;
		LCD_SCLK=0;
		LCD_SCLK=1;
		Data=Data<<1;		
	}
	LCD_SCE=1;
}
//////////////////////////////设置显示地址/////////////////////////////////
void LCD_POS(unsigned char X,unsigned char Y)
{
	send_comordata(0x40|Y,com);
	send_comordata(0x80|X,com);	
}
/////////////////////////////液晶清屏函数/////////////////////////////////
void LCD_clear(void)
{
	unsigned char t;
	unsigned char k;
	LCD_POS(0,0);
	for(t=0;t<6;t++)
	{ 
		for(k=0;k<84;k++)
		{ 
			send_comordata(0x00,data);
				
		} 
	}
}
//////////////////////////////向液晶写入汉字///////////////////////////////////
void display_hanzi(unsigned char A,unsigned char X,unsigned char Y)
{
	unsigned char line;
	LCD_POS(X*12,Y);
	for(line=0;line<12;line++)
		send_comordata(hanzi[A][line],data);	
	LCD_POS(X*12,Y+1);
	for(line=12;line<24;line++)
		send_comordata(hanzi[A][line],data);	
}  
//////////////////////////////向液晶写入字母等其他字符//////////////////////////////////////
void display_zimu(unsigned char A,unsigned char X,unsigned char Y)
{
	unsigned char line;
	LCD_POS(X*6,Y);
	for(line=0;line<6;line++)
		send_comordata(zimu[A*6+line],data);		
}
////////////////////////////////向液晶写入数字/////////////////////////////////////
void display_shuzi(unsigned char A,unsigned char X,unsigned char Y)
{
	unsigned char line;                                                              
	LCD_POS(X*6,Y);	
	for(line=0;line<6;line++)                                                
		send_comordata(shuzi[A*6+line],data);	
}
////////////////////////////////////液晶初始化函数///////////////////////////////////
void LCD_init(void)
{	
    LCD_RST = 0;     // 产生一个让LCD复位的低电平脉冲
   	delay(10);
  	LCD_RST = 1;

    send_comordata(0x21,com);	// 使用扩展命令设置LCD模式
    send_comordata(0xc8,com);	// 设置液晶偏置电压
    send_comordata(0x06,com);	// 温度校正
    send_comordata(0x13,com);	// 1:48
    send_comordata(0x20,com);	// 使用基本命令，V=0，水平寻址
    LCD_clear();	           // 清屏
    send_comordata(0x0c,com);	// 设定显示模式，正常显示
   
    LCD_SCE = 0;      // 使能LCD
}


