#include <reg52.h>
#include "intrins.h"
#include  <math.h>    //Keil library  
#include  <stdio.h>   //Keil library

#define uint unsigned int  
#define uchar unsigned char 
//#define FOSC    11059200L  //晶振11.0592M
//#define BAUD    9600

sbit beep = P0^0;
sbit delay_pm=P0^1;
sbit pwm=P0^3;
sbit DOUT=P0^2;	 

typedef unsigned char BYTE;
typedef unsigned int WORD;
typedef bit BOOL  ; 

/*Declare SFR associated with the ADC */
sfr AUXR1       =   0XA2;
sfr ADC_CONTR   =   0xBC;           //ADC control register
sfr ADC_RES     =   0xBD;           //ADC high 8-bit result register
sfr ADC_RESL    =   0xBE;
sfr ADC_LOW2    =   0xBE;           //ADC low 2-bit result register
sfr P1ASF       =   0x9D;           //P1 secondary function control register

/*Define ADC operation const for ADC_CONTR*/
#define ADC_POWER   0x80            //ADC power control bit
#define ADC_FLAG    0x10            //ADC complete flag
#define ADC_START   0x08            //ADC start control bit
#define ADC_SPEEDLL 0x00            //420 clocks
#define ADC_SPEEDL  0x20            //280 clocks
#define ADC_SPEEDH  0x40            //140 clocks
#define ADC_SPEEDHH 0x60            //70 clocks 


uchar data_byte; 
uchar str[14]="d000000000S00E";



void InitADC();
int GetADCResult(BYTE ch);
void Delay2(WORD n);
void conversion(uint temp_data);


void SerialInti();//初始化程序（必须使用，否则无法收发）
void Uart1Sends(uchar *str);
void protocol_model();
void protocol_select();
void delay();
void io_init();

uchar ge,shi,bai,qian,wan;           //显示变量

uchar rx[14],rx_cnt=0,flag_start=0,flag_control=0,start0=0,start1=0;

uint x;


/******************************************************************************

**************************** 

*************************************************主函数

***************************************************/ 

void main() 
{  

	InitADC(); 
 	delay(); 
	SerialInti();
	io_init();
	delay();
 	while(1) 
 	{              
		protocol_select();
 	} 

}

void io_init()
{
		beep=0;
		delay_pm=0;
		DOUT=1;
		pwm=0;
}

void protocol_select()
{
		if(flag_start==1)
		{	   
				flag_start=0;
				start0=1;
				
				x=GetADCResult(1);
				conversion(x);
				if(x>50)
				{
						delay_pm=1;
						beep=1;
						str[1]=1+0x30;			
				}
				else
				{
						delay_pm=0;
						beep=0;
						str[1]=0+0x30;
				}

			 	if(DOUT==0)//
			 	{
		    		delay();//延时抗干扰
					if(DOUT==0)//确定 浓度高于设定值时 ，执行条件函数
			    	{
						str[2]=1+0X30;
					}
			 	}
		
				if(DOUT!=0)
				{
						str[2]=0+0X30;
				}

				Uart1Sends(str);
					
				rx[0] ='0';
				rx[10]='0';
				rx[13]='0';	
		}

		if(start0==1)
		{
				x=GetADCResult(1);
				conversion(x);
				if(x>100)
				{
						delay_pm=1;
						beep=1;
						str[1]=1+0x30;			
				}
				else
				{
						delay_pm=0;
						beep=0;
						str[1]=0+0x30;
				}

			 	if(DOUT==0)//当有人
			 	{
		    		delay();//延时抗干扰
					if(DOUT==0)//确定 浓度高于设定值时 ，执行条件函数
			    	{
						str[2]=1+0X30;
					}
			 	}
		
				if(DOUT!=0)
				{
						str[2]=0+0X30;
				}
		}

			if(flag_control==1)
			{
					flag_control=0;
					start1=1;

					x=GetADCResult(1);
					conversion(x);

					if(rx[1]=='1')	   // 开排气扇
					{
						delay_pm=1;
						str[1]=1+0x30;
						beep=0;		
					}
					if(rx[1]=='0')			  //关
					{
						delay_pm=0;
						str[1]=0+0x30;
						beep=0;
					}

					if(DOUT==0)//当有人
				 	{
			    		delay();//延时抗干扰
						if(DOUT==0)//确定 浓度高于设定值时 ，执行条件函数
				    	{
							str[2]=1+0X30;
						}
				 	}
			
					if(DOUT!=0)
					{
							str[2]=0+0X30;
					}
						
				   	Uart1Sends(str);
					
					rx[0]= '0';
					rx[10]='0';
					rx[13]='0';
			}

			if(start1==1)
			{
					x=GetADCResult(1);
					conversion(x);

					if(rx[1]=='1')	   // 开水阀
					{
						delay_pm=1;
						str[1]=1+0x30;
						beep=0;		
					}
					
					if(rx[1]=='0')			  //关
					{
						delay_pm=0;
						str[1]=0+0x30;
						beep=0;
					}

					if(DOUT==0)//当有人
				 	{
			    		delay();//延时抗干扰
						if(DOUT==0)//确定 浓度高于设定值时 ，执行条件函数
				    	{
							str[2]=1+0X30;
						}
				 	}
			
					if(DOUT!=0)
					{
							str[2]=0+0X30;
					}
			}	
}

