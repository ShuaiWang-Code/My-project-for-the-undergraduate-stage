/********************************************************************
                            汇诚科技
实现功能:此版配套测试程序
使用芯片：AT89S52
晶振：11.0592MHZ
波特率：9600
     
*********************************************************************/
/********************************************************************
说明：1、	当测量有雨滴时，单片机IO口输出低电平
*********************************************************************/
#include<reg52.h>  	       //库文件
#define uchar unsigned char//宏定义无符号字符型
#define uint unsigned int  //宏定义无符号整型


typedef bit BOOL  ;  
uchar data_byte; 


uchar str[14]="c000000000S00E";

/********************************************************************
                            I/O定义
*********************************************************************/
sbit delay_MQ=P0^4;	 //定义单片机P1口的第1位 （即P0.0）为开关端

sbit beep=P0^6;
sbit out =P0^1;
sbit delay_door=P0^3;
sbit delay_curtain=P0^2;
sbit DOUT=P2^0;	 //定义单片机P2口的第1位 （即P2.0）为传感器的输入端
/********************************************************************
                            函数
*********************************************************************/
void delay();
void SerialInti();
void Uart1Sends(uchar *str);
void protocol_select();
void protocol_model();
void io_init();
uchar rx[14],rx_cnt=0,flag_start=0,flag_control=0,start0=0,start1=0;                        
/*********************************************************************/
void main()
{
	SerialInti();
	io_init();
	while(1)   //无限循环
	{
		protocol_select();

	}
}

void io_init()
{
		delay_MQ=0;
		beep=0;
		delay_door=0;
		delay_curtain=0;
		//out=0;
}

void protocol_select()
{
		if(flag_start==1)
		{
				flag_start=0;
				start0=1;

				if(DOUT==0)
			 	{
		    		delay();//延时抗干扰
					if(DOUT==0)//确定 浓度高于设定值时 ，执行条件函数
			    	{
				 		delay_MQ=1;	   //闭合常开开关
						beep=1;
						str[1]=1+0X30;
					}
			 	}
		
				if(DOUT!=0)
				{
						delay_MQ=0;
						beep=0;
						str[1]=0+0X30;
				}

				if(out)
				{
					str[2]=1+0x30;
				} 
				else
				{ 
					str[2]=0+0x30;
				}

				Uart1Sends(str);
					
				rx[0] ='0';
				rx[10]='0';
				rx[13]='0';
		}
		if(start0==1)
		{
				if(DOUT==0)
			 	{
		    		delay();//延时抗干扰
					if(DOUT==0)//确定 浓度高于设定值时 ，执行条件函数
			    	{
				 		delay_MQ=1;	   //闭合常开开关
						beep=1;
						str[1]=1+0X30;
					}
			 	}
		
				if(DOUT!=0)
				{
						delay_MQ=0;
						beep=0;
						str[1]=0+0X30;
				}

				if(out)
				{
					str[2]=1+0x30;
				} 
				else
				{ 
					str[2]=0+0x30;
				}
		}

		if(flag_control==1)
		{
				flag_control=0;
				start1=1;

				if(rx[1]=='1')	   // 开排气扇
				{
						delay_MQ=1;
						beep=0;
						str[1]=1+0x30;		
				}
				
				if(rx[1]=='0')			  //关
				{
						delay_MQ=0;
						beep=0;
						str[1]=0+0x30;
				}

				if(rx[3]=='1')	   // 
				{
						delay_door=1;
					//	beep=0;
						str[3]=1+0x30;		
				}
				
				if(rx[3]=='0')			  //关
				{
						delay_door=0;
					//	beep=0;
						str[3]=0+0x30;
				}

				if(rx[4]=='1')	   // 
				{
						delay_curtain=1;
					//	beep=0;
						str[4]=1+0x30;		
				}
				
				if(rx[4]=='0')			  //关
				{
						delay_curtain=0;
					//	beep=0;
						str[4]=0+0x30;
				}

				
				if(out)
				{
					str[2]=1+0x30;
				} 
				else
				{ 
					str[2]=0+0x30;
				}
				


				Uart1Sends(str);
					
				rx[0] ='0';
				rx[10]='0';
				rx[13]='0';

		}

		if(start1==1)
		{
				if(rx[1]=='1')	   // 开排气扇
				{
						delay_MQ=1;
						beep=0;	
						str[1]=1+0x30;	
				}
				
				if(rx[1]=='0')			  //关
				{
						delay_MQ=0;
						beep=0;
						str[1]=0+0x30;
				}

				if(rx[3]=='1')	   // 
				{
						delay_door=1;
					//	beep=0;
						str[3]=1+0x30;		
				}
				
				if(rx[3]=='0')			  //关
				{
						delay_door=0;
					//	beep=0;
						str[3]=0+0x30;
				}

				if(rx[4]=='1')	   // 
				{
						delay_curtain=1;
					//	beep=0;
						str[4]=1+0x30;		
				}
				
				if(rx[4]=='0')			  //关
				{
						delay_curtain=0;
					//	beep=0;
						str[4]=0+0x30;
				}

				
				if(out)
				{
					str[2]=1+0x30;
				} 
				else
				{ 
					str[2]=0+0x30;
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
				if(rx[0]== 'C')
				{
						rx_cnt++;
						if(rx_cnt>=14)
						{
								if(rx[0]=='C' && rx[10]=='S'&&rx[13]=='E')
								{
										flag_start=1;	start1=0;	rx_cnt=0;	
								}
								if(rx[0]=='C' && rx[10]=='M'&&rx[13]=='E')
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

void delay()//延时程序
{
uchar m,n,s;
for(m=20;m>0;m--)
for(n=20;n>0;n--)
for(s=248;s>0;s--);
}

void SerialInti()//初始化程序（必须使用，否则无法收发）
{	TMOD = 0x20;
    SCON = 0x50;
    TH1 = 0xFD;
    TL1 = TH1;
    PCON = 0x00;
    EA = 1;
    ES = 1;
    TR1 = 1;		//启动定时器1
    
}	
/********************************************************************
                              结束
*********************************************************************/