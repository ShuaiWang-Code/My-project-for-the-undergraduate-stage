#ifndef _PORT_H_
#define _PORT_H_
#include <hidef.h>     
#include "derivative.h"

void io_init()     //TFT¶Ë¿Úio³õÊ¼»¯
{
    DDRH = 0XFF;
    DDRE = 0XFF;
} 

#endif
