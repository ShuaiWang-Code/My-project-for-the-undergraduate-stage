/********************************************************************
                            ��ϿƼ�
ʵ�ֹ���:�˰����ײ��Գ���
ʹ��оƬ��AT89S52
����11.0592MHZ
�����ʣ�9600
     
*********************************************************************/
/********************************************************************
˵����1��	�����������ʱ����Ƭ��IO������͵�ƽ
*********************************************************************/
#include<reg52.h>  	       //���ļ�
#define uchar unsigned char//�궨���޷����ַ���
#define uint unsigned int  //�궨���޷�������


typedef bit BOOL  ;  
uchar data_byte; 


uchar str[14]="c000000000S00E";

/********************************************************************
                            I/O����
*********************************************************************/
sbit delay_MQ=P0^4;	 //���嵥Ƭ��P1�ڵĵ�1λ ����P0.0��Ϊ���ض�

sbit beep=P0^6;
sbit out =P0^1;
sbit delay_door=P0^3;
sbit delay_curtain=P0^2;
sbit DOUT=P2^0;	 //���嵥Ƭ��P2�ڵĵ�1λ ����P2.0��Ϊ�������������
/********************************************************************
                            ����
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
	while(1)   //����ѭ��
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
		    		delay();//��ʱ������
					if(DOUT==0)//ȷ�� Ũ�ȸ����趨ֵʱ ��ִ����������
			    	{
				 		delay_MQ=1;	   //�պϳ�������
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
		    		delay();//��ʱ������
					if(DOUT==0)//ȷ�� Ũ�ȸ����趨ֵʱ ��ִ����������
			    	{
				 		delay_MQ=1;	   //�պϳ�������
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

				if(rx[1]=='1')	   // ��������
				{
						delay_MQ=1;
						beep=0;
						str[1]=1+0x30;		
				}
				
				if(rx[1]=='0')			  //��
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
				
				if(rx[3]=='0')			  //��
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
				
				if(rx[4]=='0')			  //��
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
				if(rx[1]=='1')	   // ��������
				{
						delay_MQ=1;
						beep=0;	
						str[1]=1+0x30;	
				}
				
				if(rx[1]=='0')			  //��
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
				
				if(rx[3]=='0')			  //��
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
				
				if(rx[4]=='0')			  //��
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



//���п���������char�����飬������ֹ��/0��ֹͣ
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

void delay()//��ʱ����
{
uchar m,n,s;
for(m=20;m>0;m--)
for(n=20;n>0;n--)
for(s=248;s>0;s--);
}

void SerialInti()//��ʼ�����򣨱���ʹ�ã������޷��շ���
{	TMOD = 0x20;
    SCON = 0x50;
    TH1 = 0xFD;
    TL1 = TH1;
    PCON = 0x00;
    EA = 1;
    ES = 1;
    TR1 = 1;		//������ʱ��1
    
}	
/********************************************************************
                              ����
*********************************************************************/