#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>
#pragma LINK_INFO DERIVATIVE "mc9s12xs128"
#include "KEYSCAN.h"

unsigned char keyout;
unsigned char keycon;
unsigned char keybit;
unsigned char keybuf;
unsigned char temp;
unsigned long int  result;


/////////////////////////////键盘扫描函数/////////////////////////////
unsigned char key(void)
{
	keyO1=0;
	keyO2=1;
	keyO3=1;	
	asm("NOP");	
	asm("NOP");
	asm("NOP");	
	asm("NOP");	
	if(keyI1==0)
	{		
		return 1;
				
	}
	else if(keyI2==0)
	{
		return 2;
	
	}
	else if(keyI3==0)
	{
		return 3;
	
	}
	else if(keyI4==0)
	{
		return 4;
	
	}
	temp=PORTA;
	temp=temp&0xf0;
	while(temp!=0xf0)
	{
  	temp=PORTA;
  	temp=temp&0xf0;
	
	}
	
	keyO1=1;
	keyO2=0;
	keyO3=1;	
	asm("NOP");	
	asm("NOP");
	asm("NOP");	
	asm("NOP");	
	if(keyI1==0)
	{		
		return 5;
	
	}
	else if(keyI2==0)
	{
		return 6;
		
	}
	else if(keyI3==0)
	{
		return 7;
	
	}	
	else if(keyI4==0)
	{
		return 8;
	
	}
	temp=PORTA;
	temp=temp&0xf0;
	while(temp!=0xf0)
	{
  	temp=PORTA;
  	temp=temp&0xf0;
	
	}
	
	keyO1=1;
	keyO2=1;
	keyO3=0;	
	asm("NOP");	
	asm("NOP");
	asm("NOP");	
	asm("NOP");	
	if(keyI1==0)
	{		
		return 9;
	
	}
	else if(keyI2==0)
	{
		return 10;
	
	}
	else if(keyI3==0)
	{
		return 11;
	
	}
	else if(keyI4==0)
	{
		return 12;
	
	}
	temp=PORTA;
	temp=temp&0xf0;
	while(temp!=0xf0)
	{
  	temp=PORTA;
  	temp=temp&0xf0;
	
	}
	
	return 0;
}
//---------------------------------------
//名称: 按键处理函数
//作者：cby
//网站：宁波单片机开发网
//网址：www.nbdpj.com
//邮箱：nbdpj@nbdpj.com
//日期：20081216  
//----------------------------------------- 
void keypro(void)
{
	
	keybuf=key();
	if(keybuf==0)
	{
	  keyout=13;
		if(keybit==0)
		{
			if(++keycon>5)
			{
				keycon=0;
				keybit=1;
	//			diaplay_shuzi(0,1,1);	
			}	
		}	
	}
	else if(keybuf==1)
	{
		if(keybit==1)
		{
			keybit=0;
			keyout=10;			
//	  	display_hanzi(0,1,1);
		}	
	}	
	else if(keybuf==2)
	{
		if(keybit==1)
		{
			keybit=0;
			keyout=7;				
//			diaplay_shuzi(7,1,1);
		}	
	}
	else if(keybuf==3)
	{
		if(keybit==1)
		{
			keybit=0;
			keyout=4;					
//			diaplay_shuzi(4,1,1);
		}	
	}	
	else if(keybuf==4)
	{
		if(keybit==1)
		{
			keybit=0;
			keyout=1;				
//			diaplay_shuzi(1,1,1);
		}	
	}	
	else if(keybuf==5)
	{
		if(keybit==1)
		{
			keybit=0;
			keyout=0;					
//			diaplay_shuzi(0,1,1);
		}	
	}
	else if(keybuf==6)
	{
		if(keybit==1)
		{
			keybit=0;
			keyout=8;				
//			diaplay_shuzi(8,1,1);
		}	
	}
	else if(keybuf==7)
	{
		if(keybit==1)
		{
			keybit=0;
			keyout=5;				
//			diaplay_shuzi(5,1,1);
		}	
	}
	else if(keybuf==8)
	{
		if(keybit==1)
		{
			keybit=0;
			keyout=2;			
//			diaplay_shuzi(2,1,1);
		}	
	}
	else if(keybuf==9)
	{
		if(keybit==1)
		{
			keybit=0;
			keyout=11;				
//		  display_hanzi(1,1,1);
		}	
	}
	else if(keybuf==10)
	{
		if(keybit==1)
		{
			keybit=0;
			keyout=9;				
//		  diaplay_shuzi(9,1,1);
		}	
	}
	else if(keybuf==11)
	{
		if(keybit==1)
		{
			keybit=0;
			keyout=6;				
//			diaplay_shuzi(6,1,1);
		}	
	}                                     
	else if(keybuf==12)
	{
		if(keybit==1)
		{                                           
			keybit=0;
			keyout=3;				
//			diaplay_shuzi(3,1,1);
		}	
	}
	else
	{
		keybit=0;	
	}
}
void keyswait(void)
{
  	temp=PORTA;
  	temp=temp&0xf0;
  	while(temp!=0xf0)
  	{
    	temp=PORTA;
    	temp=temp&0xf0;
  	
  	}
}
