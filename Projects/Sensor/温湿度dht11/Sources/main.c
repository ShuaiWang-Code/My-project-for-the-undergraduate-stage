#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "pll.h"
#include "dht11.h"

unsigned int th,t,h;


void main(void) {
  /* put your own code here */
  
    PLL_init();

	EnableInterrupts;


  for(;;) {
                    th=getDHT11();//��ȡ��ʪ��
                    t=th/100;//�¶�
                    h=th%100;//ʪ��
                    delay_1ms(200);
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
