#ifndef _LQOLED_H
#define _LQOLED_H
#include "derivative.h"
 extern byte longqiu96x64[768];
 void OLED_Init(void);
 void OLED_CLS(void);
 void OLED_P6x8Str(byte x,byte y,byte ch[]);
 void OLED_P8x16Str(byte x,byte y,byte ch[]);
 void OLED_P14x16Str(byte x,byte y,byte ch[]);
 void OLED_Print(byte x, byte y, byte ch[]);
 void OLED_PutPixel(byte x,byte y);
 void OLED_Rectangle(byte x1,byte y1,byte x2,byte y2,byte gif);
 void Draw_LQLogo(void);
 void Draw_LibLogo(void);
 void Draw_BMP(byte x0,byte y0,byte x1,byte y1,byte bmp[]); 
 void OLED_Fill(byte dat);
 void Dis_String(byte y, byte x, byte ch[]);
 void Dis_Char(byte y,byte x,byte asc);
 void Dis_Num(byte y, byte x, unsigned int num,byte N);
 void Dis_Float(byte Y,byte X,double real,byte N);
 void Dis_Float2(byte Y,byte X,double real,byte N1,byte N2);
#endif