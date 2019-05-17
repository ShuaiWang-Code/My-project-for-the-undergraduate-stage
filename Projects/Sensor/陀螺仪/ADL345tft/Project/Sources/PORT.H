#ifndef _PORT_H_
#define _PORT_H_
#include <hidef.h>     
#include "derivative.h"
void PORT_init(void)
{
    DDRA = 0XFF;
    //PORTA=0XAA;

    
    DDRB_DDRB0=1;
    PORTB_PB0=1;
    
    DDRB_DDRB1=1;
    PORTB_PB1=0;
    
}
#endif