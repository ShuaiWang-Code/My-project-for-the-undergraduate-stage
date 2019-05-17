#ifndef _TFT_H
#define _TFT_H






  /*******************�ӿڶ���******************************/
#define	ILI9163_RESET PORTA_PA0 
#define	ILI9163_A0		PORTA_PA1
#define	ILI9163_SDA   PORTA_PA2
#define	ILI9163_SCK  	PORTA_PA3
#define	ILI9163_CS  	PORTA_PA4

#define		RED			0xf800
#define		GREEN		0x07e0
#define		BLUE		0x001f
#define		PURPLE	0xf81f
#define		YELLOW	0xffe0
#define		CYAN		0x07ff 		//����ɫ
#define		ORANGE	0xfc08
#define		BLACK		0x0000
#define		WHITE		0xffff


#define uint8 	unsigned char
#define uint16 	unsigned short int
#define uint32	unsigned long int
#define int8  	signed char
#define int16	  signed short int
#define int32 	signed long int
#define uint64	unsigned long long int
#define int64  	signed long long int



/*****************˽�к�������*********************************/

void ILI9163B_init(void);									//LCD��ʼ��

void ILI9163B_write_command(uint8 cmd);						//���Ϳ�����

void ILI9163B_write_para8(uint8 dat);						//�������ݲ���

void ILI9163B_write_para16(uint16 dat);						//����������ʾ����

void ILI9163B_address_rst(void);							//DDRAM��ַ����

void ILI9163B_SetPos(uint8 xs,uint8 ys,uint8 xe,uint8 ye);	//��λ��ʾ����λ��

void delay(uint16 t);									   	//��ʱ����

void ILI9163B_display_full(uint16 color);					//ȫ����ʾĳ����ɫ


void ILI9163B_draw_part(uint8 xs,uint8 ys,uint8 xe,uint8 ye,uint16 color_dat);
															//��������������ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ

void ILI9163B_draw_line(uint8 xs,uint8 ys,uint8 xe,uint8 ye,uint16 color_dat);
															//���ߣ�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ

void ILI9163B_draw_rectangle(uint8 xs,uint8 ys,uint8 xe,uint8 ye,uint16 color_dat);
															//�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ

void ILI9163B_draw_circle(uint8 x,uint8 y,uint8 r,uint16 color_dat);
															//��Բ�α߿�Բ�ĺ����ꡢ�����꣬�뾶����ɫ

void ILI9163B_draw_dot(uint8 x,uint8 y,uint16 color_dat);	//���㣬�����꣬�����꣬��ɫ



void LCD_printc16(uint8 x, uint8 y, uint8 c_dat,uint16 word_color,uint16 back_color);

void LCD_prints16(uint8 x, uint8 y, uint8 *s_dat,uint16 word_color,uint16 back_color);

void LCD_printc6(uint8 x, uint8 y, uint8 c_dat,uint16 word_color,uint16 back_color);

void LCD_prints6(uint8 x, uint8 y, uint8 *s_dat,uint16 word_color,uint16 back_color);

void LCD_printn6(uint8 x, uint8 y, uint16 num, uint8 num_bit,uint16 word_color,uint16 back_color);

void LCD_printc(uint8 x, uint8 y, uint8 c_dat,uint16 word_color,uint16 back_color);

void LCD_prints(uint8 x, uint8 y, uint8 *s_dat,uint16 word_color,uint16 back_color);

void LCD_printn(uint8 x, uint8 y, uint16 num, uint8 num_bit,uint16 word_color,uint16 back_color);

void LCD_printc7(uint8 x, uint8 y, uint8 c_dat,uint16 word_color,uint16 back_color);
 
void LCD_bianliang(uint8 x, uint8 y, int b,uint16 word_color,uint16 back_color);
 
void LCD_yanshi(void);

#endif