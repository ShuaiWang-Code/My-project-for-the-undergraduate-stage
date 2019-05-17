/*********************************************************************/
/********************************************************************
说明：1、	当测量有雨滴时，单片机IO口输出低电平
*********************************************************************/
#include<reg52.h>  	       //库文件

#define uchar unsigned char//宏定义无符号字符型
#define uint unsigned int  //宏定义无符号整型

typedef bit BOOL  ;  
uchar data_byte; 
uchar str[14]="b000000000S00E";

sbit delay_yudi=P0^4;	 //定义单片机P1口的第1位 （即P0.0）为开关端
sbit delay_1=P0^0;
sbit delay_2=P0^1;
sbit beep=P0^6;
sbit DOUT=P2^0;	 //定义单片机P2口的第1位 （即P2.0）为传感器的输入端 

void delay();
void SerialInti();
void Uart1Sends(uchar *str);
void protocol_model();
void protocol_select();
void io_init();
uchar rx[14],rx_cnt=0,flag_start=0,flag_control=0,start0=0,start1=0;




void main()
{
	SerialInti();
	io_init();
	while(1)  
	{
		
	 	protocol_select();	

	}
}

void io_init()
{
		delay_yudi=0;
		beep=0;
		delay_1=0;
		delay_2=0;
}


void protocol_select()
{
		if(flag_start==1)
		{	   
				flag_start=0;
				start0=1;

			 	if(DOUT==0)//当有水滴时 ，执行条件函数
			 	{
		    		delay();//延时抗干扰
					if(DOUT==0)//确定 浓度高于设定值时 ，执行条件函数
			    	{
				 		delay_yudi=1;	   //闭合常开开关
						beep=1;
						str[1]=1+0X30;
					}
			 	}
		
				if(DOUT!=0)
				{
						delay_yudi=0;
						beep=0;
						str[1]=0+0X30;
				}

				Uart1Sends(str);
					
				rx[0] ='0';
				rx[10]='0';
				rx[13]='0';	
		}

		if(start0==1)
		{
				if(DOUT==0)//当有水滴时 ，执行条件函数
			 	{
		    		delay();//延时抗干扰
					if(DOUT==0)//确定 浓度高于设定值时 ，执行条件函数
			    	{
				 		delay_yudi=1;	   //闭合常开开关
						beep=1;
						str[1]=1+0X30;
					}
			 	}
		
				if(DOUT!=0)
				{
						delay_yudi=0;
						beep=0;
						str[1]=0+0X30;
				}
		}

			if(flag_control==1)
			{
					flag_control=0;
					start1=1;
					
					if(rx[1]=='1')	   // 开水阀
					{
						delay_yudi=1;
						str[1]=1+0x30;
						beep=0;		
					}
					if(rx[1]=='0')			  //关
					{
						delay_yudi=0;
						str[1]=0+0x30;
						beep=0;
					}

					if(rx[11]=='1')	   // 开水阀
					{
						delay_1=1;
						str[11]=1+0x30;
						//beep=0;		
					}
					if(rx[11]=='0')			  //关
					{
						delay_1=0;
						str[11]=0+0x30;
						//beep=0;
					}

					if(rx[12]=='1')	   // 开水阀
					{
						delay_2=1;
						str[12]=1+0x30;
					//	beep=0;		
					}
					if(rx[12]=='0')			  //关
					{
						delay_2=0;
						str[12]=0+0x30;
					//	beep=0;
					}
				   	Uart1Sends(str);
					
					rx[0]='0' ;
					rx[10]='0';
					rx[13]='0';
			}

			if(start1==1)
			{
					if(rx[1]=='1')	   // 开水阀
					{
						delay_yudi=1;
						str[1]=1+0x30;
						beep=0;		
					}
					
					if(rx[1]=='0')			  //关
					{
						delay_yudi=0;
						str[1]=0+0x30;
						beep=0;
					}

					if(rx[11]=='1')	   // 开水阀
					{
						delay_1=1;
						str[11]=1+0x30;
					//	beep=0;		
					}
					if(rx[11]=='0')			  //关
					{
						delay_1=0;
						str[11]=0+0x30;
					//	beep=0;
					}

					if(rx[12]=='1')	   // 开水阀
					{
						delay_2=1;
						str[12]=1+0x30;
					//	beep=0;		
					}
					if(rx[12]=='0')			  //关
					{
						delay_2=0;
						str[12]=0+0x30;
					//	beep=0;
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
				if(rx[0]== 'B')
				{
						rx_cnt++;
						if(rx_cnt>=14)
						{
								if(rx[0]=='B' && rx[10]=='S'&&rx[13]=='E')
								{
										flag_start=1;	start1=0;	rx_cnt=0;	
								}
								if(rx[0]=='B' && rx[10]=='M'&&rx[13]=='E')
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

void delay()//延时程序
{
		uchar m,n,s;
		for(m=20;m>0;m--)
		for(n=20;n>0;n--)
		for(s=248;s>0;s--);
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
/********************************************************************
                              结束
*********************************************************************/