#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>
#pragma LINK_INFO DERIVATIVE "mc9s12xs128"

void PORT_INIT(void)
{
  DDRE=0xff;
  DDRM=0xff;               
  DDRP=0xff;                       
  DDRT=0x7f;                       
  DDRH=0xff;
  DDRS=0xff;                
  DDRJ=0xff;            
  DDRK=0xff;
  DDRB=0xff;
  PORTB=0;                   
  PORTE=0xff;                             
  DDRA=0xff;
  PORTA=0;  
}                  