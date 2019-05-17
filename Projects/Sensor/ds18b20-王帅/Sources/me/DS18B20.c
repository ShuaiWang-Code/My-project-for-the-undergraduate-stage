#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>
#pragma LINK_INFO DERIVATIVE "mc9s12xs128"
#include "DS18B20.h"
#include "DELAY.h"

unsigned char  temp1;                        //�ɼ������¶ȸ�8λ
unsigned char  temp2;                         //�ɼ������¶ȵ�8λ
unsigned char a;

//����: ��λDS18B20����

unsigned char reset(void)
{
  	unsigned char outbit;
	  DQ_HIGH(); 
	  delayus(1);
  	DQ_LOW() ;                                //���������͵�ƽ
    delayus(8000);                              //��ʱ503us
    DQ_HIGH();                                //�ͷ����ߵȵ�����������,������15~60us
    delayus(1000);                               //��ʱ70us
    if(DQ==1) outbit=0;                     //û�н��յ�Ӧ���źţ�������λ
    else  outbit=1;
    //���յ�Ӧ���ź�
    delayus(600);                              //��ʱ430us 
    return outbit;  	
}

//����: д�ֽں���

void write_byte(unsigned char  val)
{
 unsigned char i;
 unsigned char temp;
 for(i=8;i>0;i--)
 {
   temp=val&0x01;                            //���λ�Ƴ�
   DQ_LOW();
   delayus(125);
   if(temp==1)  DQ_HIGH();                   //���д1,���ߵ�ƽ
   delayus(410);                               //��ʱ63us
   DQ_HIGH();
   _asm(nop); 
   _asm(nop); 
   val=val>>1;                               //����һλ
  }
}
//����: ���ֽں���

unsigned char read_byte(void)
{
 unsigned char i;
 unsigned char value=0;                                //�����¶�
 unsigned char j;
 for(i=8;i>0;i--)
 {
   value>>=1;
 
   DQ_LOW();
   delayus(50);
   DQ_HIGH();
   delayus(30);
   j=DQ;
   if(j) value|=0x80;
   delayus(500);                        //63us
  }
  return(value);
}

//����: �������¶Ⱥ���

void convert_T(void) 
{ 
  if(reset()==1) 
	{  
        write_byte(0xcc);     // ����������ʶ�� 
        write_byte(0x44);     // �����¶�ת�� 
  } 
} 

//����: ���¶Ⱥ���

void read_T(void) 
{ 
    unsigned char Lsb,Msb;            
    if(reset()==1) 
	{ a=0; 
        write_byte(0xcc);      // ����������ʶ�� 
        write_byte(0xbe);      // ���ݴ��� 
        Lsb=read_byte();       // ���ֽ� 
        Msb=read_byte();  	   // ���ֽ� 
		temp2=Lsb&0x0f;
		temp1=(Lsb>>4)|(Msb<<4);
  } else a=1; 
} 

void receive_temp(void)
{
                convert_T();
            	delay(100);
            	read_T();
}