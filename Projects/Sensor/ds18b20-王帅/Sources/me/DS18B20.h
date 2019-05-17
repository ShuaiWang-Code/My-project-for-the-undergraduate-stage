#ifndef __DS18B20__
#define __DS18B20__


#define DQ     PORTB_PB7                      //����18B20���ݶ˿�
#define DQ_DIR DDRB_DDRB7                        //����18B20D�ڷ���Ĵ���
#define DQ_HIGH() DDRB_DDRB7=0                   //�������ݿ�Ϊ����
#define DQ_LOW() PORTB_PB7 = 0; DDRB=0xff           //�������ݿ�Ϊ���

unsigned char reset(void);
void write_byte(unsigned char  val);
unsigned char read_byte(void);
void convert_T(void) ;
void read_T(void) ;
void receive_temp(void);


#endif        