#ifndef __DS18B20__
#define __DS18B20__


#define DQ     PORTB_PB7                      //定义18B20数据端口
#define DQ_DIR DDRB_DDRB7                        //定义18B20D口方向寄存器
#define DQ_HIGH() DDRB_DDRB7=0                   //设置数据口为输入
#define DQ_LOW() PORTB_PB7 = 0; DDRB=0xff           //设置数据口为输出

unsigned char reset(void);
void write_byte(unsigned char  val);
unsigned char read_byte(void);
void convert_T(void) ;
void read_T(void) ;
void receive_temp(void);


#endif        