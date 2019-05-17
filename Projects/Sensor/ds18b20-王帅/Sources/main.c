/********************************************/
/************ wang-shuai ************/
/************* 移植于2017/7/30*************/
/********************************************/

#include <hidef.h>     
#include <MC9S12XS128.h>
#include "BUSCLOCK.h"
#include "DELAY.h"
#include "DS18B20.h"
#include "PORT.H"



unsigned char wendu,wendu1;//wendu 整数位 wendu1 小数位
extern unsigned char temp1,temp2;  



void main(void) 
{
   
   
          SetBusCLK_64M();
          PORT_INIT();

          EnableInterrupts;
          
          for(;;)
          {
                
            	receive_temp();
                wendu = temp1;//小数位temp2         
                _FEED_COP();                
          } 
 
}