void timer0() interrupt 1
{
		static unsigned int intr_flag;
		TH0=(65535-2000)/256;
		TL0=(65535-2000)%256;
		intr_flag++;
		if(intr_flag>500)
		{
			intr_flag=0;
			pwm=~pwm;
		}
			
}

void Serial_interrupt() interrupt 4 
{
	   
	   protocol_model();

}

void protocol_model()
{
		pwm=~pwm;
		if(RI)
		{
				RI=0;
				rx[rx_cnt]=SBUF;
				if(rx[0]== 'D')
				{
						rx_cnt++;
						if(rx_cnt>=14)
						{
								if(rx[0]=='D' && rx[10]=='S'&&rx[13]=='E')
								{
										flag_start=1;	start1=0;	rx_cnt=0;	
								}
								if(rx[0]=='D' && rx[10]=='M'&&rx[13]=='E')
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

void SerialInti()//初始化程序（必须使用，否则无法收发）
{	
		TMOD = 0x21;
	    SCON = 0x50;
	    TH1 = 0xFD;
	    TL1 = TH1;
		TH0=(65535-2000)/256;
		TL0=(65535-2000)%256;
	    PCON = 0x00;
	    EA = 1;
	    ES = 1;
		TR0=1;
		ET0=1;
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

void conversion(uint temp_data)  
{  
    wan=temp_data/10000+0x30 ;
	qian=temp_data%10000/1000+0x30 ;
	str[3]=qian; 
    bai=temp_data%1000/100+0x30   ;
	str[4]=bai; 
    shi=temp_data%100/10+0x30    ;
	str[5]=shi; 
    ge=temp_data%10+0x30; 
	str[6]=ge; 	
}

int GetADCResult(BYTE ch)
{   int AD10bitResult; 
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
    _nop_();                        //Must wait before inquiry
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//Wait complete flag
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC

    AD10bitResult=ADC_RES;
    AD10bitResult<<=8;
    AD10bitResult|=ADC_RESL;
    return AD10bitResult;                  //Return 10BIT ADC result
}

void InitADC()
{
    P1ASF = 0xff;                   //Open 8 channels ADC function

	AUXR1=AUXR1|0X04;              //ad值左对齐
    ADC_RES = 0;                    //Clear previous result
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    Delay2(2);                       //ADC power-on and delay
}

void Delay2(WORD n)
{
    WORD x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}


void delay()//延时程序
{
		uchar m,n,s;
		for(m=20;m>0;m--)
		for(n=20;n>0;n--)
		for(s=248;s>0;s--);
} 


