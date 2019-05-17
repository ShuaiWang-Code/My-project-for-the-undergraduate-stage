#include <reg52.h>

#define uint unsigned int  
#define uchar unsigned char 

typedef bit BOOL  ;  

sbit io = P1^0 ; 
sbit rs = P2^6 ;  
sbit rw = P2^5 ; 
sbit ep = P2^7 ; 

uchar data_byte; 
uchar RH,RL,TH,TL; 

void delay(uchar ms) 
{      	
		uchar i ; 
  	  	while(ms--) 
		{ 
    		for(i=0;i<250;i++); 
  		} 
} 

void delay1()//10us 
{ 
		 uchar i; 
		 i--; 		
		 i--; 		
		 i--; 		
		 i--; 		
		 i--; 		
		 i--; 
} 

void longdelay(uchar s) //长延时 
{ 
		  while(s--) 
		  { 
		    delay(90) ; 
		  }  
} 

BOOL lcd_bz()//测试LCD忙碌状态 
{       
		  BOOL result ; 
		  rs = 0 ; 
		  rw = 1 ; 
		  ep = 1 ; 
		  result = (BOOL)(P0 & 0x80) ; 
		  ep = 0 ; 
		  return result ;  
} 

 

void write_cmd(uchar cmd)// xie
{        
		 while(lcd_bz()) ; 		
		 rs = 0 ; 		
		 rw = 0 ; 		
		 ep = 0 ; 		
		 P0 = cmd ; 		
		 ep = 1 ; 		
		 ep = 0 ;   
}

void write_addr(uchar addr)//address 
{        
  		write_cmd(addr|0x80) ; 
} 

void write_byte(uchar dat)//dat
{       

  		while(lcd_bz()) ; 
   		rs = 1 ; 
   		rw = 0 ; 
   		ep = 0 ; 
   		P0 = dat ; 
   		ep = 1 ; 
   		ep = 0 ;  
} 


void lcd_init() 	 //2
{        
		  write_cmd(0x38) ;  
		  delay(3); 
		  write_cmd(0x08) ;   
		  delay(3); 
		  write_cmd(0x01) ;  
		  delay(3); 
		  write_cmd(0x06) ; 
		  delay(3); 
		  write_cmd(0x0c) ;  
		  delay(3);
} 

 

void display(uchar addr, uchar q) 
{    

		  delay(15) ; 					   //10		
		  write_addr(addr) ; 		
		  write_byte(q) ; 		
		  longdelay(2) ; 				   //2
} 

/******************************************************************************

******************************* 

************************************************ DHT11测试模块

***********************************************/ 

 

void start()//开始信号 
{ 
		 io=1; 
		 delay1();  
		 delay1(); 
		 
		 io=0; 
		 delay(40);//>18ms 		  //20

		 io=1; 
		 delay1();//20-40us 
		 delay1(); 
		 delay1(); 
		 delay1();
		 delay1(); 
		 delay1(); 			//
		 delay1(); 

} 

uchar receive_byte()//接收一个字节 
{ 
		 uchar i,temp,count; 
		 for(i=0;i<8;i++) 
		 { 
				  count=2; 
				  while((!io)&&count++)//等待50us低电平结束 
				  temp=0; 
				  delay1();delay1();delay1();delay1(); delay1(); delay1();delay1();delay1(); delay1(); //4
				
				  if(io==1)		
				  temp=1; 

				  count=2; 
				  while((io)&&count++); 
				  if(count==1)break; 
				  data_byte<<=1;  
				  data_byte|=temp; 
		  } 
		 
		 return data_byte; 

} 

void receive()//接收数据 
{ 
		 uchar T_H,T_L,R_H,R_L,check,num_check; 
		 uchar count; 
		 start();//开始信号 
		 io=1; 
		 if(!io)//读取DHT11响应信号 
		 { 
				 count=2; 
				 while((!io)&&count++);//DHT11高电平80us是否结束 
				 count=2;
				  
				 while((io)&&count++); 
				 R_H=receive_byte(); 
				 R_L=receive_byte(); 
				 T_H=receive_byte(); 
				 T_L=receive_byte(); 
				 check=receive_byte();
				  
				 io=0;//拉低延时50us 
				 delay1();delay1();delay1();delay1();delay1(); delay1();delay1();delay1(); delay1();  
				 
				 io=1; 
				 num_check=R_H+R_L+T_H+T_L; 
				 
				 if(num_check=check) 
				 { 
						  RH=R_H; 
						  RL=R_L; 
						  TH=T_H; 
						  TL=T_L; 
						  check=num_check; 
				 } 
		
		 } 

} 

void display_lcd1602()
{
		   receive(); 

   			delay(200); 

   			display(0x00,'R') ; 

   			display(0x01,':'); 

   			display(0x02,RH/10+0x30); 

   			display(0x03,RH%10+0x30); 

   			display(0x04,'%'); 

   			display(0x40,'T') ; 

   			display(0x41,':'); 

   			display(0x42,TH/10+0x30); 

   			display(0x43,TH%10+0x30); 

   			display(0x44,0xdf); 

   			display(0x45,0x43);
			
			display(0x06,'L');
			display(0x07,'i');
			display(0x08,'g');
			display(0x09,'h');
			display(0x0a,'t');
			display(0x0b,':');
}

/******************************************************************************

**************************** 

*************************************************主函数

***************************************************/ 

void main() 
{  

  	lcd_init(); 
 	delay(20); 
 	while(1) 
 	{ 
			display_lcd1602();
 	} 

}
