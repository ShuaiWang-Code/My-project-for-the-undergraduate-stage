/*********************************************************************/
/********************************************************************
˵����1��	�����������ʱ����Ƭ��IO������͵�ƽ
*********************************************************************/
#include<reg52.h>  	       //���ļ�

#define uchar unsigned char//�궨���޷����ַ���
#define uint unsigned int  //�궨���޷�������

typedef bit BOOL  ;  
uchar data_byte; 
uchar str[14]="b000000000S00E";

sbit delay_yudi=P0^4;	 //���嵥Ƭ��P1�ڵĵ�1λ ����P0.0��Ϊ���ض�
sbit delay_1=P0^0;
sbit delay_2=P0^1;
sbit beep=P0^6;
sbit DOUT=P2^0;	 //���嵥Ƭ��P2�ڵĵ�1λ ����P2.0��Ϊ������������� 

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

			 	if(DOUT==0)//����ˮ��ʱ ��ִ����������
			 	{
		    		delay();//��ʱ������
					if(DOUT==0)//ȷ�� Ũ�ȸ����趨ֵʱ ��ִ����������
			    	{
				 		delay_yudi=1;	   //�պϳ�������
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
				if(DOUT==0)//����ˮ��ʱ ��ִ����������
			 	{
		    		delay();//��ʱ������
					if(DOUT==0)//ȷ�� Ũ�ȸ����趨ֵʱ ��ִ����������
			    	{
				 		delay_yudi=1;	   //�պϳ�������
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
					
					if(rx[1]=='1')	   // ��ˮ��
					{
						delay_yudi=1;
						str[1]=1+0x30;
						beep=0;		
					}
					if(rx[1]=='0')			  //��
					{
						delay_yudi=0;
						str[1]=0+0x30;
						beep=0;
					}

					if(rx[11]=='1')	   // ��ˮ��
					{
						delay_1=1;
						str[11]=1+0x30;
						//beep=0;		
					}
					if(rx[11]=='0')			  //��
					{
						delay_1=0;
						str[11]=0+0x30;
						//beep=0;
					}

					if(rx[12]=='1')	   // ��ˮ��
					{
						delay_2=1;
						str[12]=1+0x30;
					//	beep=0;		
					}
					if(rx[12]=='0')			  //��
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
					if(rx[1]=='1')	   // ��ˮ��
					{
						delay_yudi=1;
						str[1]=1+0x30;
						beep=0;		
					}
					
					if(rx[1]=='0')			  //��
					{
						delay_yudi=0;
						str[1]=0+0x30;
						beep=0;
					}

					if(rx[11]=='1')	   // ��ˮ��
					{
						delay_1=1;
						str[11]=1+0x30;
					//	beep=0;		
					}
					if(rx[11]=='0')			  //��
					{
						delay_1=0;
						str[11]=0+0x30;
					//	beep=0;
					}

					if(rx[12]=='1')	   // ��ˮ��
					{
						delay_2=1;
						str[12]=1+0x30;
					//	beep=0;		
					}
					if(rx[12]=='0')			  //��
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

void delay()//��ʱ����
{
		uchar m,n,s;
		for(m=20;m>0;m--)
		for(n=20;n>0;n--)
		for(s=248;s>0;s--);
}

void SerialInti()//��ʼ�����򣨱���ʹ�ã������޷��շ���
{	
		TMOD = 0x20;
	    SCON = 0x50;
	    TH1 = 0xFD;
	    TL1 = TH1;
	    PCON = 0x00;
	    EA = 1;
	    ES = 1;
	    TR1 = 1;		//������ʱ��1
    
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
/********************************************************************
                              ����
*********************************************************************/