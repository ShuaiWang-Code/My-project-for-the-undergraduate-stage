/********************************************/
/************ wang-shuai ************/
/************* ��ֲ��2017/7/30*************/
/********************************************/

#include <hidef.h>     
#include <MC9S12XS128.h>
#include "BUSCLOCK.h"
#include "DELAY.h"
#include "DS18B20.h"
#include "PORT.H"



unsigned char wendu,wendu1;//wendu ����λ wendu1 С��λ
extern unsigned char temp1,temp2;  



void main(void) 
{
   
   
          SetBusCLK_64M();
          PORT_INIT();

          EnableInterrupts;
          
          for(;;)
          {
                
            	receive_temp();
                wendu = temp1;//С��λtemp2         
                _FEED_COP();                
          } 
 
}
