#ifndef __LCD__
#define __LCD__

#define LCD_SCE		PORTA_PA3
#define LCD_RST   PORTA_PA4
#define LCD_DC		PORTA_PA2
#define LCD_SDIN	PORTA_PA1
#define LCD_SCLK	PORTA_PA0

#define com         0
#define data		1

void send_comordata(unsigned char Data,unsigned char Com);
void LCD_POS(unsigned char X,unsigned char Y);
void LCD_clear(void);
void display_hanzi(unsigned char A,unsigned char X,unsigned char Y);
void display_zimu(unsigned char A,unsigned char X,unsigned char Y);
void display_shuzi(unsigned char A,unsigned char X,unsigned char Y);
void LCD_init(void);
                    

#endif        