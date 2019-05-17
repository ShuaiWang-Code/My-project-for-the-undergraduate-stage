//ͷ�ļ�
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "PLL.h"
#include "PWM.h"
#include "port.h"
#include "NBCTFT.h"
#include "interface.h"
#include "pit.h"
#include "tuoluo.h"


unsigned int intr,sec;
unsigned int Device_code;

int xv,yv,zv;
unsigned char devid;
float Roll,Pitch,Q,T,K;

void io_init() 
{
    DDRH = 0XFF;
    DDRE = 0XFF;
}

void main(void) 
{
    DisableInterrupts
    
    io_init();
    PLL_init();
    PWM_init();
    PORT_init();
    PIT_Init();
    Device_code=0x9328;
    TFT_Initial();
    
    
	EnableInterrupts;
	delay_1ms(8);
    Init_BH1750(); 
    //devid=Single_Read_ADXL345(0X00); 
    
  for(;;) 
  {
      //interface_init();
      Single_Write_BH1750(0x01);   // power on
      Single_Write_BH1750(0x10);
      delay_1ms(200);
      
      Multiple_read_BH1750();
	   xv=BUF[0];
       xv=(xv<<8)+BUF[1];  
	 
     
       Q=(float)xv/1.2;
       yv=(int)Q;
         
  } /* loop forever */
  /* please make sure that you never leave main */
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED //ָʾ�ó����ڲ���ҳ��
void interrupt 66 PIT0(void)//��ʱ��0 �жϷ�����
{
        intr++;
        if(intr==1000)
{          //��?��3?�㨦????��
        sec++;
        LCD_PutChar(90, 300, 0x30+(unsigned int)Roll/100, Black, Red);
        LCD_PutChar(98, 300, 0x30+(unsigned int)Roll%100/10, Black, Red);
        LCD_PutChar(106, 300, 0x30+(unsigned int)Roll%10, Black, Red);
         //PORTA_PA0=~PORTA_PA0;//A0 LED ��ת��T=1S
         intr=0;
}
PITTF_PTF0=1;//���жϱ�־λ
}
