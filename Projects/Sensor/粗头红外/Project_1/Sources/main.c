#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "pll.h"
unsigned int x;

void port()
{
    DDRA=0X00;
}


void main(void) {
  /* put your own code here */
  
                 
    PLL_init();
    port();
	EnableInterrupts;


  for(;;)
{
     x=PORTA_PA0;
     
    _FEED_COP(); /* feeds the dog */
} /* loop forever */
  /* please make sure that you never leave main */
}
