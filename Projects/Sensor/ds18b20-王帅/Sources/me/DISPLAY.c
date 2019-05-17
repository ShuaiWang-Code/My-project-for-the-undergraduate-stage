#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>
#pragma LINK_INFO DERIVATIVE "mc9s12xs128"
#include "DS18B20.h"
#include "DELAY.h"
#include "LCD.h"

extern unsigned char  temp1;                        //采集到的温度高8位
extern unsigned char  temp2;                        //采集到的温度低8位
const unsigned char tablexiao[16]={0,0,1,2,2,3,4,4,5,6,6,7,8,8,9,9};
extern unsigned char a;                         
void display(void)
{
    convert_T();
		delay(100);
		read_T();  
		if(temp1>99) temp1=0;			 
		if(temp2>15) temp2=0;
		
		display_hanzi(0,0,0);             //当
		display_hanzi(1,1,0);             //前
		display_hanzi(2,2,0);             //温
		display_hanzi(3,3,0);             //度
		
		display_shuzi(temp1/10,2,3);	    //0
		display_shuzi(temp1%10,3,3);	    //x
		display_shuzi(10,4,3);		//.
		display_shuzi(tablexiao[temp2],5,3);	    //0
	
		display_hanzi(3,4,3);             //℃  
		
//		display_shuzi(a,6,3);	
}