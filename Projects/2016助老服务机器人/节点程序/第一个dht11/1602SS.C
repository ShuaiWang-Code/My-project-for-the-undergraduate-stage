#include <reg52.h>

#define uint unsigned int  
#define uchar unsigned char 

typedef bit BOOL  ;  

sbit io = P2^0 ; 
sbit door = P1^7;
sbit beep = P0^6;
sbit delay_fs=P0^5;
sbit delay_td=P0^4;
 
uchar data_byte; 
uchar RH,RL,TH,TL;
uchar T_H,T_L,R_H,R_L,check,num_check; 
uchar count; 
uchar rx[14],rx_cnt=0,flag_start=0,flag_control=0,start0=0,start1=0;

uchar str[14]="a010199990S00E";
uchar str1[14]="00000000000001";
 
unsigned int time=0;

extern void Init_BH1750(void);
extern uchar   ge,shi,bai,qian,wan;
extern get_bh1750();
extern float temp;


void delay(uchar ms) ;
void delay1();
void Uart1Sends(uchar *str);
void io_init();
void start();
uchar receive_byte();
void receive();
void SerialInti();

void protocol_model();
void protocol_select();
void get_info();
/******************************************************************************

**************************** 

**********************主函数

***************************************************/
 

void main() 
{  
	SerialInti();
	Init_BH1750();  
	io_init();
 	delay(20); 
 	while(1) 
 	{ 		
			get_info();
			protocol_select();	
 	} 

}
void get_info()
{
		   	receive(); 
	   		delay(100); 
			get_bh1750();
			delay(100);
}

void protocol_select()
{

		   if(flag_start==1)
			{	 
					start0=1;
					flag_start=0;

					if(TH>35)
					{
							delay_fs=1;
							str[11]=1+0x30;
					}
					if(TH<=35)
					{
							delay_fs=0;
							str[11]=0+0x30;
					}
					
					if(temp<20)
					{
						time++;
						if(time>22)
						{
							time=0;
							delay_td=1;
							str[12]=1+0x30;
						}
						
					}
					else
					{
						delay_td=0;
						str[12]=0+0x30;
					}

					if(door==1)
					{
		
						beep=1;
						str[9]=1+0x30;
					}
					else
					{
		
						beep=0;
						str[9]=0+0x30;
					}

					Uart1Sends(str);
					
					rx[0] ='0';
					rx[10]='0';
					rx[13]='0';

			}
			
			if(start0==1)
			{
					if(TH>35)
					{
							delay_fs=1;
							str[11]=1+0x30;
					}
					if(TH<=35)
					{
							delay_fs=0;
							str[11]=0+0x30;
					}
					
					if(temp<20)
					{
						time++;
						
						if(time>22)
						{
								time=0;
								delay_td=1;
								str[12]=1+0x30;
						}
						
					}
					else
					{
						delay_td=0;
						str[12]=0+0x30;
					}

					if(door==1)
					{
		
						beep=1;
						str[9]=1+0x30;
					}
					else
					{
		
						beep=0;
						str[9]=0+0x30;
					}	
			}

			if(flag_control==1)
			{
					flag_control=0;
					start1=1;
					
					if(rx[11]=='1')	   // 风扇
					{
						delay_fs=1;
						str[11]=1+0x30;		
					}

					if(rx[11]=='0')			  //关风扇
					{
						delay_fs=0;
						str[11]=0+0x30;
					}

					if(rx[12]=='1')	   //台灯
					{
						delay_td=1;
						str[12]=1+0x30;	
					}
					if(rx[12]=='0')
					{
						delay_td=0;
						str[12]=0+0x30;	
					}

					if(door==1)
					{
		
						beep=1;
						str[9]=1+0x30;
					}
					else
					{
		
						beep=0;
						str[9]=0+0x30;
					}
					Uart1Sends(str);
					
					rx[0] ='0';
					rx[10]='0';
					rx[13]='0';


			}
			if(start1==1)
			{		
					
					if(rx[11]=='1')	   // 风扇
					{
						delay_fs=1;
						str[11]=1+0x30;		
					}

					if(rx[11]=='0')			  //关风扇
					{
						delay_fs=0;
						str[11]=0+0x30;
					}

					if(rx[12]=='1')	   //台灯
					{
						delay_td=1;
						str[12]=1+0x30;	
					}
					if(rx[12]=='0')
					{
						delay_td=0;
						str[12]=0+0x30;	
					}

					if(door==1)
					{
		
						beep=1;
						str[9]=1+0x30;
					}
					else
					{
		
						beep=0;
						str[9]=0+0x30;
					}
					
			}
}


void Serial_interrupt() interrupt 4 
{

		protocol_model();
		
}

void protocol_model()
{
		if(RI)
		{
				RI=0;
				rx[rx_cnt]=SBUF;
				if(rx[0]== 'A')
				{
						rx_cnt++;
						if(rx_cnt>=14)
						{
								if(rx[0]=='A' && rx[10]=='S'&&rx[13]=='E')
								{
										flag_start=1;	start1=0;		rx_cnt=0;	
								}
								
								if(rx[0]=='A' && rx[10]=='M'&&rx[13]=='E')
								{
									
										flag_control=1;	start0=0;	rx_cnt=0;
								}			
										
								rx_cnt=0;
						}
				}
				else
				{
						rx_cnt=0;
				}

		}

		if(TI)
		{
			TI=0;
		}	
}

//串行口连续发送char型数组，遇到终止号/0将停止
void Uart1Sends(uchar *str)
{
	unsigned char *p;
    
    p = str;
    while(*p != '\0')
    {
        SBUF = *p;
		while(TI == 0); 
		TI = 0;
        p++;
    }
}

void io_init()
{
		delay_fs=0;
		delay_td=0;
		beep=0;
}
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
		 //uchar T_H,T_L,R_H,R_L,check,num_check; 
		 //uchar count; 
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
						  str[1]= RH/10+0x30;
						  str[2]= RH%10+0x30;
						  str[3]= TH/10+0x30;
						  str[4]= TH%10+0x30;
				 } 
		
		 } 

} 



void SerialInti()//初始化程序（必须使用，否则无法收发）
{	
		TMOD = 0x20;
	    SCON = 0x50;
	    TH1 = 0xFD;
	    TL1 = TH1;
	    PCON = 0x00;
	    EA = 1;
	    ES = 1;
	    TR1 = 1;		//启动定时器1
    
}

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
